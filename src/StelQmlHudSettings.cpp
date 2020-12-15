#include "StelQmlHudSettings.hpp"
#include "StelApp.hpp"

#include <QSettings>

StelQmlHudSettings::StelQmlHudSettings(StelQmlGui* qg) :
    QObject(qg)
{

    qmlGui = qg;

    QSettings* conf = StelApp::getInstance().getSettings();

    QObject* object;
    bool v;


    v = conf->value("qmlgui/show_location", true).toBool();
    setLocationVisible(v);
    object = qmlGui->findItemSettingsWindow("HudShowLocation");
    object->setProperty("checked", v);
    QObject::connect(object, SIGNAL(triggered(bool)), this, SLOT(setLocationVisible(bool)));

    v = conf->value("qmlgui/show_datetime", true).toBool();
    setDatetimeVisible(v);
    object = qmlGui->findItemSettingsWindow("HudShowDatetime");
    object->setProperty("checked", v);
    QObject::connect(object, SIGNAL(triggered(bool)), this, SLOT(setDatetimeVisible(bool)));

    v = conf->value("qmlgui/show_timerate", true).toBool();
    setTimerateVisible(v);
    object = qmlGui->findItemSettingsWindow("HudShowTimerate");
    object->setProperty("checked", v);
    QObject::connect(object, SIGNAL(triggered(bool)), this, SLOT(setTimerateVisible(bool)));

    v = conf->value("qmlgui/show_fps", true).toBool();
    setFpsVisible(v);
    object = qmlGui->findItemSettingsWindow("HudShowFps");
    object->setProperty("checked", v);
    QObject::connect(object, SIGNAL(triggered(bool)), this, SLOT(setFpsVisible(bool)));

    v = conf->value("qmlgui/show_fov", true).toBool();
    setFovVisible(v);
    object = qmlGui->findItemSettingsWindow("HudShowFov");
    object->setProperty("checked", v);
    QObject::connect(object, SIGNAL(triggered(bool)), this, SLOT(setFovVisible(bool)));

    v = conf->value("qmlgui/show_buttons", true).toBool();
    setButtonsVisible(v);
    object = qmlGui->findItemSettingsWindow("HudShowButtons");
    object->setProperty("checked", v);
    QObject::connect(object, SIGNAL(triggered(bool)), this, SLOT(setButtonsVisible(bool)));

    v = conf->value("qmlgui/disable_screensaver", false).toBool();
    setDisableScreensaver(v);
    object = qmlGui->findItemSettingsWindow("HudDisableScreensaver");
    object->setProperty("checked", v);
    QObject::connect(object, SIGNAL(triggered(bool)), this, SLOT(setDisableScreensaver(bool)));

    object = qmlGui->findItemSettingsWindow("HudNightVisionMode");
    object->setProperty("checked", StelApp::getInstance().getVisionModeNight());
    QObject::connect(object, SIGNAL(triggered(bool)), &StelApp::getInstance(), SLOT(setVisionModeNight(bool)));


    double t = conf->value("qmlgui/transparency", 0.4).toDouble();
    setTransparency(t);
    object = qmlGui->findItemSettingsWindow("HudTransparency");
    object->setProperty("value", t);
    QObject::connect(object, SIGNAL(valueChanged(double)), this, SLOT(setTransparency(double)));

    t = conf->value("qmlgui/info_transparency", 0.).toDouble();
    setInfoTransparency(t);
    object = qmlGui->findItemSettingsWindow("HudInfoTransparency");
    object->setProperty("value", t);
    QObject::connect(object, SIGNAL(valueChanged(double)), this, SLOT(setInfoTransparency(double)));

}

void StelQmlHudSettings::saveCurrentViewOptions(QSettings* conf)
{
    QObject* object;

    object = qmlGui->findItemSettingsWindow("HudShowLocation");
    conf->setValue("qmlgui/show_location", object->property("checked").toBool());

    object = qmlGui->findItemSettingsWindow("HudShowDatetime");
    conf->setValue("qmlgui/show_datetime", object->property("checked").toBool());

    object = qmlGui->findItemSettingsWindow("HudShowTimerate");
    conf->setValue("qmlgui/show_timerate", object->property("checked").toBool());

    object = qmlGui->findItemSettingsWindow("HudShowFps");
    conf->setValue("qmlgui/show_fps", object->property("checked").toBool());

    object = qmlGui->findItemSettingsWindow("HudShowFov");
    conf->setValue("qmlgui/show_fov", object->property("checked").toBool());

    object = qmlGui->findItemSettingsWindow("HudShowButtons");
    conf->setValue("qmlgui/show_buttons", object->property("checked").toBool());

    object = qmlGui->findItemSettingsWindow("HudDisableScreensaver");
    conf->setValue("qmlgui/disable_screensaver", object->property("checked").toBool());

    object = qmlGui->findItemSettingsWindow("HudTransparency");
    conf->setValue("qmlgui/transparency", object->property("value").toDouble());

    object = qmlGui->findItemSettingsWindow("HudInfoTransparency");
    conf->setValue("qmlgui/info_transparency", object->property("value").toDouble());

}


