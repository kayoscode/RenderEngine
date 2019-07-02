#ifndef INCLUDE_VECTOR2_H
#define INCLUDE_VECTOR2_H

class Vector2{
	public:
		Vector2(float x = 0, float y = 0);
		Vector2(const Vector2& vect);
		Vector2& operator=(const Vector2& vect);

		virtual ~Vector2();

		float length() const;
		static void add(const Vector2& left, const Vector2& right, Vector2& dest);
		static void sub(const Vector2& left, const Vector2& right, Vector2& dest);
		static void mul(const Vector2& left, const Vector2& right, Vector2& dest);

		static float dot(const Vector2& a, const Vector2& b);
		static float angle(const Vector2& a, const Vector2& b);
		static float dist(const Vector2& a, const Vector2& b);
		static Vector2 getNormalized(const Vector2& v);

		void scale(float s);
		void normalize();

		inline float getX() const {return x;}
		inline float getY() const {return y;}

		inline void setX(float x){this->x = x;}
		inline void setY(float y){this->y = y;}

	private:
		float x, y;
};

#endif
