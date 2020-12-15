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

#ifndef STELQMLGUI_HPP
#define STELQMLGUI_HPP

#include <QGraphicsScene>
#include <QGraphicsObject>
//#include <QtQuickItem>
#include <QQuickItem>
//#include <QQuickEngine>

#include <QObject>

#include "StelLocation.hpp"

class StelQmlGui : public QObject
{
Q_OBJECT

public:

    //StelQmlGui(class StelCore*);
    StelQmlGui();
    ~StelQmlGui();

    void init();

    QString adjustPath(const QString &path);



    void update();

public slots:

    QString version() const { return STELN9_VERSION; }
    QString versionOriginal() const { return PACKAGE_VERSION; }
    QString dataDir() const { return INSTALL_DATADIR; }

    void showSettingsWindow();
    void showHud();
    void hideStartupPage();

    QObject* getInfoTextLabel() const { return infoTextLabel; }
    QObject* getNameLabel() const { return nameLabel; }

    QObject* findItemHud(const char* id) { return findItem(hud, id); }

    QObject* findItemSettingsWindow(const char* id) { return findItem(settingsWindow, id); }

    QDeclarativeItem* getHud() { return hud; }

protected:

    void connectItem(QDeclarativeItem* root_item, const char* signal_item, const char* signal, QObject* slot_object, const char* slot);

    QObject* findItem(QDeclarativeItem* root_item, const char* id);

private slots:

    void setCurrentLandscapeAsDefault(bool b);
    void setCurrentSkyCultureAsDefault(bool b);
    void setLightPollution(double v);
    void setStarLabels(double v);
    void setPlanetLabels(double v);
    void setNebulaLabels(double v);

    void onObjectSearchTextChanged(const QString& text);
    void onObjectSearchTextEntered(const QString& text, bool recheck);

    void saveCurrentViewOptions();
    void onLocationSearchTextChanged(const QString& text);
    void onLocationSearchTextEntered(const QString& text, bool recheck);
    void windowStateChanged(const QString& state);
    void onLocationChanged();
    void mountTypeChanged(int t);

    void onLandscapeChanged(int index);
    void onSkyCultureChanged(int index);

    void setTimeNow();
    void unselect();


    void addLocationToList();
    void deleteLocation();

private:

    StelLocation locationFromFields();

    void populateLists();
    void updateLocationInfo(const StelLocation& loc);
    void updateSkyCultureInfo();
    void updateLandscapeInfo();

    QDeclarativeItem* hud;
    QDeclarativeItem* settingsWindow;
    QDeclarativeItem* startupPage;
    QDeclarativeEngine* declEngine;

    QObject* infoTextLabel;
    QObject* nameLabel;

    class StelQmlHudSettings* qmlHudSettings;

    QDeclarativeItem* createComponent(const QString& path);

    class EventFilter* ef;
    class StelQmlSearch* qmlSearch;
    class StelQmlDateTime* qmlDateTime;
};

#endif // STELQMLGUI_HPP
