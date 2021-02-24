#include "Matrix44.h"
#include "Vector3.h"
#include "Vector4.h"

#include <iostream>
#include <math.h>

#define DET33(t00, t01, t02, t10, t11, t12, t20, t21, t22) (((t00) * ((t11) * (t22) - (t12) * (t21))) + ((t01) * ((t12) * (t20) - (t10) * (t22))) + ((t02) * ((t10) * (t21) - (t11) * (t20))))

Matrix44::Matrix44()
    :m00(1), m01(0), m02(0), m03(0),
    m10(0), m11(1), m12(0), m13(0),
    m20(0), m21(0), m22(1), m23(0),
    m30(0), m31(0), m32(0), m33(1)
{}      

Matrix44::Matrix44(const Matrix44& m)
    :m00(m.m00), m01(m.m01), m02(m.m02), m03(m.m03),
    m10(m.m10), m11(m.m11), m12(m.m12), m13(m.m13),
    m20(m.m20), m21(m.m21), m22(m.m22), m23(m.m23),
    m30(m.m30), m31(m.m31), m32(m.m32), m33(m.m33)
{}      

Matrix44& Matrix44::translate(const Vector3& vec) {
    this->m30 += this->m00 * vec.x + this->m10 * vec.y + this->m20 * vec.z;
    this->m31 += this->m01 * vec.x + this->m11 * vec.y + this->m21 * vec.z;
    this->m32 += this->m02 * vec.x + this->m12 * vec.y + this->m22 * vec.z;
    this->m33 += this->m03 * vec.x + this->m13 * vec.y + this->m23 * vec.z;

    return *this;
}

Matrix44& Matrix44::operator=(const Matrix44& m){
    m00 = m.m00;
    m01 = m.m01;
    m02 = m.m02;
    m03 = m.m03;

    m10 = m.m10;
    m11 = m.m11;
    m12 = m.m12;
    m13 = m.m13;

    m20 = m.m20;
    m21 = m.m21;
    m22 = m.m22;
    m23 = m.m23;

    m30 = m.m30;
    m31 = m.m31;
    m32 = m.m32;
    m33 = m.m33;

    return *this;
}

Matrix44::~Matrix44(){}

Matrix44& Matrix44::add(const Matrix44& left, const Matrix44& right, Matrix44& dest){
    dest.m00 = left.m00 + right.m00;
    dest.m01 = left.m01 + right.m01;
    dest.m02 = left.m02 + right.m02;
    dest.m03 = left.m03 + right.m03;

    dest.m10 = left.m10 + right.m10;
    dest.m11 = left.m11 + right.m11;
    dest.m12 = left.m12 + right.m12;
    dest.m13 = left.m13 + right.m13;

    dest.m20 = left.m20 + right.m20;
    dest.m21 = left.m21 + right.m21;
    dest.m22 = left.m22 + right.m22;
    dest.m23 = left.m23 + right.m23;

    dest.m30 = left.m30 + right.m30;
    dest.m31 = left.m31 + right.m31;
    dest.m32 = left.m32 + right.m32;
    dest.m33 = left.m33 + right.m33;

    return dest;
}

Matrix44& Matrix44::sub(const Matrix44& left, const Matrix44& right, Matrix44& dest){
    dest.m00 = left.m00 - right.m00;
    dest.m01 = left.m01 - right.m01;
    dest.m02 = left.m02 - right.m02;
    dest.m03 = left.m03 - right.m03;

    dest.m10 = left.m10 - right.m10;
    dest.m11 = left.m11 - right.m11;
    dest.m12 = left.m12 - right.m12;
    dest.m13 = left.m13 - right.m13;

    dest.m20 = left.m20 - right.m20;
    dest.m21 = left.m21 - right.m21;
    dest.m22 = left.m22 - right.m22;
    dest.m23 = left.m23 - right.m23;

    dest.m30 = left.m30 - right.m30;
    dest.m31 = left.m31 - right.m31;
    dest.m32 = left.m32 - right.m32;
    dest.m33 = left.m33 - right.m33;

    return dest;
}

