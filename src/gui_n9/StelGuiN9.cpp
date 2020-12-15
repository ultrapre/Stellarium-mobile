/*
 * Stellarium
 * Copyright (C) 2008 Fabien Chereau
 * Copyright (C) 2012 Timothy Reaves
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

#include "StelGuiN9.hpp"
#include "StelGuiItems.hpp"
#include "SkyGuiN9.hpp"
#include "StelApp.hpp"
#include "StelCore.hpp"
#include "StelProjector.hpp"
#include "StelMovementMgr.hpp"
#include "StelFileMgr.hpp"
#include "StelModuleMgr.hpp"
#include "StelMainGraphicsView.hpp"
#include "StelMainWindow.hpp"
#include "StelObjectMgr.hpp"
#include "LandscapeMgr.hpp"
#include "StarMgr.hpp"
#include "ConstellationMgr.hpp"
#include "GridLinesMgr.hpp"
#include "NebulaMgr.hpp"
#include "StelLocaleMgr.hpp"

#include "StelObjectType.hpp"
#include "StelObject.hpp"
#include "StelProjector.hpp"
#include "SolarSystem.hpp"
#include "StelSkyLayerMgr.hpp"
#include "StelStyle.hpp"
#include "StelSkyDrawer.hpp"
#include "MeteorMgr.hpp"
#ifdef ENABLE_SCRIPT_CONSOLE
#include "ScriptConsole.hpp"
#endif
#ifndef DISABLE_SCRIPTING
#include "StelScriptMgr.hpp"
#endif
#include "StelAppGraphicsWidget.hpp"

#include "ConfigurationDialog.hpp"
#include "DateTimeDialog.hpp"
#include "HelpDialog.hpp"
#include "LocationDialog.hpp"
#include "SearchDialog.hpp"
#include "ViewDialog.hpp"


#include <QDebug>
#include <QTimeLine>
#include <QFontDatabase>
#include <QMouseEvent>
#include <QAction>
#include <QApplication>
#include <QFile>
#include <QTextBrowser>
#include <QGraphicsWidget>
#include <QGraphicsGridLayout>
#include <QClipboard>
#include <QPalette>
#include <QColor>



StelGuiN9::StelGuiN9() :
    topLevelGraphicsWidget(NULL),
#ifdef ENABLE_SCRIPT_CONSOLE
    scriptConsole(0),
#endif
    initDone(false),
    frameNo(0)
{
}

StelGuiN9::~StelGuiN9()
{
    delete skyGui;
    skyGui = NULL;

    // configurationDialog is automatically deleted with its parent widget.
#ifdef ENABLE_SCRIPT_CONSOLE
    if (scriptConsole)
    {
        delete scriptConsole;
        scriptConsole = 0;
    }
#endif
}

void StelGuiN9::init(QGraphicsWidget* atopLevelGraphicsWidget, StelAppGraphicsWidget* astelAppGraphicsWidget)
{
    qDebug() << "Creating N9 GUI ...";

    StelGuiBase::init(atopLevelGraphicsWidget, astelAppGraphicsWidget);

    StelObjectMgr* omgr = GETSTELMODULE(StelObjectMgr);
    QObject::connect(omgr, SIGNAL(selectedObjectChanged(StelModule::StelModuleSelectAction)), this, SLOT(onSelectedObjectChanged(StelModule::StelModuleSelectAction)));


    skyGui = new SkyGuiN9(atopLevelGraphicsWidget);

#ifdef ENABLE_SCRIPT_CONSOLE
    scriptConsole = new ScriptConsole();
#endif


    ///////////////////////////////////////////////////////////////////////
    // Create the main base widget
    skyGui->init(this);
    QGraphicsGridLayout* l = new QGraphicsGridLayout();
    l->setContentsMargins(0,0,0,0);
    l->setSpacing(0);
    l->addItem(skyGui, 0, 0);
    stelAppGraphicsWidget->setLayout(l);

    setStelStyle(StelApp::getInstance().getCurrentStelStyle());

    skyGui->setGeometry(stelAppGraphicsWidget->geometry());
    skyGui->updateBarsPos();

    // The disabled text for checkboxes is embossed with the QPalette::Light setting for the ColorGroup Disabled.
    // It doesn't appear to be possible to set this from the stylesheet.  Instead we'll make it 100% transparent
    // and set the text color for disabled in the stylesheets.
    QPalette p = QApplication::palette();
    p.setColor(QPalette::Disabled, QPalette::Light, QColor(0,0,0,0));

    // And this is for the focus...  apparently the focus indicator is the inverted value for Active/Button.
    p.setColor(QPalette::Active, QPalette::Button, QColor(255,255,255));
    QApplication::setPalette(p);

    StelApp *app = &StelApp::getInstance();
    connect(app, SIGNAL(languageChanged()), this, SLOT(updateI18n()));
    connect(app, SIGNAL(colorSchemeChanged(const QString&)), this, SLOT(setStelStyle(const QString&)));

    StelCore* core = StelApp::getInstance().getCore();
    orientationChanged(core->getPortraitMode());
    initDone = true;
}


void StelGuiN9::quit()
{
    #ifndef DISABLE_SCRIPTING
    StelMainGraphicsView::getInstance().getScriptMgr().stopScript();
    #endif
    QCoreApplication::exit();
}

//! Reload the current Qt Style Sheet (Debug only)
void StelGuiN9::reloadStyle()
{
    setStelStyle(StelApp::getInstance().getCurrentStelStyle());
}

//! Load color scheme from the given ini file and section name
void StelGuiN9::setStelStyle(const QString& section)
{
    if (currentStelStyle.confSectionName!=section)
    {
        // Load the style sheets
        currentStelStyle.confSectionName = section;

        QString qtStyleFileName;
        QString htmlStyleFileName;

        if (section=="night_color")
        {
            qtStyleFileName = ":/graphicGui/nightStyle.css";
            htmlStyleFileName = ":/graphicGui/nightHtml.css";
        }
        else if (section=="color")
        {
            qtStyleFileName = ":/graphicGui/normalStyle.css";
            htmlStyleFileName = ":/graphicGui/normalHtml.css";
        }

        // Load Qt style sheet
        QFile styleFile(qtStyleFileName);
        styleFile.open(QIODevice::ReadOnly);
        currentStelStyle.qtStyleSheet = styleFile.readAll();

        QFile htmlStyleFile(htmlStyleFileName);
        htmlStyleFile.open(QIODevice::ReadOnly);
        currentStelStyle.htmlStyleSheet = htmlStyleFile.readAll();
    }
    qApp->setStyleSheet(currentStelStyle.qtStyleSheet);


#ifdef ENABLE_SCRIPT_CONSOLE
    scriptConsole->styleChanged();
#endif // ENABLE_SCRIPT_CONSOLE
}


void StelGuiN9::updateI18n()
{
    StelGuiBase::updateI18n();
}

void StelGuiN9::update()
{
    frameNo++;
    if (frameNo % 10 == 0)
    {
        //skyGui->infoPanel->setTextFromObjects(GETSTELMODULE(StelObjectMgr)->getSelectedObject());
        skyGui->infoPanel->setQmlLabelFromObjects(GETSTELMODULE(StelObjectMgr)->getSelectedObject());
    }

    // Check if the progressbar window changed, if yes update the whole view
    if (savedProgressBarSize!=skyGui->progressBarMgr->boundingRect().size())
    {
        savedProgressBarSize=skyGui->progressBarMgr->boundingRect().size();
        skyGui->updateBarsPos();
    }
}

void StelGuiN9::onSelectedObjectChanged(StelModule::StelModuleSelectAction)
{
    skyGui->infoPanel->setQmlLabelFromObjects(GETSTELMODULE(StelObjectMgr)->getSelectedObject());
}

// Add a new progress bar in the lower right corner of the screen.
QProgressBar* StelGuiN9::addProgressBar()
{
    return skyGui->progressBarMgr->addProgressBar();
}

#ifndef DISABLE_SCRIPTING
void StelGuiN9::setScriptKeys(bool b)
{
//    if (b)
//    {
//        getGuiActions("actionDecrease_Time_Speed")->setShortcut(QKeySequence());
//        getGuiActions("actionIncrease_Time_Speed")->setShortcut(QKeySequence());
//        getGuiActions("actionSet_Real_Time_Speed")->setShortcut(QKeySequence());
//        getGuiActions("actionDecrease_Script_Speed")->setShortcut(QKeySequence("J"));
//        getGuiActions("actionIncrease_Script_Speed")->setShortcut(QKeySequence("L"));
//        getGuiActions("actionSet_Real_Script_Speed")->setShortcut(QKeySequence("K"));

//        getGuiActions("actionStop_Script")->setShortcut(QKeySequence("4"));
//        getGuiActions("actionPause_Script")->setShortcut(QKeySequence("5"));
//        getGuiActions("actionResume_Script")->setShortcut(QKeySequence("6"));
//    }
//    else
//    {
//        getGuiActions("actionDecrease_Script_Speed")->setShortcut(QKeySequence());
//        getGuiActions("actionIncrease_Script_Speed")->setShortcut(QKeySequence());
//        getGuiActions("actionSet_Real_Script_Speed")->setShortcut(QKeySequence());
//        getGuiActions("actionDecrease_Time_Speed")->setShortcut(QKeySequence("J"));
//        getGuiActions("actionIncrease_Time_Speed")->setShortcut(QKeySequence("L"));
//        getGuiActions("actionSet_Real_Time_Speed")->setShortcut(QKeySequence("K"));
//    }
}

void StelGuiN9::increaseScriptSpeed()
{
    StelMainGraphicsView::getInstance().getScriptMgr().setScriptRate(StelMainGraphicsView::getInstance().getScriptMgr().getScriptRate()*2);
}

void StelGuiN9::decreaseScriptSpeed()
{
    StelMainGraphicsView::getInstance().getScriptMgr().setScriptRate(StelMainGraphicsView::getInstance().getScriptMgr().getScriptRate()/2);
}

void StelGuiN9::setRealScriptSpeed()
{
    StelMainGraphicsView::getInstance().getScriptMgr().setScriptRate(1);
}

void StelGuiN9::stopScript()
{
    StelMainGraphicsView::getInstance().getScriptMgr().stopScript();
}

void StelGuiN9::pauseScript()
{
    StelMainGraphicsView::getInstance().getScriptMgr().pauseScript();
}

void StelGuiN9::resumeScript()
{
    StelMainGraphicsView::getInstance().getScriptMgr().resumeScript();
}
#endif


void StelGuiN9::setVisible(bool b)
{
    skyGui->setVisible(b);
}

bool StelGuiN9::getVisible() const
{
    return skyGui->isVisible();
}

bool StelGuiN9::isCurrentlyUsed() const
{
    return false;
    //return skyGui->buttonBar->isUnderMouse() || skyGui->winBar->isUnderMouse();
}


void StelGuiN9::setInfoTextFilters(const StelObject::InfoStringGroup& aflags)
{
    skyGui->infoPanel->setInfoTextFilters(aflags);
}

const StelObject::InfoStringGroup& StelGuiN9::getInfoTextFilters() const
{
    return skyGui->infoPanel->getInfoTextFilters();
}


SkyGuiN9* StelGuiN9::getSkyGui() const
{
    return skyGui;
}

bool StelGuiN9::initComplete(void) const
{
    return initDone;
}

void StelGuiN9::forceRefreshGui()
{
  skyGui->updateBarsPos();
}

#ifndef DISABLE_SCRIPTING
void StelGuiN9::scriptStarted()
{
    //setScriptKeys(true);
}

void StelGuiN9::scriptStopped()
{
    //setScriptKeys(false);
}
#endif

void StelGuiN9::setGuiVisible(bool b)
{
    setVisible(b);
}

QAction* StelGuiN9::addGuiActions(const QString& actionName, const QString& text, const QString& shortCut, const QString& helpGroup, bool checkable, bool autoRepeat, bool global)
{
//    if (!shortCut.isEmpty())
//        helpDialog->setKey(helpGroup, "", shortCut, text);
    return StelGuiBase::addGuiActions(actionName, text, shortCut, helpGroup, checkable, autoRepeat, global);
}


void StelGuiN9::copySelectedObjectInfo(void)
{
    QApplication::clipboard()->setText(skyGui->infoPanel->getSelectedText());
}

void StelGuiN9::orientationChanged(bool portraitMode)
{
    StelCore* core = StelApp::getInstance().getCore();
    if (portraitMode && skyGui && skyGui->infoPanel)
    {
        skyGui->infoPanel->setRotation(270.);
        skyGui->infoPanel->setPos(8, core->getProjection2d()->getViewportHeight() - 8);
    }
    else
    {
        skyGui->infoPanel->setRotation(0.);
        skyGui->infoPanel->setPos(8, 8);
    }
}
