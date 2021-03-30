#include "Vector4.h"
#include <math.h>

#include <iostream>

Vector4::Vector4(float x, float y, float z, float w)
    :x(x), y(y), z(z), w(w)
{}

Vector4::Vector4(const Vector4& v)
    :x(v.x), y(v.y), z(v.z), w(v.w)
{}

Vector4& Vector4::operator=(const Vector4& vect){
    x = vect.x;
    y = vect.y;
    z = vect.z;
    w = vect.w;

    return *this;
}

Vector4::~Vector4(){}

float Vector4::length() const {
    return sqrt(x * x + y * y + z * z + w * w);
}

Vector4& Vector4::lerp(const Vector4& a, const Vector4& b, float t, Vector4& dest){
    dest.x = a.x + ((b.x - a.x) * t);
    dest.y = a.y + ((b.y - a.y) * t);
    dest.z = a.z + ((b.z - a.z) * t);
    dest.w = a.w + ((b.w - a.w) * t);

    return dest;
}

Vector4& Vector4::sub(const Vector4& left, const Vector4& right, Vector4& dest){
    dest.x = left.x - right.x;
    dest.y = left.y - right.y;
    dest.z = left.z - right.z;
    dest.w = left.w - right.w;

    return dest;
}

Vector4& Vector4::add(const Vector4& left, const Vector4& right, Vector4& dest){
    dest.x = left.x + right.x;
    dest.y = left.y + right.y;
    dest.z = left.z + right.z;
    dest.w = left.w + right.w;

    return dest;
}

float Vector4::dot(const Vector4& left, const Vector4& right){
    return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

Vector4& Vector4::operator+=(const Vector4& right){
    Vector4::add(*this, right, *this);
    return *this;
}

Vector4& Vector4::operator-=(const Vector4& right){
    Vector4::sub(*this, right, *this);
    return *this;
}

Vector4 Vector4::operator+(const Vector4& right) const{
    Vector4 ret;
    Vector4::add(*this, right, ret);
    return ret;
}

Vector4 Vector4::operator-(const Vector4& right) const{
    Vector4 ret;
    Vector4::sub(*this, right, ret);
    return ret;
}

float Vector4::operator*(const Vector4& b) const{
    return Vector4::dot(*this, b);
}

float Vector4::dist(const Vector4& a, const Vector4& b){
    float x = a.x - b.x;
    float y = a.y - b.y;
    float z = a.z - b.z;
    float w = a.w - b.w;

    return sqrt(x * x + y * y + z * z + w * w);
}

Vector4 Vector4::getNormalized(const Vector4& input){
    Vector4 ret(input);
    ret.normalize();
    return ret;
}

Vector4& Vector4::scale(float s){
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
}

Vector4& Vector4::normalize(){
    float mag = length();

    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;

    return *this;
}

void Vector4::print() const{
    std::cout << x << " " << y << " " << z << " " << w << "\n";
}