Matrix44& Matrix44::mul(const Matrix44& left, const Matrix44& right, Matrix44& dest){
    float m00 = left.m00 * right.m00 + left.m10 * right.m01 + left.m20 * right.m02 + left.m30 * right.m03;
    float m01 = left.m01 * right.m00 + left.m11 * right.m01 + left.m21 * right.m02 + left.m31 * right.m03;
    float m02 = left.m02 * right.m00 + left.m12 * right.m01 + left.m22 * right.m02 + left.m32 * right.m03;
    float m03 = left.m03 * right.m00 + left.m13 * right.m01 + left.m23 * right.m02 + left.m33 * right.m03;
    float m10 = left.m00 * right.m10 + left.m10 * right.m11 + left.m20 * right.m12 + left.m30 * right.m13;
    float m11 = left.m01 * right.m10 + left.m11 * right.m11 + left.m21 * right.m12 + left.m31 * right.m13;
    float m12 = left.m02 * right.m10 + left.m12 * right.m11 + left.m22 * right.m12 + left.m32 * right.m13;
    float m13 = left.m03 * right.m10 + left.m13 * right.m11 + left.m23 * right.m12 + left.m33 * right.m13;
    float m20 = left.m00 * right.m20 + left.m10 * right.m21 + left.m20 * right.m22 + left.m30 * right.m23;
    float m21 = left.m01 * right.m20 + left.m11 * right.m21 + left.m21 * right.m22 + left.m31 * right.m23;
    float m22 = left.m02 * right.m20 + left.m12 * right.m21 + left.m22 * right.m22 + left.m32 * right.m23;
    float m23 = left.m03 * right.m20 + left.m13 * right.m21 + left.m23 * right.m22 + left.m33 * right.m23;
    float m30 = left.m00 * right.m30 + left.m10 * right.m31 + left.m20 * right.m32 + left.m30 * right.m33;
    float m31 = left.m01 * right.m30 + left.m11 * right.m31 + left.m21 * right.m32 + left.m31 * right.m33;
    float m32 = left.m02 * right.m30 + left.m12 * right.m31 + left.m22 * right.m32 + left.m32 * right.m33;
    float m33 = left.m03 * right.m30 + left.m13 * right.m31 + left.m23 * right.m32 + left.m33 * right.m33;

    dest.m00 = m00;
    dest.m01 = m01;
    dest.m02 = m02;
    dest.m03 = m03;
    dest.m10 = m10;
    dest.m11 = m11;
    dest.m12 = m12;
    dest.m13 = m13;
    dest.m20 = m20;
    dest.m21 = m21;
    dest.m22 = m22;
    dest.m23 = m23;
    dest.m30 = m30;
    dest.m31 = m31;
    dest.m32 = m32;
    dest.m33 = m33;

    return dest;
}

Vector4& Matrix44::trans(const Matrix44& left, const Vector4& right, Vector4& dest){
    float x = left.m00 * right.x + left.m10 * right.y + left.m20 * right.z + left.m30 * right.w;
    float y = left.m01 * right.x + left.m11 * right.y + left.m21 * right.z + left.m31 * right.w;
    float z = left.m02 * right.x + left.m12 * right.y + left.m22 * right.z + left.m32 * right.w;
    float w = left.m03 * right.x + left.m13 * right.y + left.m23 * right.z + left.m33 * right.w;

    dest.x = x;
    dest.y = y;
    dest.z = z;
    dest.w = w;

    return dest;
}

Matrix44& Matrix44::operator+=(const Matrix44& right){
    Matrix44::add(*this, right, *this);
    return *this;
}

Matrix44& Matrix44::operator-=(const Matrix44& right){
    Matrix44::sub(*this, right, *this);
    return *this;
}

Matrix44& Matrix44::operator*=(const Matrix44& right){
    Matrix44::mul(*this, right, *this);
    return *this;
}

Matrix44 Matrix44::operator+(const Matrix44& right) const{
    Matrix44 ret;
    Matrix44::add(*this, right, ret);
    return ret;
}

Matrix44 Matrix44::operator-(const Matrix44& right) const{
    Matrix44 ret;
    Matrix44::sub(*this, right, ret);
    return ret;
}

Matrix44 Matrix44::operator*(const Matrix44& right) const{
    Matrix44 ret;
    Matrix44::mul(*this, right, ret);
    return ret;
}

Vector4 Matrix44::operator*(const Vector4& vec) const{
    Vector4 ret;
    Matrix44::trans(*this, vec, ret);
    return ret;
}

