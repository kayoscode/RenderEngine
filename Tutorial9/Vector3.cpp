#include "Vector3.h"
#include <math.h>

#include <iostream>

Vector3::Vector3(float x, float y, float z)
    :x(x), y(y), z(z)
{}

Vector3::Vector3(const Vector3& v)
    :x(v.x), y(v.y), z(v.z)
{}

Vector3& Vector3::operator=(const Vector3& vect){
    x = vect.x;
    y = vect.y;
    z = vect.z;

    return *this;
}

Vector3::~Vector3(){}

float Vector3::length() const {
    return sqrt(x * x + y * y + z * z);
}

Vector3& Vector3::lerp(const Vector3& a, const Vector3& b, float t, Vector3& dest){
    dest.x = a.x + ((b.x - a.x) * t);
    dest.y = a.y + ((b.y - a.y) * t);
    dest.z = a.z + ((b.z - a.z) * t);

    return dest;
}

Vector3& Vector3::sub(const Vector3& left, const Vector3& right, Vector3& dest){
    dest.x = left.x - right.x;
    dest.y = left.y - right.y;
    dest.z = left.z - right.z;

    return dest;
}

Vector3& Vector3::add(const Vector3& left, const Vector3& right, Vector3& dest){
    dest.x = left.x + right.x;
    dest.y = left.y + right.y;
    dest.z = left.z + right.z;

    return dest;
}

Vector3& Vector3::cross(const Vector3& one, const Vector3& two, Vector3& dest){
    dest.x = (one.y * two.z) - (one.z * two.y);
    dest.y = (one.z * two.x) - (one.x * two.z);
    dest.z = (one.x * two.y) - (one.y * two.x);

    return dest;
}

float Vector3::dot(const Vector3& left, const Vector3& right){
    return left.x * right.x + left.y * right.y + left.z * right.z;
}


Vector3& Vector3::operator%=(const Vector3& right){
    Vector3::cross(*this, right, *this);
    return *this;
}

Vector3& Vector3::operator+=(const Vector3& right){
    Vector3::add(*this, right, *this);
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& right){
    Vector3::sub(*this, right, *this);
    return *this;
}

Vector3 Vector3::operator+(const Vector3& right) const{
    Vector3 ret;
    Vector3::add(*this, right, ret);
    return ret;
}

Vector3 Vector3::operator-(const Vector3& right) const{
    Vector3 ret;
    Vector3::sub(*this, right, ret);
    return ret;
}

Vector3 Vector3::operator%(const Vector3& right) const{
    Vector3 ret;
    Vector3::cross(*this, right, ret);
    return ret;
}

float Vector3::operator*(const Vector3& b) const {
    return Vector3::dot(*this, b);
}

float Vector3::angle(const Vector3& left, const Vector3& right){
    float dot = Vector3::dot(left, right);
    return acos(dot/(left.length() * right.length()));
}

float Vector3::dist(const Vector3& a, const Vector3& b){
    float x = a.x - b.x;
    float y = a.y - b.y;
    float z = a.z - b.z;

    return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::getNormalized(const Vector3& input){
    Vector3 ret(input);
    ret.normalize();
    return ret;
}

Vector3& Vector3::scale(float s){
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

Vector3& Vector3::normalize(){
    float mag = length();

    x /= mag;
    y /= mag;
    z /= mag;

    return *this;
}

void Vector3::print() const{
    std::cout << x << " " << y << " " << z << "\n";
}

