#ifndef INCLUDE_VECTOR4_H
#define INCLUDE_VECTOR4_H

class Vector4{
	public:
		Vector4(float x = 0, float y = 0, float z = 0, float w = 0);
		Vector4(const Vector4& vect);
		Vector4& operator=(const Vector4& vect);

		virtual ~Vector4();

		float length() const;
		static Vector4& add(const Vector4& left, const Vector4& right, Vector4& dest);
		static Vector4& sub(const Vector4& left, const Vector4& right, Vector4& dest);
		static Vector4& lerp(const Vector4& a, const Vector4& b, float t, Vector4& dest);

		Vector4& operator+=(const Vector4& right);
		Vector4& operator-=(const Vector4& right);
		Vector4 operator+(const Vector4& right) const;
		Vector4 operator-(const Vector4& right) const;
		float operator*(const Vector4& b) const;

		static float dot(const Vector4& a, const Vector4& b);
		static float dist(const Vector4& a, const Vector4& b);
		static Vector4 getNormalized(const Vector4& v);

		Vector4& scale(float s);
		Vector4& normalize();

		void print() const;

		float x, y, z, w;
};

#endif
