#ifndef UPDATECOMETS_H
#define UPDATECOMETS_H


#include <QGuiApplication>
#include <QClipboard>
#include <QDesktopServices>
//#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QHash>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStandardItemModel>
#include <QString>
#include <QTemporaryFile>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <QDir>

#include <QColor>
//#include <QColorDialog>
//#include <QFileDialog>
#include <QImageReader>
#include <QHash>
#include <QList>
#include <QString>
#include <QVariant>

#include <QObject>
//#include "StelDialog.hpp"

#include <QHash>
#include <QString>

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QStandardItemModel>

#include <QDate>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QString>

#include "SolarSystemEditor.hpp"

//! Convenience type for storage of SSO properties in ssystem_minor.ini format.
//! This is an easy way of storing data in the format used in Stellarium's
//! solar system configuration file.
//! What would be key/value pairs in a section in the ssystem_minor.ini file
//! are key/value pairs in the hash. The section name is stored with key
//! "section_name".
//! As it is a hash, key names are not stored alphabetically. This allows
//! for rapid addition and look-up of values, unlike a real QSettings
//! object in StelIniFormat.
//! Also, using this way may allow scripts to define SSOs.
//! \todo Better name.
typedef QHash<QString, QVariant> SsoElements;

class UpdateComets : public QObject
{	Q_OBJECT
public:
    enum ImportType {
                     MpcComets,
                     MpcMinorPlanets
                     };
public:

    UpdateComets();

    ImportType importType;//
    SolarSystemEditor * ssoManager;//
    QList<SsoElements> candidatesForAddition;
    QList<SsoElements> candidatesForUpdate;
    QStandardItemModel * candidateObjectsModel;//

    //Downloading
    QNetworkAccessManager * networkManager;//
    QNetworkReply * downloadReply;//
    QNetworkReply * queryReply;//
    class StelProgressController * downloadProgressBar;//
    class StelProgressController * queryProgressBar;//

    QString downloadUrl;

public slots:
    void startDownload(QString urlString);
    void downloadComplete(QNetworkReply *reply);
    void deleteDownloadProgressBar();

    void updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    QList<SsoElements> readElementsFromFile(QString filePath);

    void populateCandidateObjects(QList<SsoElements> objects);
    void addObjects();

    void setDownloadUrl(QString url);
    void startDownloads();
};



#endif // UPDATECOMETS_H
