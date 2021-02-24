#ifndef INCLUDE_MATRIX22_H
#define INCLUDE_MATRIX22_H

class Vector2;

class Matrix22{
    public:
        Matrix22();
        Matrix22(const Matrix22& m); 
        Matrix22& operator=(const Matrix22& m); 

        virtual ~Matrix22();

        static Matrix22& add(const Matrix22& left, const Matrix22& right, Matrix22& dest);
        static Matrix22& sub(const Matrix22& left, const Matrix22& right, Matrix22& dest);
        static Matrix22& mul(const Matrix22& left, const Matrix22& right, Matrix22& dest);
        static Vector2& trans(const Matrix22& left, const Vector2& right, Vector2& dest);

        Matrix22& operator+=(const Matrix22& right);
        Matrix22& operator-=(const Matrix22& right);
        Matrix22& operator*=(const Matrix22& right);
        Matrix22 operator+(const Matrix22& right) const;
        Matrix22 operator-(const Matrix22& right) const;
        Matrix22 operator*(const Matrix22& right) const;
        Vector2 operator*(const Vector2& vec) const;

        Matrix22& setIdentity();
        Matrix22& setZero();
        Matrix22& transpose();
        Matrix22& invert();
        Matrix22& negate();
        void print() const;

        float det() const;

        float m00, m01;
        float m10, m11;
};

#endif

