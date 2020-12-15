/*
 * Stellarium
 * Copyright (C) 2008 Guillaume Chereau
 *
 * Stellarium N9 QML Gui
 * Copyright (C) 2012 Marko Srebre
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
*/

#include "StelQmlSearch.hpp"
#include "StelApp.hpp"
#include "StelCore.hpp"
#include "StelModuleMgr.hpp"
#include "StelMovementMgr.hpp"
#include "StelTranslator.hpp"

#include "StelObjectMgr.hpp"
#include "StelUtils.hpp"

#include <QDebug>
#include <QSettings>
#include <QString>
#include <QStringList>

#include "SimbadSearcher.hpp"

//const char* StelQmlSearch::DEF_SIMBAD_URL = "http://simbad.u-strasbg.fr/";

StelQmlSearch::StelQmlSearch()
    //: simbadReply(NULL)
{

    //simbadSearcher = new SimbadSearcher(this);


    greekLetters.insert("alpha", QString(QChar(0x03B1)));
    greekLetters.insert("beta", QString(QChar(0x03B2)));
    greekLetters.insert("gamma", QString(QChar(0x03B3)));
    greekLetters.insert("delta", QString(QChar(0x03B4)));
    greekLetters.insert("epsilon", QString(QChar(0x03B5)));

    greekLetters.insert("zeta", QString(QChar(0x03B6)));
    greekLetters.insert("eta", QString(QChar(0x03B7)));
    greekLetters.insert("theta", QString(QChar(0x03B8)));
    greekLetters.insert("iota", QString(QChar(0x03B9)));
    greekLetters.insert("kappa", QString(QChar(0x03BA)));

    greekLetters.insert("lambda", QString(QChar(0x03BB)));
    greekLetters.insert("mu", QString(QChar(0x03BC)));
    greekLetters.insert("nu", QString(QChar(0x03BD)));
    greekLetters.insert("xi", QString(QChar(0x03BE)));
    greekLetters.insert("omicron", QString(QChar(0x03BF)));

    greekLetters.insert("pi", QString(QChar(0x03C0)));
    greekLetters.insert("rho", QString(QChar(0x03C1)));
    greekLetters.insert("sigma", QString(QChar(0x03C3))); // second lower-case sigma shouldn't affect anything
    greekLetters.insert("tau", QString(QChar(0x03C4)));
    greekLetters.insert("upsilon", QString(QChar(0x03C5)));

    greekLetters.insert("phi", QString(QChar(0x03C6)));
    greekLetters.insert("chi", QString(QChar(0x03C7)));
    greekLetters.insert("psi", QString(QChar(0x03C8)));
    greekLetters.insert("omega", QString(QChar(0x03C9)));

    QSettings* conf = StelApp::getInstance().getSettings();
    Q_ASSERT(conf);
    //useSimbad = conf->value("search/flag_search_online", true).toBool();
    //simbadServerUrl = conf->value("search/simbad_server_url", DEF_SIMBAD_URL).toString();
}

StelQmlSearch::~StelQmlSearch()
{
//	if (simbadReply)
//	{
//		simbadReply->deleteLater();
//		simbadReply = NULL;
//	}
}


//void StelQmlSearch::enableSimbadSearch(bool enable)
//{
//	useSimbad = enable;

//	QSettings* conf = StelApp::getInstance().getSettings();
//	Q_ASSERT(conf);
//	conf->setValue("search/flag_search_online", useSimbad);
//}


void StelQmlSearch::updateSearchResults(const QString& text, QStringList& matches)
{
    StelObjectMgr* objectMgr = GETSTELMODULE(StelObjectMgr);

//    if (useSimbad) {
//		if (simbadReply) {
//			disconnect(simbadReply,
//				   SIGNAL(statusChanged()),
//				   this,
//				   SLOT(onSimbadStatusChanged()));
//			delete simbadReply;
//			simbadReply=NULL;
//		}
//		simbadResults.clear();
//	}

    QString trimmedText = text.trimmed().toLower();

    if (!trimmedText.isEmpty())
    {
//		if (useSimbad)
//		{
//			simbadReply = simbadSearcher->lookup(simbadServerUrl, trimmedText, 3);
//			onSimbadStatusChanged();
//			connect(simbadReply, SIGNAL(statusChanged()), this, SLOT(onSimbadStatusChanged()));
//		}

        QString greekText = substituteGreek(trimmedText);

        if(greekText != trimmedText) {
            matches = objectMgr->listMatchingObjectsI18n(trimmedText, 3);
            matches += objectMgr->listMatchingObjectsI18n(greekText, (20 - matches.size()));
        } else {
            matches = objectMgr->listMatchingObjectsI18n(trimmedText, 20);
        }
    }

}

