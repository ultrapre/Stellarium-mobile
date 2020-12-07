
#include "VecMath.hpp"
#include <QString>
#include <QStringList>
#include <QDebug>

///// Vector3 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Obtains a Vec3i/Vec3f/Vec3d from a stringlist with the form x,y,z  (use C++11 type delegating constructors)
template<> Vec3i::Vector3(QStringList s) : Vector3{s.value(0, "0").toInt(),s.value(1, "0").toInt(),s.value(2, "0").toInt()}
{
    if (s.size()!=3)
        qWarning() << "Vec3i from StringList of unexpected length" << s.size() << ":" << s.join("/");
}
template<> Vec3f::Vector3(QStringList s) : Vector3{s.value(0, "0.").toFloat(),s.value(1, "0.").toFloat(),s.value(2, "0.").toFloat()}
{
    if (s.size()!=3)
        qWarning() << "Vec3f from StringList of unexpected length" << s.size() << ":" << s.join("/");
}
template<> Vec3d::Vector3(QStringList s) : Vector3{s.value(0, "0.").toDouble(),s.value(1, "0.").toDouble(),s.value(2, "0.").toDouble()}
{
    if (s.size()!=3)
        qWarning() << "Vec3d from StringList of unexpected length" << s.size() << ":" << s.join("/");
}

// Obtains a Vec3i/Vec3f/Vec3d from a string with the form "x,y,z". We must also force instances here.
template<class T> Vector3<T>::Vector3(QString s) : Vector3{s.split(",")}{}
template Vector3<int>::Vector3(QString s);
template Vector3<float>::Vector3(QString s);
template Vector3<double>::Vector3(QString s);
