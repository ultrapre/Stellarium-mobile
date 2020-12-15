/*
 * Stellarium
 * Copyright (C) 2008 Fabien Chereau
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

#ifndef _STELGUIN9_HPP_
#define _STELGUIN9_HPP_

#include "StelModule.hpp"
#include "StelObject.hpp"
#include "StelGuiBase.hpp"
#include "StelStyle.hpp"



#include <QGraphicsTextItem>


class InfoPanelN9;

#ifdef ENABLE_SCRIPT_CONSOLE
class ScriptConsole;
#endif

//! @class StelGuiN9
//! Main class for the GUI based on QGraphicView.
//! It manages the various qt configuration windows, the buttons bars, the list of QAction/shortcuts.
class StelGuiN9 : public QObject, public StelGuiBase
{
    Q_OBJECT
public:


    StelGuiN9();
    virtual ~StelGuiN9();

    ///////////////////////////////////////////////////////////////////////////
    // Methods defined in the StelModule class
    //! Initialize the StelGuiN9 object.
    virtual void init(QGraphicsWidget* topLevelGraphicsWidget, StelAppGraphicsWidget* stelAppGraphicsWidget);
    void update();


    //! Add a new progress bar in the lower right corner of the screen.
    //! When the progress bar is deleted with removeProgressBar() the layout is automatically rearranged.
    //! @return a pointer to the progress bar
    class QProgressBar* addProgressBar();

    //! Get the SkyGuiN9 instance (useful for adding other interface elements).
    //! It will return a valid object only if called after init().
    class SkyGuiN9* getSkyGui() const;

    //! returns true if the gui has complted init process.
    bool initComplete(void) const;

#ifdef ENABLE_SCRIPT_CONSOLE
    ScriptConsole* getScriptConsole() {return scriptConsole;}
#endif

    //! Used to force a refreshing of the GUI elements such as the button bars.
    virtual void forceRefreshGui();

    virtual void setVisible(bool b);

    virtual bool getVisible() const;

    virtual bool isCurrentlyUsed() const;

    virtual void setInfoTextFilters(const StelObject::InfoStringGroup& aflags);
    virtual const StelObject::InfoStringGroup& getInfoTextFilters() const;

    virtual QAction* addGuiActions(const QString& actionName,
                                     const QString& text,
                                     const QString& shortCut,
                                     const QString& helpGroup,
                                     bool checkable=true,
                                     bool autoRepeat=false,
                                     bool global = false);

    virtual void orientationChanged(bool portraitMode);

    void setGuiVisible(bool b);

    void copySelectedObjectInfo(void);
public slots:

    void onSelectedObjectChanged(StelModule::StelModuleSelectAction);

    #ifndef DISABLE_SCRIPTING
    //! change keys when a script is running / not running
    void setScriptKeys(bool b);
    void increaseScriptSpeed();
    void decreaseScriptSpeed();
    void setRealScriptSpeed();
    void stopScript();
    void pauseScript();
    void resumeScript();
    #endif

private slots:

    void quit();

    #ifndef DISABLE_SCRIPTING
    void scriptStarted();
    void scriptStopped();
    #endif
    //! Load color scheme from the given ini file and section name
    void setStelStyle(const QString& section);

    void updateI18n();
    //! Process changes from the ConstellationMgr


private:
    void reloadStyle();

    QGraphicsWidget* topLevelGraphicsWidget;

    class SkyGuiN9* skyGui;

#ifdef ENABLE_SCRIPT_CONSOLE
    ScriptConsole* scriptConsole;
#endif

    bool initDone;
    bool guiHidden;
    unsigned int frameNo;

    QSizeF savedProgressBarSize;

    // Currently used StelStyle
    StelStyle currentStelStyle;

};


#endif // _STELGUIN9_HPP_
