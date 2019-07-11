#ifndef INCLUDE_QUATERNION_H
#define INCLUDE_QUATERNION_H

class Vector3;
class Vector4;
class Matrix44;

class Quaternion
{
    public: 
        Quaternion(float x = 0, float y = 0, float z = 0, float w = 1);
        Quaternion(const Vector3& axis, float angle);
        Quaternion(const Quaternion& q);

        Quaternion& setIdentity();
        float length() const; 
        Quaternion& normalize();
        Quaternion& negate();

        Quaternion operator*(const Quaternion& right);
        Quaternion& operator*=(const Quaternion& right);
        Vector3 operator*(const Vector3& right);
        Vector4 operator*(const Vector4& right); 

        Matrix44 toMatrix() const;
        Quaternion& setToAxisAngle(const Vector3& axis, float angle);
        static Quaternion slerp(const Quaternion& a, const Quaternion& b, float blend);
        Quaternion& lookRotation(const Vector3& forward, const Vector3& up);
        Quaternion& setMatrix(const Matrix44& matrix);

        float x, y, z, w;
};

#endif

