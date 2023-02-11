#include "updatecomets.h"

#include "StelApp.hpp"
#include "StelFileMgr.hpp"
#include "StelJsonParser.hpp"
#include "StelModuleMgr.hpp"
#include "StelTranslator.hpp"
#include "SolarSystem.hpp"
#include "StelProgressController.hpp"
//#include "SearchDialog.hpp"
#include "StelUtils.hpp"

#include "StelApp.hpp"
#include "StelFileMgr.hpp"
#include "StelModuleMgr.hpp"
#include "StelApp.hpp"
#include "StelFileMgr.hpp"
#include "StelModuleMgr.hpp"
#include "StelTranslator.hpp"
#include "Planet.hpp"
#include "SolarSystem.hpp"
//#include "StelGui.hpp"
#include "StelModule.hpp"
//#include "CAIMainWindow.hpp"


#include "StelUtils.hpp"
#include "StelApp.hpp"
//#include "StelGui.hpp"
//#include "StelGuiItems.hpp"
#include "StelFileMgr.hpp"
#include "StelIniParser.hpp"
#include "StelLocaleMgr.hpp"
#include "StelModuleMgr.hpp"
#include "StelObjectMgr.hpp"
#include "SolarSystem.hpp"
#include "Orbit.hpp"


#include <cmath>
#include <stdexcept>
#include "StelModule.hpp"
#include "SolarSystemEditor.hpp"

UpdateComets::UpdateComets()
    :importType(ImportType())
    , downloadReply(Q_NULLPTR)
    , queryReply(Q_NULLPTR)
    , downloadProgressBar(Q_NULLPTR)
    , queryProgressBar(Q_NULLPTR)
{
//    ssoManager = GETSTELMODULE(SolarSystemEditor);
    ssoManager = new SolarSystemEditor();
    networkManager = new QNetworkAccessManager();
    candidateObjectsModel = new QStandardItemModel(this);
}

void UpdateComets::startDownload(QString urlString)
{
//    QString urlString = "http://astro.vanbuitenen.nl/cometelements?format=mpc&mag=obs";
    if (downloadReply)
    {
        //There's already an operation in progress?
        //TODO
        return;
    }

    QUrl url(urlString);
    if (!url.isValid() || url.isRelative() || !url.scheme().startsWith("http", Qt::CaseInsensitive))
    {
        qWarning() << "Invalid URL:" << urlString;
        return;
    }
    //qDebug() << url.toString();

    //TODO: Interface changes!

    downloadProgressBar = StelApp::getInstance().addProgressBar();
    downloadProgressBar->setValue(0);
    downloadProgressBar->setRange(0, 0);

    //TODO: Better handling of the interface
    //dialog->setVisible(false);
//        enableInterface(false);
//        ui->pushButtonAbortDownload->setVisible(true);

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadComplete(QNetworkReply*)));
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("User-Agent", StelUtils::getUserAgentString().toUtf8());
    #if QT_VERSION >= 0x050600
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    #endif
    downloadReply = networkManager->get(request);
    connect(downloadReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateDownloadProgress(qint64,qint64)));
}

void UpdateComets::deleteDownloadProgressBar()
{
    disconnect(this, SLOT(updateDownloadProgress(qint64,qint64)));

    if (downloadProgressBar)
    {
        StelApp::getInstance().removeProgressBar(downloadProgressBar);
        downloadProgressBar = Q_NULLPTR;
    }
}

void UpdateComets::updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (downloadProgressBar == Q_NULLPTR)
        return;

    int currentValue = 0;
    int endValue = 0;

    if (bytesTotal > -1 && bytesReceived <= bytesTotal)
    {
        //Round to the greatest possible derived unit
        while (bytesTotal > 1024)
        {
            bytesReceived = std::floor(bytesReceived / 1024.);
            bytesTotal    = std::floor(bytesTotal / 1024.);
        }
        currentValue = bytesReceived;
        endValue = bytesTotal;
    }

    downloadProgressBar->setValue(currentValue);
    downloadProgressBar->setRange(0, endValue);
}

void UpdateComets::downloadComplete(QNetworkReply *reply)
{
    disconnect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadComplete(QNetworkReply*)));
    deleteDownloadProgressBar();
