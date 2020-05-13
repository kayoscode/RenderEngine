#ifndef INCLUDE_MATRIX44_H
#define INCLUDE_MATRIX44_H

class Vector3;
class Vector4;

class Matrix44{
    public:
        Matrix44();
        Matrix44(const Matrix44& m);
        Matrix44& operator=(const Matrix44& m);
    
        virtual ~Matrix44();

        static Matrix44& add(const Matrix44& left, const Matrix44& right, Matrix44& dest);
        static Matrix44& sub(const Matrix44& left, const Matrix44& right, Matrix44& dest);
        static Matrix44& mul(const Matrix44& left, const Matrix44& right, Matrix44& dest);
        static Vector4& trans(const Matrix44& left, const Vector4& right, Vector4& dest);

        Matrix44& operator+=(const Matrix44& right);
        Matrix44& operator-=(const Matrix44& right);
        Matrix44& operator*=(const Matrix44& right);
        Matrix44 operator+(const Matrix44& right) const;
        Matrix44 operator-(const Matrix44& right) const;
        Matrix44 operator*(const Matrix44& right) const;
        Vector4 operator*(const Vector4& vec) const;

        Matrix44& setIdentity(); 
        Matrix44& setZero();
        Matrix44& transpose();
        Matrix44& invert();
        Matrix44& negate();
        void print() const;

        Matrix44& scale(const Vector3& scale);
        Matrix44& rotate(const Vector3& eulerAxis, float angle);
        Matrix44& translate(const Vector3& translation);

        float det() const;
    
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
};  
    
#endif

