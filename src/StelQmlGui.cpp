/*
 * Stellarium QML Gui
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
#include "StelQmlGui.hpp"
#include "StelMainGraphicsView.hpp"
#include "StelAppGraphicsWidget.hpp"

#include "StelApp.hpp"
#include "StelCore.hpp"

#include "StelUtils.hpp"
#include "StelLocaleMgr.hpp"
#include "StelMovementMgr.hpp"

#include "StarMgr.hpp"
#include "LabelMgr.hpp"
#include "NebulaMgr.hpp"
#include "SolarSystem.hpp"
#include "LandscapeMgr.hpp"
#include "GridLinesMgr.hpp"
#include "ConstellationMgr.hpp"
#include "MeteorMgr.hpp"
#include "StelSkyCultureMgr.hpp"
#include "StelModuleMgr.hpp"
#include "StelObjectMgr.hpp"
#include "StelGuiBase.hpp"
#include "StelFileMgr.hpp"
#include "StelMainWindow.hpp"
#include "StelLocationMgr.hpp"

#include "StelQmlSearch.hpp"
#include "StelQmlDateTime.hpp"
#include "StelQmlHudSettings.hpp"

#include <QGraphicsScene>


#include <QDeclarativeComponent>
#include <QDeclarativeItem>
#include <QDeclarativeContext>


#include <QApplication>
#include <QFileInfo>
#include <QSettings>
#include <QStringListModel>

#include <QDebug>

#include <QInputContext>

class EventFilter : public QObject
{
public:
    EventFilter() : prevFocusWidget(0) {}
protected:
    bool eventFilter(QObject *obj, QEvent *event) {
        QInputContext *ic = qApp->inputContext();
        if (ic) {
            if (ic->focusWidget() == 0 && prevFocusWidget)
            {
                QEvent closeSIPEvent(QEvent::CloseSoftwareInputPanel);
                ic->filterEvent(&closeSIPEvent);
            }
            else if (prevFocusWidget == 0 && ic->focusWidget())
            {
                QEvent openSIPEvent(QEvent::RequestSoftwareInputPanel);
                ic->filterEvent(&openSIPEvent);
            }
            prevFocusWidget = ic->focusWidget();
        }
        return QObject::eventFilter(obj,event);
    }

private:
    QWidget *prevFocusWidget;
};


StelQmlGui::StelQmlGui()
{

    qmlSearch = new StelQmlSearch;

    declEngine = new QDeclarativeEngine;

    declEngine->rootContext()->setContextProperty("qmlGui", this);
    declEngine->rootContext()->setContextProperty("locations", QVariant::fromValue(QStringList()));
    declEngine->rootContext()->setContextProperty("searchResults", QVariant::fromValue(QStringList()));
    declEngine->rootContext()->setContextProperty("landscapes", QVariant::fromValue(QStringList()));
    declEngine->rootContext()->setContextProperty("skyCultures", QVariant::fromValue(QStringList()));

    StelMainGraphicsView* view = &StelMainGraphicsView::getInstance();

    // hud
//    QDeclarativeComponent component(declEngine, QUrl::fromLocalFile(adjustPath("qml/stellarium-n9/Hud.qml")));
//    hud = qobject_cast<QDeclarativeItem *>(component.create());
//    if (component.isError())
//        qDebug() << component.errors();

    hud = createComponent("qml/stellarium-n9/Hud.qml");
    view->scene()->addItem(hud);
    hud->setVisible(false);

    // startup page

    startupPage = createComponent("qml/stellarium-n9/StartupPage.qml");
    view->scene()->addItem(startupPage);
    startupPage->setVisible(true);

    // settings window

    settingsWindow = createComponent("qml/stellarium-n9/SettingsWindow.qml");
    view->scene()->addItem(settingsWindow);
    settingsWindow->setVisible(false);

    EventFilter* ef = new EventFilter;  // fix for VKB
    view->scene()->installEventFilter(ef);

}

void StelQmlGui::init()
{

    NebulaMgr* nmgr = GETSTELMODULE(NebulaMgr);
    StarMgr* smgr = GETSTELMODULE(StarMgr);
    LandscapeMgr* lmgr = GETSTELMODULE(LandscapeMgr);
    GridLinesMgr* glmgr = GETSTELMODULE(GridLinesMgr);
    ConstellationMgr* cmgr = GETSTELMODULE(ConstellationMgr);
    StelMovementMgr* mvmgr = GETSTELMODULE(StelMovementMgr);

    StelMainGraphicsView* view = &StelMainGraphicsView::getInstance();

    StelCore* core = StelApp::getInstance().getCore();

    QObject* object;

    // Hud buttons

    connectItem(hud, "settingsWindow", SIGNAL(triggered()), this, SLOT(showSettingsWindow()));
    connectItem(hud, "increaseTimeSpeed", SIGNAL(triggered()), core, SLOT(increaseTimeSpeed()));
    connectItem(hud, "decreaseTimeSpeed", SIGNAL(triggered()), core, SLOT(decreaseTimeSpeed()));
    connectItem(hud, "toggleRealTimeSpeed", SIGNAL(triggered()), core, SLOT(toggleRealTimeSpeed()));
    connectItem(hud, "setTimeNow", SIGNAL(triggered()), this, SLOT(setTimeNow()));
    connectItem(hud, "centerSelected", SIGNAL(triggered()), mvmgr, SLOT(setFlagTracking()));
    connectItem(hud, "ClearSelection", SIGNAL(triggered()), this, SLOT(unselect()));

    infoTextLabel = findItem(hud, "InfoTextLabel");
    nameLabel = findItem(hud, "NameLabel");

    // Viewing Settings
    qmlHudSettings = new StelQmlHudSettings(this);

    // landscape/portrait
    object = findItem(hud, "Window");
    StelApp::getInstance().getCore()->setPortraitMode(object->property("state").toString() == "Portrait");
    QObject::connect(object, SIGNAL(stateChanged(QString)), this, SLOT(windowStateChanged(QString)));


    // Settings Window

    QObject::connect(settingsWindow, SIGNAL(backToSkyView()), this, SLOT(showHud()));

    // Free look
    object = findItem(settingsWindow, "FreeLook");
    object->setProperty("checked", view->getFreeLook());
    QObject::connect(object, SIGNAL(triggered(bool)), view, SLOT(setFreeLook(bool)));

    // Absolute scale
    object = findItem(settingsWindow, "AbsoluteScale");
    object->setProperty("value", core->getSkyDrawer()->getAbsoluteStarScale());
    QObject::connect(object, SIGNAL(valueChanged(double)), core->getSkyDrawer(), SLOT(setAbsoluteStarScale(double)));

    // Relative scale
    object = findItem(settingsWindow, "RelativeScale");
    object->setProperty("value", core->getSkyDrawer()->getRelativeStarScale());
    QObject::connect(object, SIGNAL(valueChanged(double)), core->getSkyDrawer(), SLOT(setRelativeStarScale(double)));

    // Twinkle
    object = findItem(settingsWindow, "Twinkle");
    object->setProperty("value", core->getSkyDrawer()->getTwinkleAmount());
    object->setProperty("checked", core->getSkyDrawer()->getFlagTwinkle());
    QObject::connect(object, SIGNAL(valueChanged(double)), core->getSkyDrawer(), SLOT(setTwinkleAmount(double)));
    QObject::connect(object, SIGNAL(triggered(bool)), core->getSkyDrawer(), SLOT(setFlagTwinkle(bool)));

    // Dynamic eye adaptation
    object = findItem(settingsWindow, "DynamicEyeAdaptation");
    object->setProperty("checked", core->getSkyDrawer()->getFlagLuminanceAdaptation());
    QObject::connect(object, SIGNAL(triggered(bool)), core->getSkyDrawer(), SLOT(setFlagLuminanceAdaptation(bool)));

    // Show atmosphere
    object = findItem(settingsWindow, "ShowAtmosphere");
    object->setProperty("checked", lmgr->getFlagAtmosphere());
    QObject::connect(object, SIGNAL(triggered(bool)), lmgr, SLOT(setFlagAtmosphere(bool)));

    // Light Pollution
    object = findItem(settingsWindow, "LightPollution");
    object->setProperty("value", (double) core->getSkyDrawer()->getBortleScale());
    QObject::connect(object, SIGNAL(valueChanged(double)), this, SLOT(setLightPollution(double)));


    // Planets section
    SolarSystem* ssmgr = GETSTELMODULE(SolarSystem);

    object = findItem(settingsWindow, "ShowPlanets");
    object->setProperty("checked", ssmgr->getFlagPlanets());
    QObject::connect(object, SIGNAL(triggered(bool)), ssmgr, SLOT(setFlagPlanets(bool)));

    object = findItem(settingsWindow, "ShowPlanetMarkers");
    object->setProperty("checked", ssmgr->getFlagHints());
    QObject::connect(object, SIGNAL(triggered(bool)), ssmgr, SLOT(setFlagHints(bool)));

    object = findItem(settingsWindow, "ScaleMoon");
    object->setProperty("checked", ssmgr->getFlagMoonScale());
    QObject::connect(object, SIGNAL(triggered(bool)), ssmgr, SLOT(setFlagMoonScale(bool)));

    object = findItem(settingsWindow, "ShowPlanetOrbits");
    object->setProperty("checked", ssmgr->getFlagOrbits());
    QObject::connect(object, SIGNAL(triggered(bool)), ssmgr, SLOT(setFlagOrbits(bool)));

    object = findItem(settingsWindow, "SimulateLightSpeed");
    object->setProperty("checked", ssmgr->getFlagLightTravelTime());
    QObject::connect(object, SIGNAL(triggered(bool)), ssmgr, SLOT(setFlagLightTravelTime(bool)));


    // Label and Markers

    object = findItem(settingsWindow, "StarLabels");
    object->setProperty("value", (double) smgr->getLabelsAmount());
    object->setProperty("checked", smgr->getFlagLabels());
    QObject::connect(object, SIGNAL(valueChanged(double)), this, SLOT(setStarLabels(double)));
    QObject::connect(object, SIGNAL(triggered(bool)), smgr, SLOT(setFlagLabels(bool)));

    object = findItem(settingsWindow, "PlanetLabels");
    object->setProperty("value", (double) ssmgr->getLabelsAmount());
    object->setProperty("checked", ssmgr->getFlagLabels());
    QObject::connect(object, SIGNAL(valueChanged(double)), this, SLOT(setPlanetLabels(double)));
    QObject::connect(object, SIGNAL(triggered(bool)), ssmgr, SLOT(setFlagLabels(bool)));

    object = findItem(settingsWindow, "NebulaLabels");
    object->setProperty("value", (double) nmgr->getLabelsAmount());
    object->setProperty("checked", nmgr->getFlagHints());
    QObject::connect(object, SIGNAL(valueChanged(double)), this, SLOT(setNebulaLabels(double)));
    QObject::connect(object, SIGNAL(triggered(bool)), nmgr, SLOT(setFlagHints(bool)));


    // Search page

    object = findItem(settingsWindow, "ObjectSearchPage");
    QObject::connect(object, SIGNAL(searchTextChanged(QString)), this, SLOT(onObjectSearchTextChanged(QString)));
    QObject::connect(object, SIGNAL(searchTextEntered(QString, bool)), this, SLOT(onObjectSearchTextEntered(QString, bool)));


    // Markings page

    object = findItem(settingsWindow, "EquatorialGrid");
    object->setProperty("checked", glmgr->getFlagEquatorGrid());
    QObject::connect(object, SIGNAL(triggered(bool)), glmgr, SLOT(setFlagEquatorGrid(bool)));

    object = findItem(settingsWindow, "EquatorialGridJ2000");
    object->setProperty("checked", glmgr->getFlagEquatorJ2000Grid());
    QObject::connect(object, SIGNAL(triggered(bool)), glmgr, SLOT(setFlagEquatorJ2000Grid(bool)));

    object = findItem(settingsWindow, "AzimuthalGrid");
    object->setProperty("checked", glmgr->getFlagAzimuthalGrid());
    QObject::connect(object, SIGNAL(triggered(bool)), glmgr, SLOT(setFlagAzimuthalGrid(bool)));

    object = findItem(settingsWindow, "GalacticGrid");
    object->setProperty("checked", glmgr->getFlagGalacticGrid());
    QObject::connect(object, SIGNAL(triggered(bool)), glmgr, SLOT(setFlagGalacticGrid(bool)));

    object = findItem(settingsWindow, "CardinalPoints");
    object->setProperty("checked", lmgr->getFlagCardinalsPoints());
    QObject::connect(object, SIGNAL(triggered(bool)), lmgr, SLOT(setFlagCardinalsPoints(bool)));

    object = findItem(settingsWindow, "Meridian");
    object->setProperty("checked", glmgr->getFlagMeridianLine());
    QObject::connect(object, SIGNAL(triggered(bool)), glmgr, SLOT(setFlagMeridianLine(bool)));

    object = findItem(settingsWindow, "Ecliptic");
    object->setProperty("checked", glmgr->getFlagEclipticLine());
    QObject::connect(object, SIGNAL(triggered(bool)), glmgr, SLOT(setFlagEclipticLine(bool)));

    object = findItem(settingsWindow, "Equator");
    object->setProperty("checked", glmgr->getFlagEquatorLine());
    QObject::connect(object, SIGNAL(triggered(bool)), glmgr, SLOT(setFlagEquatorLine(bool)));

    object = findItem(settingsWindow, "Horizon");
    object->setProperty("checked", glmgr->getFlagHorizonLine());
    QObject::connect(object, SIGNAL(triggered(bool)), glmgr, SLOT(setFlagHorizonLine(bool)));

    object = findItem(settingsWindow, "GalacticPlane");
    object->setProperty("checked", glmgr->getFlagGalacticPlaneLine());
    QObject::connect(object, SIGNAL(triggered(bool)), glmgr, SLOT(setFlagGalacticPlaneLine(bool)));

    object = findItem(settingsWindow, "ShowConstellationLines");
    object->setProperty("checked", cmgr->getFlagLines());
    QObject::connect(object, SIGNAL(triggered(bool)), cmgr, SLOT(setFlagLines(bool)));

    object = findItem(settingsWindow, "ShowConstellationLabels");
    object->setProperty("checked", cmgr->getFlagLabels());
    QObject::connect(object, SIGNAL(triggered(bool)), cmgr, SLOT(setFlagLabels(bool)));

    object = findItem(settingsWindow, "ShowConstellationBoundaries");
    object->setProperty("checked", cmgr->getFlagBoundaries());
    QObject::connect(object, SIGNAL(triggered(bool)), cmgr, SLOT(setFlagBoundaries(bool)));

    object = findItem(settingsWindow, "ShowConstellationArt");
    object->setProperty("checked", cmgr->getFlagArt());
    QObject::connect(object, SIGNAL(triggered(bool)), cmgr, SLOT(setFlagArt(bool)));

    object = findItem(settingsWindow, "ArtBrightness");
    object->setProperty("value", (double) cmgr->getArtIntensity());
    QObject::connect(object, SIGNAL(valueChanged(double)), cmgr, SLOT(setArtIntensity(double)));


    // save current view options

    object = findItem(settingsWindow, "SaveCurrentViewOptions");
    QObject::connect(object, SIGNAL(clicked()), this, SLOT(saveCurrentViewOptions()));

    // Location List
    object = findItem(settingsWindow, "LocationListPage");
    QObject::connect(object, SIGNAL(searchTextChanged(QString)), this, SLOT(onLocationSearchTextChanged(QString)));
    QObject::connect(object, SIGNAL(searchTextEntered(QString, bool)), this, SLOT(onLocationSearchTextEntered(QString, bool)));


    object = findItem(settingsWindow, "LocationPage");
    QObject::connect(object, SIGNAL(locationChanged()), this, SLOT(onLocationChanged()));
    QObject::connect(object, SIGNAL(addLocationToList()), this, SLOT(addLocationToList()));
    QObject::connect(object, SIGNAL(deleteLocation()), this, SLOT(deleteLocation()));

    onLocationSearchTextChanged("");
    updateLocationInfo(core->getCurrentLocation());


    // Landscape
    object = findItem(settingsWindow, "ShowFog");
    object->setProperty("checked", lmgr->getFlagFog());
    QObject::connect(object, SIGNAL(triggered(bool)), lmgr, SLOT(setFlagFog(bool)));

    object = findItem(settingsWindow, "ShowGround");
    object->setProperty("checked", lmgr->getFlagLandscape());
    QObject::connect(object, SIGNAL(triggered(bool)), lmgr, SLOT(setFlagLandscape(bool)));

    object = findItem(settingsWindow, "LandscapeSetsLocation");
    object->setProperty("checked", lmgr->getFlagLandscapeSetsLocation());
    QObject::connect(object, SIGNAL(triggered(bool)), lmgr, SLOT(setFlagLandscapeSetsLocation(bool)));

    object = findItem(settingsWindow, "UseLandscapeAsDefault");
    object->setProperty("checked", lmgr->getCurrentLandscapeID()==lmgr->getDefaultLandscapeID());
    QObject::connect(object, SIGNAL(triggered(bool)), this, SLOT(setCurrentLandscapeAsDefault(bool)));

    object = findItem(settingsWindow, "LandscapePage");
    object->setProperty("description", lmgr->getCurrentLandscapeHtmlDescription());
    QObject::connect(object, SIGNAL(landscapeChanged(int)), this, SLOT(onLandscapeChanged(int)));


    object = findItem(settingsWindow, "DateTimePage");
    qmlDateTime = new StelQmlDateTime;
    qmlDateTime->init(object);

    object = findItem(settingsWindow, "MountTypeSelection");
    switch (mvmgr->getMountMode())
    {
    case StelMovementMgr::MountEquinoxEquatorial:
        object->setProperty("selectedIndex", 1);
        break;
    case StelMovementMgr::MountGalactic:
        object->setProperty("selectedIndex", 2);
        break;
    default:
        object->setProperty("selectedIndex", 0);
    }
    QObject::connect(object, SIGNAL(mountTypeChanged(int)), this, SLOT(mountTypeChanged(int)));


    StelSkyCultureMgr* scmgr = &StelApp::getInstance().getSkyCultureMgr();

    object = findItem(settingsWindow, "UseSkyCultureAsDefault");
    object->setProperty("checked", scmgr->getCurrentSkyCultureID() == scmgr->getDefaultSkyCultureID());
    QObject::connect(object, SIGNAL(triggered(bool)), this, SLOT(setCurrentSkyCultureAsDefault(bool)));

    object = findItem(settingsWindow, "SkyCulturePage");
    QObject::connect(object, SIGNAL(skyCultureChanged(int)), this, SLOT(onSkyCultureChanged(int)));


    QSettings* conf = StelApp::getInstance().getSettings();
    Q_ASSERT(conf);

    object = findItem(settingsWindow, "SettingsWindowBrightness");
    object->setProperty("value", conf->value("qmlgui/settings_window_brightness", 1.0));

    object = findItem(settingsWindow, "SettingsWindowShowStatus");
    object->setProperty("checked", conf->value("qmlgui/settings_window_show_status", true));

    populateLists();
}

void StelQmlGui::mountTypeChanged(int t)
{
    StelMovementMgr* mvmgr = GETSTELMODULE(StelMovementMgr);

    switch (t)
    {
    case 0:
        mvmgr->setMountMode(StelMovementMgr::MountAltAzimuthal);
        break;
    case 1:
        mvmgr->setMountMode(StelMovementMgr::MountEquinoxEquatorial);
        break;
    case 2:
        mvmgr->setMountMode(StelMovementMgr::MountGalactic);
        break;
    }
}

void StelQmlGui::setTimeNow()
{
    StelCore* core = StelApp::getInstance().getCore();
    core->setTimeNow();
    qmlDateTime->setDateTime(core->getJDay());

}

void StelQmlGui::setCurrentLandscapeAsDefault(bool b)
{
    if (!b)
        return;

    LandscapeMgr* lmgr = GETSTELMODULE(LandscapeMgr);
    Q_ASSERT(lmgr);
    lmgr->setDefaultLandscapeID(lmgr->getCurrentLandscapeID());

    QObject* object = findItem(settingsWindow, "UseLandscapeAsDefault");
    object->setProperty("checked", lmgr->getCurrentLandscapeID()==lmgr->getDefaultLandscapeID());
}

void StelQmlGui::setCurrentSkyCultureAsDefault(bool b)
{
    if (!b)
        return;

    StelSkyCultureMgr* scmgr = &StelApp::getInstance().getSkyCultureMgr();
    scmgr->setDefaultSkyCultureID(scmgr->getCurrentSkyCultureID());

    QObject* object = findItem(settingsWindow, "UseSkyCultureAsDefault");
    object->setProperty("checked", scmgr->getCurrentSkyCultureID() == scmgr->getDefaultSkyCultureID());
}


void StelQmlGui::setLightPollution(double v)
{
    int value = (int) v;
    LandscapeMgr* lmgr = GETSTELMODULE(LandscapeMgr);
    StelCore* core = StelApp::getInstance().getCore();

    lmgr->setAtmosphereBortleLightPollution(value);
    core->getSkyDrawer()->setBortleScale(value);
}

void StelQmlGui::setStarLabels(double v)
{
    StarMgr* smgr = GETSTELMODULE(StarMgr);
    smgr->setLabelsAmount((float) v);
}

void StelQmlGui::setPlanetLabels(double v)
{
    SolarSystem* ssmgr = GETSTELMODULE(SolarSystem);
    ssmgr->setLabelsAmount((float) v);
}

void StelQmlGui::setNebulaLabels(double v)
{
    NebulaMgr* nmgr = GETSTELMODULE(NebulaMgr);
    nmgr->setLabelsAmount((float) v);
    nmgr->setHintsAmount((float) v);

}

void StelQmlGui::connectItem(QDeclarativeItem* root_item, const char* signal_item, const char* signal, QObject* slot_object, const char* slot)
{
    QObject* signal_object = findItem(root_item, signal_item);
    if (signal_object)
    {
        QObject::connect(signal_object, signal, slot_object, slot);
    }
}

QObject* StelQmlGui::findItem(QDeclarativeItem* root_item, const char* id)
{
    QObject* object = root_item->findChild<QDeclarativeItem*>(id);
    if (object)
    {
        return object;
    }
    else
    {
        qDebug() << "Cannot find child item: " << id;
        return 0;
    }

}

StelQmlGui::~StelQmlGui()
{
    delete declEngine;
    delete qmlSearch;
    delete qmlDateTime;
    delete ef;
}

QString StelQmlGui::adjustPath(const QString &path)
{
#ifdef Q_OS_UNIX
#ifdef Q_OS_MAC
    if (!QDir::isAbsolutePath(path))
        return QString::fromLatin1("%1/../Resources/%2")
                .arg(QCoreApplication::applicationDirPath(), path);
#else
    const QString pathInInstallDir =
            QString::fromLatin1("%1/../%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(pathInInstallDir).exists())
        return pathInInstallDir;
#endif
#endif
    return path;
}


void StelQmlGui::showSettingsWindow()
{
    StelMainGraphicsView* view = &StelMainGraphicsView::getInstance();
    view->getTopLevelGraphicsWidget()->setVisible(false);
    view->getMainSkyItem()->setVisible(false);
    hud->setVisible(false);
    settingsWindow->setVisible(true);
}

void StelQmlGui::hideStartupPage()
{
    StelMainGraphicsView* view = &StelMainGraphicsView::getInstance();
    startupPage->setVisible(false);
    view->scene()->removeItem(startupPage);
}

void StelQmlGui::showHud()
{
    StelMainGraphicsView* view = &StelMainGraphicsView::getInstance();
    view->getTopLevelGraphicsWidget()->setVisible(true);
    view->getMainSkyItem()->setVisible(true);
    hud->setVisible(true);
    settingsWindow->setVisible(false);

}

void StelQmlGui::update()
{
    StelCore* core = StelApp::getInstance().getCore();

    hud->setProperty("timerate", (int) (core->getTimeRate() / StelCore::JD_SECOND));
    //qDebug() << core->getTimeRate();

    QString str;
    QTextStream wos(&str);
    wos << "FOV " << qSetRealNumberPrecision(2) << core->getMovementMgr()->getCurrentFov() << QChar(0x00B0);
    hud->setProperty("fov", str);

    QString str2;
    QTextStream wos2(&str2);
    wos2 << QString::number(StelApp::getInstance().getFps(), 'f', 0) << " FPS";
    hud->setProperty("fps", str2);

    double jd = core->getJDay();
    hud->setProperty("datetime", StelApp::getInstance().getLocaleMgr().getPrintableDateLocal(jd) + " " +
            StelApp::getInstance().getLocaleMgr().getPrintableTimeLocal(jd));

    hud->setProperty("location", core->getCurrentLocation().getID());

    qmlDateTime->setDateTime(core->getJDay());
}



void StelQmlGui::onObjectSearchTextChanged(const QString& text)
{
    QStringList matches;
    qmlSearch->updateSearchResults(text, matches);
    declEngine->rootContext()->setContextProperty("searchResults", QVariant::fromValue(matches));
}

void StelQmlGui::onObjectSearchTextEntered(const QString& text, bool recheck)
{
    QString search_text;
    if (recheck)
    {
        QStringList matches;
        qmlSearch->updateSearchResults(text, matches);

        if (matches.count() > 0)
           search_text = matches[0];
    }
    else
    {
        search_text = text;
    }

    if (qmlSearch->gotoObject(search_text))
    {
        showHud();
    }
}

void StelQmlGui::onLocationSearchTextChanged(const QString& text)
{
    // locations
    StelLocationMgr& locmgr = StelApp::getInstance().getLocationMgr();

    QStringList list;

    if (text.size() == 0)
    {
        list += locmgr.getModelAll()->stringList();
    }
    else
    {
        QRegExp rx("\\b" + text.toLower());
        rx.setCaseSensitivity(Qt::CaseInsensitive);
        list += locmgr.getModelAll()->stringList().filter(rx);
    }

    declEngine->rootContext()->setContextProperty("locations", QVariant::fromValue(list));

}

void StelQmlGui::onLocationSearchTextEntered(const QString &text, bool recheck)
{

    if (text.size() == 0)
        return;

    //qDebug() << text << " : " << recheck;

    StelLocationMgr& locmgr = StelApp::getInstance().getLocationMgr();


    QString locName;
    if (recheck)
    {
        QStringList list = locmgr.getModelAll()->stringList().filter(text, Qt::CaseInsensitive);
        if (list.count() == 0)
            return;
        locName = list[0];
    }
    else
    {
        locName = text;
    }


    //qDebug() << list.count() << " : " << list[0] << " : " << list[list.count()-1];

    StelLocation loc = locmgr.locationForSmallString(locName);
    StelApp::getInstance().getCore()->moveObserverTo(loc, 0.);

    updateLocationInfo(loc);

    SolarSystem* ssm = GETSTELMODULE(SolarSystem);
    PlanetP p = ssm->searchByEnglishName(loc.planetName);
    LandscapeMgr* ls = GETSTELMODULE(LandscapeMgr);
    ls->setFlagAtmosphere(p->hasAtmosphere());
    ls->setFlagFog(p->hasAtmosphere());

    QObject* object;
    object = findItem(settingsWindow, "ShowAtmosphere");
    object->setProperty("checked", ls->getFlagAtmosphere());

    object = findItem(settingsWindow, "ShowFog");
    object->setProperty("checked", ls->getFlagFog());


    object = findItem(settingsWindow, "LocationListPage");
    QMetaObject::invokeMethod(object, "close");


}

void StelQmlGui::updateLocationInfo(const StelLocation& loc)
{

    QObject* object = findItem(settingsWindow, "LocationPage");
    object->setProperty("longitude", loc.longitude);
    object->setProperty("latitude", loc.latitude);
    object->setProperty("name", loc.name);
    object->setProperty("country", loc.country);
    object->setProperty("planet", loc.planetName);
    object->setProperty("altitude", loc.altitude);
    object->setProperty("canDeleteLocation", StelApp::getInstance().getLocationMgr().canDeleteUserLocation(loc.getID()));
    object->setProperty("newLocation", false);

    if (false && loc.planetName=="Earth")
    {
        object->setProperty("terrainImage", QString(INSTALL_DATADIR) + "/data/gui/world.png");
    }
    else
    {
        SolarSystem* ssm = GETSTELMODULE(SolarSystem);
        PlanetP p = ssm->searchByEnglishName(loc.planetName);
        QString path;
        if (p)
        {
            try
            {
                path = StelFileMgr::findFile("textures/"+p->getTextMapName());
            }
            catch (std::runtime_error& e)
            {
                qWarning() << "ERROR - could not find planet map for " << loc.planetName << e.what();
                return;
            }
            object->setProperty("terrainImage", path);
        }
    }



}

void StelQmlGui::onLocationChanged()
{
    StelLocation loc = locationFromFields();
    StelApp::getInstance().getCore()->moveObserverTo(loc, 0.);

    QObject* object = findItem(settingsWindow, "LocationPage");
    object->setProperty("canDeleteLocation", StelApp::getInstance().getLocationMgr().canDeleteUserLocation(loc.getID()));

}

void StelQmlGui::saveCurrentViewOptions()
{
    QSettings* conf = StelApp::getInstance().getSettings();
    Q_ASSERT(conf);

    LandscapeMgr* lmgr = GETSTELMODULE(LandscapeMgr);
    Q_ASSERT(lmgr);
    SolarSystem* ssmgr = GETSTELMODULE(SolarSystem);
    Q_ASSERT(ssmgr);
    MeteorMgr* mmgr = GETSTELMODULE(MeteorMgr);
    Q_ASSERT(mmgr);
    StelSkyDrawer* skyd = StelApp::getInstance().getCore()->getSkyDrawer();
    Q_ASSERT(skyd);
    ConstellationMgr* cmgr = GETSTELMODULE(ConstellationMgr);
    Q_ASSERT(cmgr);
    StarMgr* smgr = GETSTELMODULE(StarMgr);
    Q_ASSERT(smgr);
    NebulaMgr* nmgr = GETSTELMODULE(NebulaMgr);
    Q_ASSERT(nmgr);
    GridLinesMgr* glmgr = GETSTELMODULE(GridLinesMgr);
    Q_ASSERT(glmgr);
    StelMovementMgr* mvmgr = GETSTELMODULE(StelMovementMgr);
    Q_ASSERT(mvmgr);

    StelCore* core = StelApp::getInstance().getCore();
    const StelProjectorP proj = core->getProjection(StelCore::FrameJ2000);
    Q_ASSERT(proj);

    StelGuiBase* gui = StelApp::getInstance().getGui();

    // view dialog / sky tab settings
    conf->setValue("stars/absolute_scale", skyd->getAbsoluteStarScale());
    conf->setValue("stars/relative_scale", skyd->getRelativeStarScale());
    conf->setValue("stars/flag_star_twinkle", skyd->getFlagTwinkle());
    conf->setValue("stars/star_twinkle_amount", skyd->getTwinkleAmount());
    conf->setValue("viewing/use_luminance_adaptation", skyd->getFlagLuminanceAdaptation());
    conf->setValue("astro/flag_planets", ssmgr->getFlagPlanets());
    conf->setValue("astro/flag_planets_hints", ssmgr->getFlagHints());
    conf->setValue("astro/flag_planets_orbits", ssmgr->getFlagOrbits());
    conf->setValue("astro/flag_light_travel_time", ssmgr->getFlagLightTravelTime());
    conf->setValue("viewing/flag_moon_scaled", ssmgr->getFlagMoonScale());
    conf->setValue("astro/meteor_rate", mmgr->getZHR());

    // view dialog / markings tab settings
    conf->setValue("viewing/flag_azimuthal_grid", glmgr->getFlagAzimuthalGrid());
    conf->setValue("viewing/flag_equatorial_grid", glmgr->getFlagEquatorGrid());
    conf->setValue("viewing/flag_equator_line", glmgr->getFlagEquatorLine());
    conf->setValue("viewing/flag_ecliptic_line", glmgr->getFlagEclipticLine());
    conf->setValue("viewing/flag_ecliptic_J2000_grid", glmgr->getFlagEclipticJ2000Grid());
    conf->setValue("viewing/flag_meridian_line", glmgr->getFlagMeridianLine());
    conf->setValue("viewing/flag_horizon_line", glmgr->getFlagHorizonLine());
    conf->setValue("viewing/flag_equatorial_J2000_grid", glmgr->getFlagEquatorJ2000Grid());
    conf->setValue("viewing/flag_galactic_grid", glmgr->getFlagGalacticGrid());
    conf->setValue("viewing/flag_galactic_plane_line", glmgr->getFlagGalacticPlaneLine());
    conf->setValue("viewing/flag_cardinal_points", lmgr->getFlagCardinalsPoints());
    conf->setValue("viewing/flag_constellation_drawing", cmgr->getFlagLines());
    conf->setValue("viewing/flag_constellation_name", cmgr->getFlagLabels());
    conf->setValue("viewing/flag_constellation_boundaries", cmgr->getFlagBoundaries());
    conf->setValue("viewing/flag_constellation_art", cmgr->getFlagArt());
    conf->setValue("viewing/flag_constellation_isolate_selected", cmgr->getFlagIsolateSelected());
    conf->setValue("viewing/constellation_art_intensity", cmgr->getArtIntensity());
    conf->setValue("viewing/flag_night", StelApp::getInstance().getVisionModeNight());
    conf->setValue("astro/flag_star_name", smgr->getFlagLabels());
    conf->setValue("stars/labels_amount", smgr->getLabelsAmount());
    conf->setValue("astro/flag_planets_labels", ssmgr->getFlagLabels());
    conf->setValue("astro/labels_amount", ssmgr->getLabelsAmount());
    conf->setValue("astro/nebula_hints_amount", nmgr->getHintsAmount());
    conf->setValue("astro/flag_nebula_name", nmgr->getFlagHints());
    conf->setValue("projection/type", core->getCurrentProjectionTypeKey());

    // view dialog / landscape tab settings
    lmgr->setDefaultLandscapeID(lmgr->getCurrentLandscapeID());
    conf->setValue("landscape/flag_landscape_sets_location", lmgr->getFlagLandscapeSetsLocation());
    conf->setValue("landscape/flag_landscape", lmgr->getFlagLandscape());
    conf->setValue("landscape/flag_atmosphere", lmgr->getFlagAtmosphere());
    conf->setValue("landscape/flag_fog", lmgr->getFlagFog());
    conf->setValue("stars/init_bortle_scale", core->getSkyDrawer()->getBortleScale());
        conf->setValue("landscape/atmospheric_extinction_coefficient", core->getSkyDrawer()->getExtinctionCoefficient());
        conf->setValue("landscape/pressure_mbar", core->getSkyDrawer()->getAtmospherePressure());
        conf->setValue("landscape/temperature_C", core->getSkyDrawer()->getAtmosphereTemperature());

    // view dialog / starlore tab
    StelApp::getInstance().getSkyCultureMgr().setDefaultSkyCultureID(StelApp::getInstance().getSkyCultureMgr().getCurrentSkyCultureID());

    // Save default location
    StelApp::getInstance().getCore()->setDefaultLocationID(core->getCurrentLocation().getID());

    // configuration dialog / main tab
    QString langName = StelApp::getInstance().getLocaleMgr().getAppLanguage();
    conf->setValue("localization/app_locale", StelTranslator::nativeNameToIso639_1Code(langName));
    langName = StelApp::getInstance().getLocaleMgr().getSkyLanguage();
    conf->setValue("localization/sky_locale", StelTranslator::nativeNameToIso639_1Code(langName));

    // configuration dialog / selected object info tab
    const StelObject::InfoStringGroup& flags = gui->getInfoTextFilters();
    if (flags == StelObject::InfoStringGroup(0))
        conf->setValue("gui/selected_object_info", "none");
    else if (flags == StelObject::InfoStringGroup(StelObject::ShortInfo))
        conf->setValue("gui/selected_object_info", "short");
    else if (flags == StelObject::InfoStringGroup(StelObject::AllInfo))
        conf->setValue("gui/selected_object_info", "all");
    else
    {
        conf->setValue("gui/selected_object_info", "custom");

        conf->beginGroup("custom_selected_info");
        conf->setValue("flag_show_name", (bool) (flags & StelObject::Name));
        conf->setValue("flag_show_catalognumber",
                       (bool) (flags & StelObject::CatalogNumber));
        conf->setValue("flag_show_magnitude",
                       (bool) (flags & StelObject::Magnitude));
        conf->setValue("flag_show_absolutemagnitude",
                       (bool) (flags & StelObject::AbsoluteMagnitude));
        conf->setValue("flag_show_radecj2000",
                       (bool) (flags & StelObject::RaDecJ2000));
        conf->setValue("flag_show_radecofdate",
                       (bool) (flags & StelObject::RaDecOfDate));
        conf->setValue("flag_show_hourangle",
                       (bool) (flags & StelObject::HourAngle));
        conf->setValue("flag_show_altaz",
                       (bool) (flags &  StelObject::AltAzi));
        conf->setValue("flag_show_distance",
                       (bool) (flags & StelObject::Distance));
        conf->setValue("flag_show_size",
                       (bool) (flags & StelObject::Size));
        conf->setValue("flag_show_extra1",
                       (bool) (flags & StelObject::Extra1));
        conf->setValue("flag_show_extra2",
                       (bool) (flags & StelObject::Extra2));
        conf->setValue("flag_show_extra3",
                       (bool) (flags & StelObject::Extra3));
        conf->endGroup();
    }


    mvmgr->setInitFov(mvmgr->getCurrentFov());
    mvmgr->setInitViewDirectionToCurrent();

    // configuration dialog / navigation tab
    conf->setValue("navigation/flag_enable_zoom_keys", mvmgr->getFlagEnableZoomKeys());
    conf->setValue("navigation/flag_enable_mouse_navigation", mvmgr->getFlagEnableMouseNavigation());
    conf->setValue("navigation/flag_enable_move_keys", mvmgr->getFlagEnableMoveKeys());
    conf->setValue("navigation/startup_time_mode", core->getStartupTimeMode());
    conf->setValue("navigation/today_time", core->getInitTodayTime());
    conf->setValue("navigation/preset_sky_time", core->getPresetSkyTime());
    conf->setValue("navigation/init_fov", mvmgr->getInitFov());
    if (mvmgr->getMountMode() == StelMovementMgr::MountAltAzimuthal)
        conf->setValue("navigation/viewing_mode", "horizon");
    else
        conf->setValue("navigation/viewing_mode", "equator");


    // configuration dialog / tools tab
    conf->setValue("video/viewport_effect", StelMainGraphicsView::getInstance().getStelAppGraphicsWidget()->getViewportEffect());
    conf->setValue("projection/viewport", StelProjector::maskTypeToString(proj->getMaskType()));
    conf->setValue("viewing/flag_gravity_labels", proj->getFlagGravityLabels());
    conf->setValue("navigation/auto_zoom_out_resets_direction", mvmgr->getFlagAutoZoomOutResetsDirection());
    conf->setValue("gui/flag_mouse_cursor_timeout", StelMainGraphicsView::getInstance().getFlagCursorTimeout());
    conf->setValue("gui/mouse_cursor_timeout", StelMainGraphicsView::getInstance().getCursorTimeout());

    conf->setValue("main/screenshot_dir", StelFileMgr::getScreenshotDir());
    conf->setValue("main/invert_screenshots_colors", StelMainGraphicsView::getInstance().getFlagInvertScreenShotColors());

    // full screen and window size
    conf->setValue("video/fullscreen", StelMainWindow::getInstance().getFullScreen());
    if (!StelMainWindow::getInstance().getFullScreen())
    {
        StelMainWindow& mainWindow = StelMainWindow::getInstance();
        conf->setValue("video/screen_w", mainWindow.size().width());
        conf->setValue("video/screen_h", mainWindow.size().height());
        conf->setValue("video/screen_x", mainWindow.x());
        conf->setValue("video/screen_y", mainWindow.y());
    }

    // clear the restore defaults flag if it is set.
    conf->setValue("main/restore_defaults", false);


    // save free look
    conf->setValue("projection/free_look", StelApp::getInstance().getCore()->getFreeLook());

    qmlHudSettings->saveCurrentViewOptions(conf);

    QObject* object;
    object = findItem(settingsWindow, "SettingsWindowBrightness");
    conf->setValue("qmlgui/settings_window_brightness", object->property("value"));

    object = findItem(settingsWindow, "SettingsWindowShowStatus");
    conf->setValue("qmlgui/settings_window_show_status", object->property("checked"));



}

void StelQmlGui::windowStateChanged(const QString& state)
{
    if (state == "Landscape")
    {
        StelApp::getInstance().getCore()->setPortraitMode(false);
    }
    else if (state == "Portrait")
    {
        StelApp::getInstance().getCore()->setPortraitMode(true);
    }
}


void StelQmlGui::populateLists()
{
    // Fill the projection list
//	l = ui->projectionListWidget;
//	l->blockSignals(true);
//	l->clear();
//	const QStringList mappings = core->getAllProjectionTypeKeys();
//	foreach (QString s, mappings)
//	{
//		l->addItem(core->projectionTypeKeyToNameI18n(s));
//	}
//	l->setCurrentItem(l->findItems(core->projectionTypeKeyToNameI18n(core->getCurrentProjectionTypeKey()), Qt::MatchExactly).at(0));
//	l->blockSignals(false);
//	ui->projectionTextBrowser->setHtml(core->getProjection(StelCore::FrameJ2000)->getHtmlSummary());

    // Fill the landscape list
    LandscapeMgr* lmgr = GETSTELMODULE(LandscapeMgr);
    QStringList landscapeList = lmgr->getAllLandscapeNames();

    declEngine->rootContext()->setContextProperty("landscapes", QVariant::fromValue(landscapeList));

    updateLandscapeInfo();

    // Sky cultures / starlore

    StelSkyCultureMgr* scmgr = &StelApp::getInstance().getSkyCultureMgr();
    QStringList skyCultures = scmgr->getSkyCultureListI18();
    declEngine->rootContext()->setContextProperty("skyCultures", QVariant::fromValue(skyCultures));

    updateSkyCultureInfo();
}

void StelQmlGui::updateLandscapeInfo()
{
    LandscapeMgr* lmgr = GETSTELMODULE(LandscapeMgr);

    QObject* object = findItem(settingsWindow, "UseLandscapeAsDefault");
    object->setProperty("checked", lmgr->getCurrentLandscapeID()==lmgr->getDefaultLandscapeID());

    object = findItem(settingsWindow, "LandscapePage");
    object->setProperty("description", lmgr->getCurrentLandscapeHtmlDescription());
    object->setProperty("landscapeName", lmgr->getCurrentLandscapeName());
}

void StelQmlGui::updateSkyCultureInfo()
{
    StelSkyCultureMgr* scmgr = &StelApp::getInstance().getSkyCultureMgr();

    QObject* object = findItem(settingsWindow, "UseSkyCultureAsDefault");
    object->setProperty("checked", scmgr->getCurrentSkyCultureID() == scmgr->getDefaultSkyCultureID());

    object = findItem(settingsWindow, "SkyCulturePage");


    // find description path

    StelApp& app = StelApp::getInstance();
    QString skyCultureId = app.getSkyCultureMgr().getCurrentSkyCultureID();
    QString descPath;
    try
    {
        QString lang = app.getLocaleMgr().getAppLanguage();
        if (!QString("pt_BR zh_CN zh_HK zh_TW").contains(lang))
        {
            lang = lang.split("_").at(0);
        }
        descPath = StelFileMgr::findFile("skycultures/" + skyCultureId + "/description."+lang+".utf8");
    }
    catch (std::runtime_error& e)
    {
        try
        {
            descPath = StelFileMgr::findFile("skycultures/" + skyCultureId + "/description.en.utf8");
        }
        catch (std::runtime_error& e)
        {
            qWarning() << "WARNING: can't find description for skyculture" << skyCultureId;
        }
    }

    QStringList searchPaths;
    try
    {
        searchPaths << StelFileMgr::findFile("skycultures/" + skyCultureId);
    }
    catch (std::runtime_error& e) {}

    if (descPath.isEmpty())
    {
        object->setProperty("htmlFile", "No description");
    }
    else
    {
        QFile f(descPath);
        f.open(QIODevice::ReadOnly);
        QString htmlFile = QString::fromUtf8(f.readAll());

        QString path = QFileInfo(f).path();
        QString newtag = "<img src=\"file://" + path + "/\\1";
        htmlFile.replace(QRegExp("<img src=\"(\\w)"), newtag);

        object->setProperty("htmlFile", htmlFile);

        //qDebug() << "Setting: " << htmlFile << "   ";
    }

    object->setProperty("skyCultureName", scmgr->getCurrentSkyCultureNameI18());

}



void StelQmlGui::onLandscapeChanged(int index)
{
    const StelCore* core = StelApp::getInstance().getCore();

    LandscapeMgr* lmgr = GETSTELMODULE(LandscapeMgr);
    QStringList landscapeList = lmgr->getAllLandscapeNames();

    if (index >= landscapeList.size() || index < 0)
        return;

    lmgr->setCurrentLandscapeName(landscapeList[index]);

    updateLandscapeInfo();
    updateLocationInfo(core->getCurrentLocation());

    QObject* object;

    object = findItem(settingsWindow, "ShowFog");
    object->setProperty("checked", lmgr->getFlagFog());

    object = findItem(settingsWindow, "LightPollution");
    object->setProperty("value", (double) core->getSkyDrawer()->getBortleScale());

}

void StelQmlGui::onSkyCultureChanged(int index)
{
    StelSkyCultureMgr* scmgr = &StelApp::getInstance().getSkyCultureMgr();

    QStringList skyCultureList = scmgr->getSkyCultureListI18();

    if (index >= skyCultureList.size() || index < 0)
        return;

    scmgr->setCurrentSkyCultureNameI18(skyCultureList[index]);

    updateSkyCultureInfo();

}

QDeclarativeItem* StelQmlGui::createComponent(const QString& path)
{
    QDeclarativeComponent component(declEngine, QUrl::fromLocalFile(adjustPath(path)));
    QDeclarativeItem* item = qobject_cast<QDeclarativeItem *>(component.create());
    if (component.isError())
        qDebug() << component.errors();

    return item;
}

void StelQmlGui::unselect()
{
    StelApp::getInstance().getStelObjectMgr().unSelect();
}

void StelQmlGui::addLocationToList()
{
    StelLocation loc = locationFromFields();
    StelApp::getInstance().getLocationMgr().saveUserLocation(loc);
}

void StelQmlGui::deleteLocation()
{
    StelLocation loc = locationFromFields();
    StelApp::getInstance().getLocationMgr().deleteUserLocation(loc.getID());
}

StelLocation StelQmlGui::locationFromFields()
{
    QObject* object = findItem(settingsWindow, "LocationPage");
    StelLocation loc;
    loc.name = object->property("name").toString();
    loc.country = object->property("country").toString();
    loc.planetName = object->property("planet").toString();
    loc.altitude = object->property("altitude").toInt();
    loc.longitude = object->property("longitude").toFloat();
    loc.latitude = object->property("latitude").toFloat();
    return loc;
}