// Called when the current simbad query status changes
//void StelQmlSearch::onSimbadStatusChanged()
//{
//	Q_ASSERT(simbadReply);
//	if (simbadReply->getCurrentStatus()==SimbadLookupReply::SimbadLookupErrorOccured)
//	{
//		ui->simbadStatusLabel->setText(QString("%1: %2")
//					       .arg(q_("Simbad Lookup Error"))
//					       .arg(simbadReply->getErrorString()));
//		if (ui->completionLabel->isEmpty())
//			ui->pushButtonGotoSearchSkyObject->setEnabled(false);
//	}
//	else
//	{
//		ui->simbadStatusLabel->setText(QString("%1: %2")
//					       .arg(q_("Simbad Lookup"))
//					       .arg(simbadReply->getCurrentStatusString()));
//		// Query not over, don't disable button
//		ui->pushButtonGotoSearchSkyObject->setEnabled(true);
//	}

//	if (simbadReply->getCurrentStatus()==SimbadLookupReply::SimbadLookupFinished)
//	{
//		simbadResults = simbadReply->getResults();
//		ui->completionLabel->appendValues(simbadResults.keys());
//		// Update push button enabled state
//		ui->pushButtonGotoSearchSkyObject->setEnabled(!ui->completionLabel->isEmpty());
//	}

//	if (simbadReply->getCurrentStatus()!=SimbadLookupReply::SimbadLookupQuerying)
//	{
//		disconnect(simbadReply, SIGNAL(statusChanged()), this, SLOT(onSimbadStatusChanged()));
//		delete simbadReply;
//		simbadReply=NULL;

//		// Update push button enabled state
//		ui->pushButtonGotoSearchSkyObject->setEnabled(!ui->completionLabel->isEmpty());
//	}
//}



bool StelQmlSearch::gotoObject(const QString& name)
{
    if (name.isEmpty())
        return false;

    StelMovementMgr* mvmgr = GETSTELMODULE(StelMovementMgr);

//	if (simbadResults.contains(name))
//	{
//		close();
//		Vec3d pos = simbadResults[name];
//		objectMgr->unSelect();
//		mvmgr->moveToJ2000(pos, mvmgr->getAutoMoveDuration());
//	}

    StelObjectMgr* objectMgr = GETSTELMODULE(StelObjectMgr);

    if (objectMgr->findAndSelectI18n(name))
    {
        const QList<StelObjectP> newSelected = objectMgr->getSelectedObject();
        if (!newSelected.empty())
        {
            // Can't point to home planet
            if (newSelected[0]->getEnglishName()!=StelApp::getInstance().getCore()->getCurrentLocation().planetName)
            {
                mvmgr->moveToObject(newSelected[0], mvmgr->getAutoMoveDuration());
                mvmgr->setFlagTracking(true);
            }
            else
            {
                GETSTELMODULE(StelObjectMgr)->unSelect();
            }
        }
        return true;
    }

    //simbadResults.clear();


    return false;
}


QString StelQmlSearch::substituteGreek(const QString& keyString)
{
    if (!keyString.contains(' '))
        return getGreekLetterByName(keyString);
    else
    {
        QStringList nameComponents = keyString.split(" ", QString::SkipEmptyParts);
        if(!nameComponents.empty())
            nameComponents[0] = getGreekLetterByName(nameComponents[0]);
        return nameComponents.join(" ");
    }
}

QString StelQmlSearch::getGreekLetterByName(const QString& potentialGreekLetterName)
{
    if(greekLetters.contains(potentialGreekLetterName))
        return greekLetters[potentialGreekLetterName.toLower()];

    // There can be indices (e.g. "α1 Cen" instead of "α Cen A"), so strip
    // any trailing digit.
    int lastCharacterIndex = potentialGreekLetterName.length()-1;
    if(potentialGreekLetterName.at(lastCharacterIndex).isDigit())
    {
        QChar digit = potentialGreekLetterName.at(lastCharacterIndex);
        QString name = potentialGreekLetterName.left(lastCharacterIndex);
        if(greekLetters.contains(name))
            return greekLetters[name.toLower()] + digit;
    }

    return potentialGreekLetterName;
}

//void StelQmlSearch::populateSimbadServerList()
//{
//	Q_ASSERT(ui);
//	Q_ASSERT(ui->serverListComboBox);

//	QComboBox* servers = ui->serverListComboBox;
//	//Save the current selection to be restored later
//	servers->blockSignals(true);
//	int index = servers->currentIndex();
//	QVariant selectedUrl = servers->itemData(index);
//	servers->clear();
//	//For each server, display the localized description and store the URL as user data.
//	servers->addItem(q_("University of Strasbourg (France)"), DEF_SIMBAD_URL);
//	servers->addItem(q_("Harvard University (USA)"), "http://simbad.harvard.edu/");

//	//Restore the selection
//	index = servers->findData(selectedUrl, Qt::UserRole, Qt::MatchCaseSensitive);
//	servers->setCurrentIndex(index);
//	servers->model()->sort(0);
//	servers->blockSignals(false);
//}

//void StelQmlSearch::selectSimbadServer(int index)
//{
//	if (index < 0)
//		simbadServerUrl = DEF_SIMBAD_URL;
//	else
//		simbadServerUrl = ui->serverListComboBox->itemData(index).toString();

//	QSettings* conf = StelApp::getInstance().getSettings();
//	Q_ASSERT(conf);
//	conf->setValue("search/simbad_server_url", simbadServerUrl);
//}
