#include "defs.h"

#include "Quaternion.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"

#include <math.h>

Quaternion::Quaternion(float x, float y, float z, float w)
    :x(x), y(y), z(z), w(w)
    {}

Quaternion::Quaternion(const Vector3& axis, float angle)
    :x(0), y(0), z(0), w(1)
{
    setToAxisAngle(axis, angle);
}

Quaternion::Quaternion(const Quaternion& quat)
    :x(quat.x), y(quat.y), z(quat.z), w(quat.w)
{}

Quaternion& Quaternion::setIdentity(){
    x = 0;
    y = 0;
    z = 0;
    w = 1;

    return *this;
}

float Quaternion::length() const{
    return sqrt(x * x + y * y + z * z + w * w);
}

Quaternion& Quaternion::normalize(){
    float mag = length();

    if(mag == 0) return *this;

    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;

    return *this;
}

Quaternion& Quaternion::negate(){
    x = -x;
    y = -y;
    z = -z;
    w = -w;

    return *this;
}

Quaternion Quaternion::operator*(const Quaternion& right){
    return Quaternion(
            this->x * right.w + this->w * right.x + this->y * right.z
            - this->z * right.y, this->y * right.w + this->w * right.y
            + this->z * right.x - this->x * right.z, this->z * right.w
            + this->w * right.z + this->x * right.y - this->y * right.x,
            this->w * right.w - this->x * right.x - this->y * right.y
            - this->z * right.z
            );
}

Quaternion& Quaternion::operator*=(const Quaternion& right){
    this->x = this->x * right.w + this->w * right.x + this->y * right.z - this->z * right.y;
    this->y = this->y * right.w + this->w * right.y + this->z * right.x - this->x * right.z;
    this->z = this->z * right.w + this->w * right.z + this->x * right.y - this->y * right.x;
    this->w = this->w * right.w - this->x * right.x - this->y * right.y - this->z * right.z;

    return *this;
}

Vector3 Quaternion::operator*(const Vector3& right){
    Matrix44 trans = toMatrix();
    Vector4 mod = trans * Vector4(right.x, right.y, right.z, 0);
    return Vector3(mod.x, mod.y, mod.z);
}

Vector4 Quaternion::operator*(const Vector4& right){
    Matrix44 trans = toMatrix();
    return trans * right;
}

Matrix44 Quaternion::toMatrix() const{
    Matrix44 matrix;

    float xy = x * y;
    float xz = x * z;
    float xw = x * w;
    float yz = y * z;
    float yw = y * w;
    float zw = z * w;
    float xSquared = x * x;
    float ySquared = y * y;
    float zSquared = z * z;

    matrix.m00 = 1 - 2 * (ySquared + zSquared);
    matrix.m01 = 2 * (xy - zw);
    matrix.m02 = 2 * (xz + yw);
    matrix.m03 = 0;
    matrix.m10 = 2 * (xy + zw);
    matrix.m11 = 1 - 2 * (xSquared + zSquared);
    matrix.m12 = 2 * (yz - xw);
    matrix.m13 = 0;
    matrix.m20 = 2 * (xz - yw);
    matrix.m21 = 2 * (yz + xw);
    matrix.m22 = 1 - 2 * (xSquared + ySquared);
    matrix.m23 = 0;
    matrix.m30 = 0;
    matrix.m31 = 0;
    matrix.m32 = 0;
    matrix.m33 = 1;

    return matrix;
}

Quaternion& Quaternion::setToAxisAngle(const Vector3& axis, float angle){
    Matrix44 rot;
    rot.rotate(axis, angle);

    setMatrix(rot);
    normalize();

    return *this;
}

Quaternion Quaternion::slerp(const Quaternion& a, const Quaternion& b, float blend){
    Quaternion result;

    float dot = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
    float blendI = 1.0f - blend;

    if (dot < 0)
    {
        result.w = blendI * a.w + blend * -b.w;
        result.x = blendI * a.x + blend * -b.x;
        result.y = blendI * a.y + blend * -b.y;
        result.z = blendI * a.z + blend * -b.z;
    }
    else
    {
        result.w = blendI * a.w + blend * b.w;
        result.x = blendI * a.x + blend * b.x;
        result.y = blendI * a.y + blend * b.y;
        result.z = blendI * a.z + blend * b.z;
    }

    result.normalize();
    return result;
}

Quaternion& Quaternion::lookRotation(const Vector3& f, const Vector3& u){
    Vector3 forward(f);
    Vector3 up(u);

    forward.normalize();
    up.normalize();
    Vector3 right = forward % up;

    Matrix44 rot;
    rot.m00 = right.x;
    rot.m10 = right.y;
    rot.m20 = right.z;

    rot.m01 = up.x;
    rot.m11 = up.y;
    rot.m21 = up.z;

    rot.m02 = forward.x;
    rot.m12 = forward.y;
    rot.m22 = forward.z;

    setMatrix(rot);
    normalize();

    return *this;
}

Quaternion& Quaternion::setMatrix(const Matrix44& matrix){
    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;

    m00 = matrix.m00;
    m01 = matrix.m01;
    m02 = matrix.m02;

    m10 = matrix.m10;
    m11 = matrix.m11;
    m12 = matrix.m12;

    m20 = matrix.m20;
    m21 = matrix.m21;
    m22 = matrix.m22;

    float s;
    float tr = m00 + m11 + m22;
    if (tr >= 0.0) {
        s = (float) sqrt(tr + 1.0);
        w = s * 0.5f;
        s = 0.5f / s;
        x = (m21 - m12) * s;
        y = (m02 - m20) * s;
        z = (m10 - m01) * s;
    } else {
        float max = MAX(MAX(m00, m11), m22);
        if (max == m00) {
            s = (float) sqrt(m00 - (m11 + m22) + 1.0);
            x = s * 0.5f;
            s = 0.5f / s;
            y = (m01 + m10) * s;
            z = (m20 + m02) * s;
            w = (m21 - m12) * s;
        } else if (max == m11) {
            s = (float) sqrt(m11 - (m22 + m00) + 1.0);
            y = s * 0.5f;
            s = 0.5f / s;
            z = (m12 + m21) * s;
            x = (m01 + m10) * s;
            w = (m02 - m20) * s;
        } else {
            s = (float) sqrt(m22 - (m00 + m11) + 1.0);
            z = s * 0.5f;
            s = 0.5f / s;
            x = (m20 + m02) * s;
            y = (m12 + m21) * s;
            w = (m10 - m01) * s;
        }
    }

    return *this;
}





