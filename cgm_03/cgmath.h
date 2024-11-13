/**
 * Computergrafik
 * Copyright © 2021-2024 Tobias Reimann
 * Copyright © 2024 Lukas Scheurer: Rewritten in modern C++
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#define _USE_MATH_DEFINES

#include <cmath>

inline double deg2rad(double deg)
{
    return deg * M_PI / 180.0;
}

inline double rad2deg(double rad)
{
    return rad * 180.0 / M_PI;
}

struct Vector3
{
    double x;
    double y;
    double z;

    Vector3(double x, double y, double z)
        : x(x), y(y), z(z)
    {
    }

    Vector3 operator+(const Vector3 &b)
    {
        Vector3 result = {
            x + b.x,
            y + b.y,
            z + b.z
        };
        return result;
    }
};

struct Vector4
{
    double x;
    double y;
    double z;
    double w;

    Vector4(double x, double y, double z, double w)
        : x(x), y(y), z(z), w(w)
    {
    }

    Vector4(const Vector3 &v, double w)
        : x(v.x), y(v.y), z(v.z), w(w)
    {
    }

    Vector3 xyz()
    {
        return {x, y, z};
    }

    Vector4 operator+(const Vector4 &b)
    {
        Vector4 result = {
            x + b.x,
            y + b.y,
            z + b.z,
            w + b.w
        };
        return result;
    }
};


struct Matrix4
{
    double m11;  double m21;  double m31;  double m41;
    double m12;  double m22;  double m32;  double m42;
    double m13;  double m23;  double m33;  double m43;
    double m14;  double m24;  double m34;  double m44;

    float values[16];

    static Matrix4 translate(double x, double y, double z)
    {
        Matrix4 m = {
            1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1
        };
        return m;
    }

    static Matrix4 rotateX(double a)
    {
        Matrix4 m = {
            1,      0,       0, 0,
            0, cos(a), -sin(a), 0,
            0, sin(a),  cos(a), 0,
            0,      0,       0, 1
        };
        return m;
    }

    static Matrix4 rotateY(double a)
    {
        Matrix4 m = {
             cos(a), 0, sin(a), 0,
                  0, 1,      0, 0,
            -sin(a), 0, cos(a), 0,
                  0, 0,      0, 1
        };
        return m;
    }

    static Matrix4 rotateZ(double a)
    {
        Matrix4 m = {
            cos(a), -sin(a), 0, 0,
            sin(a),  cos(a), 0, 0,
                 0,       0, 1, 0,
                 0,       0, 0, 1
        };
        return m;
    }

    static Matrix4 scale(double a)
    {
        Matrix4 m = {
            a, 0, 0, 0,
            0, a, 0, 0,
            0, 0, a, 0,
            0, 0, 0, 1
        };
        return m;
    }

    static Matrix4 perspective(double fov, double aspect, double zNear, double zFar)
    {
        double h = zNear * tan(fov * 0.5);
        double w = h * aspect;

        double left = -w;
        double right = w;
        double bottom = -h;
        double top = h;

        double m11 = 2 * zNear / (right - left);
        double m22 = 2 * zNear / (top - bottom);
        double m31 = (right + left) / (right - left);
        double m32 = (top + bottom) / (top - bottom);
        double m33 = -(zFar + zNear) / (zFar - zNear);
        double m43 = -2 * zFar * zNear / (zFar - zNear);

        Matrix4 m = {
            m11,   0, m31,   0,
              0, m22, m32,   0,
              0,   0, m33, m43,
              0,   0,  -1,   0
        };
        return m;
    }

    static Matrix4 identity()
    {
        static Matrix4 m = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
        return m;
    }

    Matrix4 operator*(const Matrix4 &b)
    {
        Matrix4 result = {
            m11 * b.m11 + m21 * b.m12 + m31 * b.m13 + m41 * b.m14,
            m11 * b.m21 + m21 * b.m22 + m31 * b.m23 + m41 * b.m24,
            m11 * b.m31 + m21 * b.m32 + m31 * b.m33 + m41 * b.m34,
            m11 * b.m41 + m21 * b.m42 + m31 * b.m43 + m41 * b.m44,
            
            m12 * b.m11 + m22 * b.m12 + m32 * b.m13 + m42 * b.m14,
            m12 * b.m21 + m22 * b.m22 + m32 * b.m23 + m42 * b.m24,
            m12 * b.m31 + m22 * b.m32 + m32 * b.m33 + m42 * b.m34,
            m12 * b.m41 + m22 * b.m42 + m32 * b.m43 + m42 * b.m44,
            
            m13 * b.m11 + m23 * b.m12 + m33 * b.m13 + m43 * b.m14,
            m13 * b.m21 + m23 * b.m22 + m33 * b.m23 + m43 * b.m24,
            m13 * b.m31 + m23 * b.m32 + m33 * b.m33 + m43 * b.m34,
            m13 * b.m41 + m23 * b.m42 + m33 * b.m43 + m43 * b.m44,
            
            m14 * b.m11 + m24 * b.m12 + m34 * b.m13 + m44 * b.m14,
            m14 * b.m21 + m24 * b.m22 + m34 * b.m23 + m44 * b.m24,
            m14 * b.m31 + m24 * b.m32 + m34 * b.m33 + m44 * b.m34,
            m14 * b.m41 + m24 * b.m42 + m34 * b.m43 + m44 * b.m44
        };
        return result;
    }

    Vector4 operator*(const Vector4 &v) const
    {
        Vector4 result = {
            m11 * v.x + m21 * v.y + m31 * v.z + m41 * v.w,
            m12 * v.x + m22 * v.y + m32 * v.z + m42 * v.w,
            m13 * v.x + m23 * v.y + m33 * v.z + m43 * v.w,
            m14 * v.x + m24 * v.y + m34 + v.z + m44 * v.w
        };
        return result;
    }

    float *toFloat()
    {
        // Reorder for OpenGL
        values[0] = static_cast<float>(m11);
        values[1] = static_cast<float>(m12);
        values[2] = static_cast<float>(m13);
        values[3] = static_cast<float>(m14);
        values[4] = static_cast<float>(m21);
        values[5] = static_cast<float>(m22);
        values[6] = static_cast<float>(m23);
        values[7] = static_cast<float>(m24);
        values[8] = static_cast<float>(m31);
        values[9] = static_cast<float>(m32);
        values[10] = static_cast<float>(m33);
        values[11] = static_cast<float>(m34);
        values[12] = static_cast<float>(m41);
        values[13] = static_cast<float>(m42);
        values[14] = static_cast<float>(m43);
        values[15] = static_cast<float>(m44);

        return values;
    }
};