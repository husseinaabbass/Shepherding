#ifndef __Vector2_H__
#define __Vector2_H__

#define _USE_MATH_DEFINES
#include <cmath>


template <class T>
class Vector2 {
public:
	T x, y;

	Vector2() :x(0), y(0) {}
	Vector2(T x, T y) : x(x), y(y) {}
	Vector2(const Vector2& v) : x(v.x), y(v.y) {}

	Vector2& operator=(const Vector2& v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	Vector2 operator+(Vector2& v) {
		return Vector2(x + v.x, y + v.y);
	}
	Vector2 operator-(Vector2& v) {
		return Vector2(x - v.x, y - v.y);
	}

	Vector2& operator+=(Vector2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2& operator-=(Vector2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2 operator+(double s) {
		return Vector2(x + s, y + s);
	}
	Vector2 operator-(double s) {
		return Vector2(x - s, y - s);
	}
	Vector2 operator*(double s) {
		return Vector2(x * s, y * s);
	}
	Vector2 operator/(double s) {
		return Vector2(x / s, y / s);
	}

	Vector2 operator+(float s) {
		return Vector2(x + s, y + s);
	}
	Vector2 operator-(float s) {
		return Vector2(x - s, y - s);
	}
	Vector2 operator*(float s) {
		return Vector2(x * s, y * s);
	}
	Vector2 operator/(float s) {
		return Vector2(x / s, y / s);
	}



	Vector2& operator+=(double s) {
		x += s;
		y += s;
		return *this;
	}
	Vector2& operator-=(double s) {
		x -= s;
		y -= s;
		return *this;
	}
	Vector2& operator*=(double s) {
		x *= s;
		y *= s;
		return *this;
	}
	Vector2& operator/=(double s) {
		x /= s;
		y /= s;
		return *this;
	}

	Vector2& operator+=(float s) {
		x += s;
		y += s;
		return *this;
	}
	Vector2& operator-=(float s) {
		x -= s;
		y -= s;
		return *this;
	}
	Vector2& operator*=(float s) {
		x *= s;
		y *= s;
		return *this;
	}
	Vector2& operator/=(float s) {
		x /= s;
		y /= s;
		return *this;
	}


	void set(T x, T y) {
		this->x = x;
		this->y = y;
	}

	void rotate(double deg) {
		double theta = deg / 180.0 * M_PI;
		double c = cos(theta);
		double s = sin(theta);
		double tx = x * c - y * s;
		double ty = x * s + y * c;
		x = tx;
		y = ty;
	}

	Vector2& normalize() {
		if (length() == 0) return *this;
		*this *= (1.0 / length());
		return *this;
	}

	float dist(Vector2 v) const {
		Vector2 d(v.x - x, v.y - y);
		return d.length();
	}
	float length() const {
		return std::sqrt(x * x + y * y);
	}
	void truncate(double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}

	Vector2 ortho() const {
		return Vector2(y, -x);
	}

	static float dot(Vector2 v1, Vector2 v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	static float cross(Vector2 v1, Vector2 v2) {
		return (v1.x * v2.y) - (v1.y * v2.x);
	}

};

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;


#endif