Matrix44& Matrix44::setIdentity(){
    m00 = 1;
    m01 = 0;
    m02 = 0;
    m03 = 0;

    m10 = 0;
    m11 = 1;
    m12 = 0;
    m13 = 0;

    m20 = 0;
    m21 = 0;
    m22 = 1;
    m23 = 0;

    m30 = 0;
    m31 = 0;
    m32 = 0;
    m33 = 1;

    return *this;
}

Matrix44& Matrix44::setZero(){
    m00 = 0;
    m01 = 0;
    m02 = 0;
    m03 = 0;

    m10 = 0;
    m11 = 0;
    m12 = 0;
    m13 = 0;

    m20 = 0;
    m21 = 0;
    m22 = 0;
    m23 = 0;

    m30 = 0;
    m31 = 0;
    m32 = 0;
    m33 = 0;

    return *this;
}

Matrix44& Matrix44::transpose(){
    float m00 = this->m00;
    float m01 = this->m10;
    float m02 = this->m20;
    float m03 = this->m30;
    float m10 = this->m01;
    float m11 = this->m11;
    float m12 = this->m21;
    float m13 = this->m31;
    float m20 = this->m02;
    float m21 = this->m12;
    float m22 = this->m22;
    float m23 = this->m32;
    float m30 = this->m03;
    float m31 = this->m13;
    float m32 = this->m23;
    float m33 = this->m33;

    this->m00 = m00;
    this->m01 = m01;
    this->m02 = m02;
    this->m03 = m03;
    this->m10 = m10;
    this->m11 = m11;
    this->m12 = m12;
    this->m13 = m13;
    this->m20 = m20;
    this->m21 = m21;
    this->m22 = m22;
    this->m23 = m23;
    this->m30 = m30;
    this->m31 = m31;
    this->m32 = m32;
    this->m33 = m33;

    return *this;
}

Matrix44& Matrix44::invert(){
    float determinant = det();

    if (determinant != 0) {
        float determinant_inv = (float)1/determinant;

        float t00 =  DET33(m11, m12, m13, m21, m22, m23, m31, m32, m33);
        float t01 = -DET33(m10, m12, m13, m20, m22, m23, m30, m32, m33);
        float t02 =  DET33(m10, m11, m13, m20, m21, m23, m30, m31, m33);
        float t03 = -DET33(m10, m11, m12, m20, m21, m22, m30, m31, m32);

        float t10 = -DET33(m01, m02, m03, m21, m22, m23, m31, m32, m33);
        float t11 =  DET33(m00, m02, m03, m20, m22, m23, m30, m32, m33);
        float t12 = -DET33(m00, m01, m03, m20, m21, m23, m30, m31, m33);
        float t13 =  DET33(m00, m01, m02, m20, m21, m22, m30, m31, m32);

        float t20 =  DET33(m01, m02, m03, m11, m12, m13, m31, m32, m33);
        float t21 = -DET33(m00, m02, m03, m10, m12, m13, m30, m32, m33);
        float t22 =  DET33(m00, m01, m03, m10, m11, m13, m30, m31, m33);
        float t23 = -DET33(m00, m01, m02, m10, m11, m12, m30, m31, m32);

        float t30 = -DET33(m01, m02, m03, m11, m12, m13, m21, m22, m23);
        float t31 =  DET33(m00, m02, m03, m10, m12, m13, m20, m22, m23);
        float t32 = -DET33(m00, m01, m03, m10, m11, m13, m20, m21, m23);
        float t33 =  DET33(m00, m01, m02, m10, m11, m12, m20, m21, m22);

        m00 = t00*determinant_inv;
        m11 = t11*determinant_inv;
        m22 = t22*determinant_inv;
        m33 = t33*determinant_inv;
        m01 = t10*determinant_inv;
        m10 = t01*determinant_inv;
        m20 = t02*determinant_inv;
        m02 = t20*determinant_inv;
        m12 = t21*determinant_inv;
        m21 = t12*determinant_inv;
        m03 = t30*determinant_inv;
        m30 = t03*determinant_inv;
        m13 = t31*determinant_inv;
        m31 = t13*determinant_inv;
        m32 = t23*determinant_inv;
        m23 = t32*determinant_inv;
    }

    return *this;
}

Matrix44& Matrix44::negate(){
    m00 = -m00;
    m01 = -m01;
    m02 = -m02;
    m03 = -m03;

    m10 = -m10;
    m11 = -m11;
    m12 = -m12;
    m13 = -m13;

    m20 = -m20;
    m21 = -m21;
    m22 = -m22;
    m23 = -m23;

    m30 = -m30;
    m31 = -m31;
    m32 = -m32;
    m33 = -m33;

    return *this;
}

