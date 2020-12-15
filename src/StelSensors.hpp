#ifndef STELSENSORS_HPP
#define STELSENSORS_HPP

#include <QAccelerometer>
#include <QMagnetometer>
#include <QRotationSensor>

#include "StelQuaternion.hpp"
#include "VecMath.hpp"

class StelSensors : public QObject
{
    Q_OBJECT

public:
    explicit StelSensors(QObject *parent = 0);

    Mat4d calcMatrix();

    void startSensors();
    void stopSensors();

    bool getEnabled() const { return enabled; }

private:

    QtMobility::QAccelerometer* accelSensor;
    QtMobility::QMagnetometer* magSensor;

    Quat rotation;
    Vec3 angVel;

    friend class AccelFilter;

    bool firstMeasurement;
    bool enabled;

};


class AccelFilter : public QObject, public QtMobility::QAccelerometerFilter
{
    Q_OBJECT
public:

    explicit AccelFilter(StelSensors* s);
    virtual bool filter(QtMobility::QAccelerometerReading * reading );

private:


    static inline Quat q_dot2(const Quat& q, const Quat& q_dot, const Quat& w_dot)
    {
        return q_dot * q.conj() * q_dot + q * w_dot * 0.5;
    }

    StelSensors* sensors;
    unsigned int frameNo;

};


#endif
