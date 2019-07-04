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
             
        static void add(const Matrix44& left, const Matrix44& right, Matrix44& dest);
        static void sub(const Matrix44& left, const Matrix44& right, Matrix44& dest);
        static void mul(const Matrix44& left, const Matrix44& right, Matrix44& dest);
        static void trans(const Matrix44& left, const Vector4& right, Vector4& dest);
              
        void setIdentity();
        void setZero();
        void transpose();
        void invert();  
        void negate();        
		void print() const;

        void scale(const Vector3& scale);
        void rotate(const Vector3& eulerAxis, float angle);
                                               
        float det() const;                     
                                               
        float m00, m01, m02, m03;              
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
};                      
                        
#endif

