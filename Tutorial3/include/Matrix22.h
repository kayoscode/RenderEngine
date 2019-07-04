#ifndef INCLUDE_MATRIX22_H
#define INCLUDE_MATRIX22_H

class Vector2;

class Matrix22{
    public:
        Matrix22();
        Matrix22(const Matrix22& m);
        Matrix22& operator=(const Matrix22& m);

        virtual ~Matrix22(); 

        static void add(const Matrix22& left, const Matrix22& right, Matrix22& dest);
        static void sub(const Matrix22& left, const Matrix22& right, Matrix22& dest);
        static void mul(const Matrix22& left, const Matrix22& right, Matrix22& dest);
        static void trans(const Matrix22& left, const Vector2& right, Vector2& dest);
    
        void setIdentity();
        void setZero();
        void transpose();
        void invert();
        void negate();
		void print() const;

        float det() const;

        float m00, m01, m10, m11;
};  
    
#endif

