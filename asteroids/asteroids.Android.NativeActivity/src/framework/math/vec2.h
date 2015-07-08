#pragma once

//////////////////////////////////////////////////////////////////////////

namespace math
{
	template<typename T>
	struct vec2_type
	{
		union { T x; T u; };
		union { T y; T v; };

		vec2_type() : x(0), y(0) {}
		vec2_type(T value) : x(value), y(value) {}
		vec2_type(T x, T y) : x(x), y(y) {}
		vec2_type(const vec2_type<T>& other) : x(other.x), y(other.y) {}

		vec2_type<T> operator+() const { return vec2_type<T>(+x, +y); }
		vec2_type<T> operator-() const { return vec2_type<T>(-x, -y); }

		vec2_type<T> operator+(const vec2_type<T>& other) const { return vec2_type<T>(x + other.x, y + other.y); }
		vec2_type<T> operator-(const vec2_type<T>& other) const { return vec2_type<T>(x - other.x, y - other.y); }
		vec2_type<T> operator*(const vec2_type<T>& other) const { return vec2_type<T>(x * other.x, y * other.y); }
		vec2_type<T> operator/(const vec2_type<T>& other) const { return vec2_type<T>(x / other.x, y / other.y); }

		vec2_type<T>& operator+=(const vec2_type<T>& other) { return *this = *this + other; }
		vec2_type<T>& operator-=(const vec2_type<T>& other) { return *this = *this - other; }
		vec2_type<T>& operator*=(const vec2_type<T>& other) { return *this = *this * other; }
		vec2_type<T>& operator/=(const vec2_type<T>& other) { return *this = *this / other; }
		vec2_type<T>& operator+=(T other) { return *this = *this + other; }
		vec2_type<T>& operator-=(T other) { return *this = *this - other; }
		vec2_type<T>& operator*=(T other) { return *this = *this * other; }
		vec2_type<T>& operator/=(T other) { return *this = *this / other; }

		bool operator==(const vec2_type<T>& other) const { return x == other.x && y == other.y; }
		bool operator!=(const vec2_type<T>& other) const { return x != other.x || y != other.y; }
	};

	using vec2 = vec2_type<GLfloat>;
}
