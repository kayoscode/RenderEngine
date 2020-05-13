#include "Vector2.h"
#include <math.h>

#include <iostream>

Vector2::Vector2(float x, float  y)
    :x(x), y(y)
{}

Vector2::Vector2(const Vector2& v)
    :x(v.x), y(v.y)
{}

Vector2& Vector2::operator=(const Vector2& vect){
    x = vect.x;
    y = vect.y;

    return *this;
}

Vector2::~Vector2(){}

float Vector2::length() const {
    return sqrt(x * x + y * y);
}

Vector2& Vector2::lerp(const Vector2& a, const Vector2& b, float t, Vector2& dest){
    dest.x = a.x + ((b.x - a.x) * t);
    dest.y = a.y + ((b.y - a.y) * t);

    return dest;
}

Vector2& Vector2::sub(const Vector2& left, const Vector2& right, Vector2& dest){
    dest.x = left.x - right.x;
    dest.y = left.y - right.y;

    return dest;
}

Vector2& Vector2::add(const Vector2& left, const Vector2& right, Vector2& dest){
    dest.x = left.x + right.x;
    dest.y = left.y + right.y;

    return dest;
}

float Vector2::dot(const Vector2& left, const Vector2& right){
    return left.x * right.x + left.y * right.y;
}

Vector2& Vector2::operator+=(const Vector2& right){
    Vector2::add(*this, right, *this);
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& right){
    Vector2::sub(*this, right, *this);
    return *this;
}

Vector2 Vector2::operator+(const Vector2& right) const{
    Vector2 ret;
    Vector2::add(*this, right, ret);
    return ret;
}

Vector2 Vector2::operator-(const Vector2& right) const{
    Vector2 ret;
    Vector2::sub(*this, right, ret);
    return ret;
}

float Vector2::operator*(const Vector2& b) const{
    return Vector2::dot(*this, b);
}

float Vector2::angle(const Vector2& left, const Vector2& right){
    float dot = Vector2::dot(left, right);
    return acos(dot/(left.length() * right.length()));
}

float Vector2::dist(const Vector2& a, const Vector2& b){
    float x = a.x - b.x;
    float y = a.y - b.y;

    return sqrt(x * x + y * y);
}

Vector2 Vector2::getNormalized(const Vector2& input){
    Vector2 ret(input);
    ret.normalize();
    return ret;
}

Vector2& Vector2::scale(float s){
    x *= s;
    y *= s;

    return *this;
}

Vector2& Vector2::normalize(){
    float mag = length();

    x /= mag;
    y /= mag;

    return *this;
}


void Vector2::print() const{
    std::cout << x << " " << y << "\n";
}