Matrix44& Matrix44::scale(const Vector3& scale){
    this->m00 = this->m00 * scale.x;
    this->m01 = this->m01 * scale.x;
    this->m02 = this->m02 * scale.x;
    this->m03 = this->m03 * scale.x;
    this->m10 = this->m10 * scale.y;
    this->m11 = this->m11 * scale.y;
    this->m12 = this->m12 * scale.y;
    this->m13 = this->m13 * scale.y;
    this->m20 = this->m20 * scale.z;
    this->m21 = this->m21 * scale.z;
    this->m22 = this->m22 * scale.z;
    this->m23 = this->m23 * scale.z;

    return *this;
}

Matrix44& Matrix44::rotate(const Vector3& eulerAxis, float angle){
    float c = (float) cos(angle);
    float s = (float) sin(angle);
    float oneminusc = 1.0f - c;
    float xy = eulerAxis.x*eulerAxis.y;
    float yz = eulerAxis.y*eulerAxis.z;
    float xz = eulerAxis.x*eulerAxis.z;
    float xs = eulerAxis.x*s;
    float ys = eulerAxis.y*s;
    float zs = eulerAxis.z*s;

    float f00 = eulerAxis.x*eulerAxis.x*oneminusc+c;
    float f01 = xy*oneminusc+zs;
    float f02 = xz*oneminusc-ys;
    float f10 = xy*oneminusc-zs;
    float f11 = eulerAxis.y*eulerAxis.y*oneminusc+c;
    float f12 = yz*oneminusc+xs;
    float f20 = xz*oneminusc+ys;
    float f21 = yz*oneminusc-xs;
    float f22 = eulerAxis.z*eulerAxis.z*oneminusc+c;

    float t00 = this->m00 * f00 + this->m10 * f01 + this->m20 * f02;
    float t01 = this->m01 * f00 + this->m11 * f01 + this->m21 * f02;
    float t02 = this->m02 * f00 + this->m12 * f01 + this->m22 * f02;
    float t03 = this->m03 * f00 + this->m13 * f01 + this->m23 * f02;
    float t10 = this->m00 * f10 + this->m10 * f11 + this->m20 * f12;
    float t11 = this->m01 * f10 + this->m11 * f11 + this->m21 * f12;
    float t12 = this->m02 * f10 + this->m12 * f11 + this->m22 * f12;
    float t13 = this->m03 * f10 + this->m13 * f11 + this->m23 * f12;

    this->m20 = this->m00 * f20 + this->m10 * f21 + this->m20 * f22;
    this->m21 = this->m01 * f20 + this->m11 * f21 + this->m21 * f22;
    this->m22 = this->m02 * f20 + this->m12 * f21 + this->m22 * f22;
    this->m23 = this->m03 * f20 + this->m13 * f21 + this->m23 * f22;
    this->m00 = t00;
    this->m01 = t01;
    this->m02 = t02;
    this->m03 = t03;
    this->m10 = t10;
    this->m11 = t11;
    this->m12 = t12;
    this->m13 = t13;

    return *this;
}

float Matrix44::det() const{
    float f = m00 * ((m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32)
            - m13 * m22 * m31
            - m11 * m23 * m32
            - m12 * m21 * m33);
    f -= m01 * ((m10 * m22 * m33 + m12 * m23 * m30 + m13 * m20 * m32)
            - m13 * m22 * m30
            - m10 * m23 * m32
            - m12 * m20 * m33);
    f += m02 * ((m10 * m21 * m33 + m11 * m23 * m30 + m13 * m20 * m31)
            - m13 * m21 * m30
            - m10 * m23 * m31
            - m11 * m20 * m33);
    f -= m03 * ((m10 * m21 * m32 + m11 * m22 * m30 + m12 * m20 * m31)
            - m12 * m21 * m30
            - m10 * m22 * m31
            - m11 * m20 * m32);
    return f;
}

void Matrix44::print() const{
    std::cout << m00 << " " << m01 << " " << m02 << " " << m03 << "\n";
    std::cout << m10 << " " << m11 << " " << m12 << " " << m13 << "\n";
    std::cout << m20 << " " << m21 << " " << m22 << " " << m23 << "\n";
    std::cout << m30 << " " << m31 << " " << m32 << " " << m33 << "\n";
}


