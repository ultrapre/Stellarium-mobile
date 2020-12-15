/*
 TheLarge - Copyright (C) 2011-2012 Marko Srebre

 TheLarge is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TheLarge is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TheLarge.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef STELQUATERNION_HPP
#define STELQUATERNION_HPP



#include <cmath>
#include <cassert>
#include <sstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif

struct Vec3 
{ 
    Vec3() : x(0.0), y(0.0), z(0.0) {}
    Vec3(double px, double py, double pz) : x(px), y(py), z(pz) {}


    double x, y, z; 

    bool operator==(const Vec3& r) const
    {
        return x == r.x && y == r.y && z == r.z;
    }

    bool operator!=(const Vec3& r) const
    {
        return x != r.x || y != r.y || z != r.z;
    }

    /* Cross product. */
    Vec3 operator^(const Vec3& r) const
    {
        return Vec3(
                y*r.z - z*r.y,
                z*r.x - x*r.z,
                x*r.y - y*r.x);
    }

    /* Dot product. */
    double operator*(const Vec3& r) const
    {
        return x*r.x + y*r.y + z*r.z;
    }

    Vec3& operator*=(double r)
    {
        x *= r;
        y *= r;
        z *= r;
        return *this;
    }

    Vec3& operator/=(double r)
    {
        x /= r;
        y /= r;
        z /= r;
        return *this;
    }

    Vec3 operator*(double r) const
    {
        return Vec3(x*r, y*r, z*r);
    }

    Vec3 operator+(const Vec3& r) const
    {
        return Vec3(x + r.x, y + r.y, z + r.z);
    }

    Vec3 operator-(const Vec3& r) const
    {
        return Vec3(x - r.x, y - r.y, z - r.z);
    }

    Vec3& operator+=(const Vec3& r)
    {
        x += r.x;
        y += r.y;
        z += r.z;
        return *this;
    }

    double normalize()
    {
        double f = length();
        if (f > 0.)
        {
            x /= f;
            y /= f;
            z /= f;
        }
        else
        {
            x = 1.0;
            y = 0.0;
            z = 0.0;
        }
        return f;
    }

    double length() const
    {
        return sqrt(x*x + y*y + z*z);
    }

    double length2() const
    {
        return x*x + y*y + z*z;
    }

    std::string tostr() const
    {
        std::stringstream s;
        s << "(" << x << "," << y << "," << z << ")";
        return s.str();
    };
};

struct Matrix3 
{ 

    void set(double v00, double v01, double v02,
            double v10, double v11, double v12,
            double v20, double v21, double v22)
    {
        v[0][0] = v00; v[0][1] = v01; v[0][2] = v02;
        v[1][0] = v10; v[1][1] = v11; v[1][2] = v12;
        v[2][0] = v20; v[2][1] = v21; v[2][2] = v22;
    }



    double v[3][3]; 
};

struct Quat 
{ 
    double w, x, y, z; 

    Quat() : w(1.0), x(0.0), y(0.0), z(0.0) {}
    Quat(const Vec3& v) : w(0.0), x(v.x), y(v.y), z(v.z) {}
    Quat(double pw, double px, double py, double pz) : w(pw), x(px), y(py), z(pz) {}

    Quat(const Vec3& axis, double angle)
    {
        double s = sin(angle * 0.5);
        x = axis.x * s;
        y = axis.y * s;
        z = axis.z * s;
        w = cos(angle * 0.5);
    }

    void set(const Quat& q)
    {
        *this = q;
    }


    Quat(const Matrix3& m)
    {
        // openscenegraph implementation
        
        double s;
        double tq[4];
        int    i, j;

        // Use tq to store the largest trace
        tq[0] = 1 + m.v[0][0]+m.v[1][1]+m.v[2][2];
        tq[1] = 1 + m.v[0][0]-m.v[1][1]-m.v[2][2];
        tq[2] = 1 - m.v[0][0]+m.v[1][1]-m.v[2][2];
        tq[3] = 1 - m.v[0][0]-m.v[1][1]+m.v[2][2];

        // Find the maximum (could also use stacked if's later)
        j = 0;
        for(i=1;i<4;i++) j = (tq[i]>tq[j])? i : j;

        // check the diagonal
        if (j==0)
        {
            /* perform instant calculation */
            w = tq[0];
            x = m.v[1][2]-m.v[2][1]; 
            y = m.v[2][0]-m.v[0][2]; 
            z = m.v[0][1]-m.v[1][0]; 
        }
        else if (j==1)
        {
            w = m.v[1][2]-m.v[2][1]; 
            x = tq[1];
            y = m.v[0][1]+m.v[1][0]; 
            z = m.v[2][0]+m.v[0][2]; 
        }
        else if (j==2)
        {
            w = m.v[2][0]-m.v[0][2]; 
            x = m.v[0][1]+m.v[1][0]; 
            y = tq[2];
            z = m.v[1][2]+m.v[2][1]; 
        }
        else /* if (j==3) */
        {
            w = m.v[0][1]-m.v[1][0]; 
            x = m.v[2][0]+m.v[0][2]; 
            y = m.v[1][2]+m.v[2][1]; 
            z = tq[3];
        }

        s = sqrt(0.25/tq[j]);
        w *= s;
        x *= s;
        y *= s;
        z *= s;
    }

