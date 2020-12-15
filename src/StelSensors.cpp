#include "StelSensors.hpp"
#include "StelQuaternion.hpp"
#include "StelMovementMgr.hpp"
#include "StelApp.hpp"
#include "StelModuleMgr.hpp"

#include <QMagnetometer>

#include <QDebug>>



StelSensors::StelSensors(QObject *parent) :
    QObject(parent), enabled(false), firstMeasurement(true)
{

    magSensor = new QtMobility::QMagnetometer(this);
    magSensor->setProperty("returnGeoValues", true);
    magSensor->setDataRate(40);

    accelSensor = new QtMobility::QAccelerometer(this);
    accelSensor->setDataRate(40);
    accelSensor->addFilter(new AccelFilter(this));

}



AccelFilter::AccelFilter(StelSensors* s) :
    QObject(s), sensors(s), frameNo(0)
{
}

bool AccelFilter::filter(QtMobility::QAccelerometerReading* accelReading)
{
    if (!sensors->enabled)
    {
        return false;
    }

    QtMobility::QMagnetometerReading* magReading = sensors->magSensor->reading();

    if (!accelReading || !magReading)
    {
        return false;
    }


    // Gravity acceleration; normalized to equal alt/az up in device frame.
    Vec3 u(accelReading->x(),
            accelReading->y(),
            accelReading->z());

    //qDebug() << "U length: " << u.normalize();
    if (u.normalize() < 1e-8)
    {
        return false;
    }

    // Magentic field direction, points north and down
    Vec3 b(
                magReading->x(),
                magReading->y(),
                magReading->z());

    //qDebug() << "B length: " << b.normalize();
    if (b.normalize() < 1e-8)
    {
        return false;
    }

    Vec3 s(b^u);	// east
    s.normalize();

    Vec3 f(u^s);	// north
    f.normalize();


    double dt = 1./40.;

    Matrix3 m;
    m.set(s.x, f.x, u.x,
          s.y, f.y, u.y,
          s.z, f.z, u.z);

    Quat qt(m);


    Quat& q0 = sensors->rotation;
    Vec3& w0 = sensors->angVel;



    if (sensors->firstMeasurement)
    {
        sensors->firstMeasurement = false;
        q0 = qt;
        w0 = Vec3(0., 0., 0.);
        return true;
    }

    StelMovementMgr* mmgr = GETSTELMODULE(StelMovementMgr);

    double smooth;
    double fov = mmgr->getCurrentFov();
    if (fov > 60.)
    {
        smooth = 0.0;
    }
    else
    {
        smooth = (60. - fov) / 60.;
    }



    double Kp = 23.0 * (1.0 - smooth);
    double Kd = 8.;

    // calc rotation error in device frame
    Vec3 error;
    {
        double angle;
        (q0.conj() * qt).getAngleAxis(angle, error);
        error *= angle;
    }


    // integrate to next rotation state
    //
    // see Rigid body dynamics using Euler’s equations, Runge-Kutta and quaternions.
    // by Indrek Mandre <indrek@mare.ee> http://www.mare.ee/indrek/


    Quat w_dot(error * Kp - w0 * Kd);

    Quat q0_dot = q0 * Quat(w0) * 0.5;

    Quat k1 = q_dot2(q0, q0_dot, w_dot);
    Quat C = q0 + q0_dot*dt*0.5 + k1*(dt*dt*0.125);
    Quat k2 = q_dot2(C, q0_dot + k1*dt*0.5, w_dot);
    Quat k3 = q_dot2(C, q0_dot + k2*dt*0.5, w_dot);
    Quat k4 = q_dot2(q0 + q0_dot*dt + k3*(dt*dt*0.5), q0_dot + k3*dt, w_dot);

    Quat q1 = q0 + q0_dot * dt + (k1 + k2 + k3)*(dt*dt/6.0);
    Quat q1_dot = q0_dot + (k1 + k2*2. + k3*2. + k4)*(dt/6.0);

    Quat w1 = q1.conj() * q1_dot * 2.;

    q0 = q1;

    if (frameNo++ % 100 == 0)
    {
        //qDebug() << "Norm";
        q0.normalize();
    }

    w0 = w1.getVec3();

    return true;
}



void StelSensors::startSensors()
{
    qDebug() << "Starting sensors";
    if (enabled)
        return;


    firstMeasurement = true;
    if (!magSensor->isActive())
        magSensor->start();

    if (!magSensor->isActive())
    {
        qDebug() << "StelCore::StelCore(): Magnetometer Sensor didn't start!" << endl;
    }

    if (!accelSensor->isActive())
            accelSensor->start();

    if (!accelSensor->isActive())
    {
        qDebug() << "StelCore::StelCore(): Accelerometer Sensor didn't start!" << endl;
    }


    enabled = accelSensor->isActive() && magSensor->isActive();

}

void StelSensors::stopSensors()
{
    qDebug() << "Stopping sensors";
    if (magSensor->isActive())
        magSensor->stop();

    if (accelSensor->isActive())
        accelSensor->stop();


    enabled = false;
}

Mat4d StelSensors::calcMatrix()
{
    Matrix3 m;
    rotation.getMatrix(m);

    return Mat4d(m.v[0][0], m.v[0][1], m.v[0][2], 0.,
                 m.v[1][0], m.v[1][1], m.v[1][2], 0.,
                 m.v[2][0], m.v[2][1], m.v[2][2], 0.,
                 0., 0., 0., 1.);
}