//    ui->pushButtonAbortDownload->setVisible(false);

    /*
    qDebug() << "reply->isOpen():" << reply->isOpen()
        << "reply->isReadable():" << reply->isReadable()
        << "reply->isFinished():" << reply->isFinished();
    */

    if(reply->error() || reply->bytesAvailable()==0)
    {
        qWarning() << "Download error: While downloading"
                   << reply->url().toString()
                   << "the following error occured:"
                   << reply->errorString();
//		enableInterface(true);
        reply->deleteLater();
        downloadReply = Q_NULLPTR;
        return;
    }

    QList<SsoElements> objects;
    QTemporaryFile file;
    if (file.open())
    {
        file.write(reply->readAll());
        file.close();
        objects = readElementsFromFile(file.fileName());
    }
    else
    {
        qWarning() << "Unable to open a temporary file. Aborting operation.";
    }

    if (objects.isEmpty())
    {
        qWarning() << "No objects found in the file downloaded from"
                   << reply->url().toString();
    }
    else
    {
        //The request has been successful: add the URL to bookmarks?
//        if (ui->checkBoxAddBookmark->isChecked())
//        {
//            QString url = reply->url().toString();
//            QString title = ui->lineEditBookmarkTitle->text().trimmed();
//            //If no title has been entered, use the URL as a title
//            if (title.isEmpty())
//                title = url;
//            if (!bookmarks.value(importType).values().contains(url))
//            {
//                bookmarks[importType].insert(title, url);
//                populateBookmarksList();
//                saveBookmarks();
//            }
//        }
    }

    reply->deleteLater();
    downloadReply = Q_NULLPTR;

    //Temporary, until the slot/socket mechanism is ready
    populateCandidateObjects(objects);
//    ui->stackedWidget->setCurrentIndex(1);
    //As this window is persistent, if the Solar System is changed
    //while there is a list, it should be reset.
//    connect(ssoManager, SIGNAL(solarSystemChanged()), this, SLOT(resetDialog()));

    addObjects();
}

//填充候选对象
void UpdateComets::populateCandidateObjects(QList<SsoElements> objects)
{
    candidatesForAddition.clear();

    //Get a list of the current objects
    //QHash<QString,QString> defaultSsoIdentifiers = ssoManager->getDefaultSsoIdentifiers();
    QHash<QString,QString> loadedSsoIdentifiers = ssoManager->listAllLoadedSsoIdentifiers();

    //Separating the objects into visual groups in the list
    //int newDefaultSsoIndex = 0;
    int newLoadedSsoIndex = 0;
    int newNovelSsoIndex = 0;
    int insertionIndex = 0;

    QStandardItemModel * model = candidateObjectsModel;
    model->clear();
    model->setColumnCount(1);

    for (auto object : objects)
    {
        QString name = object.value("name").toString();
        qDebug()<<"populate Candidate Objects:"<<name;
        if (name.isEmpty())
            continue;

        QString group = object.value("section_name").toString();
        if (group.isEmpty())
            continue;

        //Prevent name conflicts between asteroids and moons
        if (loadedSsoIdentifiers.contains(name))
        {
            if (loadedSsoIdentifiers.value(name) != group)
            {
                name.append('*');
                object.insert("name", name);
            }
        }

        QStandardItem * item = new QStandardItem();
        item->setText(name);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setCheckState(Qt::Unchecked);

//      //重复
//		if (defaultSsoIdentifiers.contains(name))
//		{
//			//Duplicate of a default solar system object
//			QFont itemFont(item->font());
//			itemFont.setBold(true);
//			item->setFont(itemFont);

//			candidatesForUpdate.append(object);

//			insertionIndex = newDefaultSsoIndex;
//			newDefaultSsoIndex++;
//			newLoadedSsoIndex++;
//			newNovelSsoIndex++;
//		}
//		else
        if (loadedSsoIdentifiers.contains(name))
        {
            //Duplicate of another existing object
            QFont itemFont(item->font());
            itemFont.setItalic(true);
            item->setFont(itemFont);

            candidatesForUpdate.append(object);

            insertionIndex = newLoadedSsoIndex;
            newLoadedSsoIndex++;
            newNovelSsoIndex++;
        }
        else
        {
            candidatesForAddition.append(object);
            insertionIndex = newNovelSsoIndex;
            newNovelSsoIndex++;
        }

        model->insertRow(insertionIndex, item);
        qDebug()<<"model->insertRow()"<<insertionIndex<<item;
    }

    //Scroll to the first items
//    ui->listViewObjects->scrollToTop();
}

