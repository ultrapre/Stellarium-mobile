#ifndef STELQMLHUDSETTINGS_HPP
#define STELQMLHUDSETTINGS_HPP


#include "StelQmlGui.hpp"

#include <QObject>


class StelQmlHudSettings : public QObject
{
    Q_OBJECT
public:
    explicit StelQmlHudSettings(StelQmlGui*);

    void saveCurrentViewOptions(class QSettings*);

signals:
    
public slots:

    void setLocationVisible(bool v) { qmlGui->getHud()->setProperty("locationVisible", v); }
    void setDatetimeVisible(bool v) { qmlGui->getHud()->setProperty("datetimeVisible", v); }
    void setTimerateVisible(bool v) { qmlGui->getHud()->setProperty("timerateVisible", v); }
    void setFovVisible(bool v) { qmlGui->getHud()->setProperty("fovVisible", v); }
    void setFpsVisible(bool v) { qmlGui->getHud()->setProperty("fpsVisible", v); }
    void setButtonsVisible(bool v) { qmlGui->getHud()->setProperty("buttonsVisible", v); }
    void setDisableScreensaver(bool v) { qmlGui->getHud()->setProperty("disableScreensaver", v); }
    void setTransparency(double t) { qmlGui->getHud()->setProperty("transparency", t); }
    void setInfoTransparency(double t) { qmlGui->getHud()->setProperty("infoTransparency", t); }



private:

    StelQmlGui* qmlGui;
    
};

#endif // STELQMLHUDSETTINGS_HPP