    Vec3 getVec3() const { return Vec3(x, y, z); }

    Quat(const Vec3& from, const Vec3& to)
    {
        Vec3 a = from ^ to;
        x = a.x;
        y = a.y;
        z = a.z;
        w = sqrt(from.length2() * to.length2()) + from * to;
        (*this).normalize();
    }

    std::string tostr() const
    {
        std::stringstream s;
        s << "(" << w << ", " << x << "," << y << "," << z << ")";
        return s.str();
    };

    Quat operator*(const Quat& r) const
    {
        return Quat(
                r.w*w - r.x*x - r.y*y - r.z*z,
                r.w*x + r.x*w + r.y*z - r.z*y,
                r.w*y - r.x*z + r.y*w + r.z*x,
                r.w*z + r.x*y - r.y*x + r.z*w);
    }

    Quat conj() const
    {
        return Quat(w, -x, -y, -z);
    }

    Quat operator+(const Quat& r)
    {
        return Quat(r.w+w, r.x+x, r.y+y, r.z+z);
    }

    Quat operator*(double s) const
    {
        return Quat(w*s, x*s, y*s, z*s);
    }

    double magnitude() const
    {
        return sqrt(w*w + x*x + y*y + z*z);
    }

    void normalize()
    {
        double m = magnitude();
        w /= m;
        x /= m;
        y /= m;
        z /= m;
    }

    void slerp(double t, const Quat& q1, const Quat& pq2)
    {
        Quat q2(pq2);

        const double epsilon = 0.00001;
        double omega, cosomega, sinomega, scale_from, scale_to;

        cosomega = 
            q1.x * q2.x +
            q1.y * q2.y +
            q1.z * q2.z +
            q1.w * q2.w;

        if (cosomega < 0.0)
        { 
            cosomega = -cosomega; 
            q2.x = -q2.x;
            q2.y = -q2.y;
            q2.z = -q2.z;
            q2.w = -q2.w;
        }

        if((1.0 - cosomega) > epsilon)
        {
            omega= acos(cosomega) ;  // 0 <= omega <= Pi (see man acos)
            sinomega = sin(omega) ;  // this sinomega should always be +ve so
            // could try sinomega=sqrt(1-cosomega*cosomega) to avoid a sin()?
            scale_from = sin((1.0-t)*omega)/sinomega ;
            scale_to = sin(t*omega)/sinomega ;
        }
        else
        {
            /* --------------------------------------------------
               The ends of the vectors are very close
               we can use simple linear interpolation - no need
               to worry about the "spherical" interpolation
               -------------------------------------------------- */
            scale_from = 1.0 - t ;
            scale_to = t ;
        }

        x = q1.x * scale_from + q2.x * scale_to;
        y = q1.y * scale_from + q2.y * scale_to;
        z = q1.z * scale_from + q2.z * scale_to;
        w = q1.w * scale_from + q2.w * scale_to;
    }


    Vec3 rotate(const Vec3 v) const
    {
        // openscenegraph - nVidia SDK implementation
        Vec3 uv, uuv; 
        Vec3 qvec(x, y, z);

        uv = qvec ^ v;
        uuv = qvec ^ uv; 

        uv *= (2.0 * w); 
        uuv *= 2.0; 
        return v + uv + uuv;
    }

    void getAngleAxis(double& angle, Vec3& axis) const
    {
        // adopted from openscenegraph
        double sinhalfangle = sqrt(x*x + y*y + z*z);

        angle = 2.0 * atan2(sinhalfangle, w);
        //std::cout << "s: " << sinhalfangle << ": " << magnitude() << std::endl;
        if (sinhalfangle)
        {
            axis.x = x / sinhalfangle;
            axis.y = y / sinhalfangle;
            axis.z = z / sinhalfangle;
        }
        else
        {
            axis.x = 0.0;
            axis.y = 0.0;
            axis.z = 1.0;
        }
        if (angle > M_PI)
        {
            angle = 2.*M_PI - angle;
            axis *= -1.;
        }
    }

    void getMatrix(Matrix3& m)
    {
        const double p0 = w;
        const double p1 = x;
        const double p2 = y;
        const double p3 = z;

        const double pp0 = p0 * p0;
        const double pp1 = p1 * p1;
        const double pp2 = p2 * p2;
        const double pp3 = p3 * p3;

        m.set(
                2.*(pp0 + pp1) - 1.,    2.*(p1 * p2 + p0 * p3),  2.*(p1 * p3 - p0 * p2),
                2.*(p1 * p2 - p0 * p3),  2.*(pp0 + pp2) - 1., 2.*(p2 * p3 + p0 * p1),
                2.*(p1 * p3 + p0 * p2),  2.*(p2 * p3 - p0 * p1),  2.*(pp0 + pp3) - 1.);
    }

};

#endif