QList<SsoElements> UpdateComets::readElementsFromFile(QString filePath)
{
    Q_ASSERT(ssoManager);

    return ssoManager->readMpcOneLineCometElementsFromFile(filePath);

//    switch (type)
//    {
//        case MpcComets:
//            return ssoManager->readMpcOneLineCometElementsFromFile(filePath);
//        case MpcMinorPlanets:
//        default:
//            return ssoManager->readMpcOneLineMinorPlanetElementsFromFile(filePath);
//    }
}



void UpdateComets::addObjects()
{
//    disconnect(ssoManager, SIGNAL(solarSystemChanged()), this, SLOT(resetDialog()));

    qDebug()<<"UpdateComets: add Objects";
    QList<QString> checkedObjectsNames;

    //Extract the marked objects
    //TODO: Something smarter?
    for (int row = 0; row < candidateObjectsModel->rowCount(); row++)
    {
        QStandardItem * item = candidateObjectsModel->item(row);
//        if (item->checkState() == Qt::Checked)
//        {
            checkedObjectsNames.append(item->text());
//            if (row==0)
//                SearchDialog::extSearchText = item->text();
//        }
    }


    //qDebug() << "Checked:" << checkedObjectsNames;

    QList<SsoElements> approvedForAddition;
    for (int i = 0; i < candidatesForAddition.count(); i++)
    {
        QString name = candidatesForAddition.at(i).value("name").toString();
        if (checkedObjectsNames.contains(name))
            approvedForAddition.append(candidatesForAddition.at(i));
    }

//    bool overwrite = ui->radioButtonOverwrite->isChecked();
    bool overwrite = true;
    QList<SsoElements> approvedForUpdate;
    for (int j = 0; j < candidatesForUpdate.count(); j++)
    {
        QString name = candidatesForUpdate.at(j).value("name").toString();
        if (checkedObjectsNames.contains(name))
        {
            if (overwrite)
            {
                approvedForAddition.append(candidatesForUpdate.at(j));
            }
            else
            {
                approvedForUpdate.append(candidatesForUpdate.at(j));
            }
        }
    }

    //Write to file
    qDebug()<<"Write to file .approvedForAddition.length:"<<approvedForAddition.length();
    ssoManager->appendToSolarSystemConfigurationFile(approvedForAddition);

//    if (ui->radioButtonUpdate->isChecked())
//    {
        SolarSystemEditor::UpdateFlags flags(SolarSystemEditor::UpdateNameAndNumber | SolarSystemEditor::UpdateOrbitalElements);
//        if (!ui->checkBoxOnlyOrbitalElements->isChecked())
//        {
            flags |= SolarSystemEditor::UpdateType;
            flags |= SolarSystemEditor::UpdateMagnitudeParameters;
//        }

        ssoManager->updateSolarSystemConfigurationFile(approvedForUpdate, flags);
//    }

    //Refresh the Solar System
    GETSTELMODULE(SolarSystem)->reloadPlanets();

//    resetDialog();
//    emit objectsImported();
}

void UpdateComets::startDownloads()
{
    int msgid=0;
    qDebug()<<msgid++;//debug

    if(downloadUrl==""){
        downloadUrl = "http://astro.vanbuitenen.nl/cometelements?format=mpc&mag=obs";
    }
    QUrl url(downloadUrl);
    if (!url.isValid() || url.isRelative() || !url.scheme().startsWith("http", Qt::CaseInsensitive))
    {
        qWarning() << "Invalid URL:" << downloadUrl;
        return;
    }
    //qDebug() << url.toString();

    qDebug()<<msgid++;//debug

    //TODO: Interface changes!

    downloadProgressBar = StelApp::getInstance().addProgressBar();
    downloadProgressBar->setValue(0);
    downloadProgressBar->setRange(0, 0);

    //TODO: Better handling of the interface
    //dialog->setVisible(false);
//        enableInterface(false);
//        ui->pushButtonAbortDownload->setVisible(true);

    qDebug()<<msgid++;//debug

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadComplete(QNetworkReply*)));
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("User-Agent", StelUtils::getUserAgentString().toUtf8());
    #if QT_VERSION >= 0x050600
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    #endif

    qDebug()<<msgid++;//debug//

    downloadReply = networkManager->get(request);

    qDebug()<<msgid++;//debug

    connect(downloadReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateDownloadProgress(qint64,qint64)));


    qDebug()<<msgid++;//debug
}

void UpdateComets::setDownloadUrl(QString url)
{
    downloadUrl = url;
}
