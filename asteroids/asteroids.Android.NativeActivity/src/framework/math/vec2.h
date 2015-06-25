#pragma once

//////////////////////////////////////////////////////////////////////////

namespace m
{

	template<typename T>
	struct vec2_type
	{
		union
		{
			T xy[2];
			T uv[2];
			T rg[2];
			struct { T x; T y; };
			struct { T u; T v; };
			struct { T r; T g; };
		};

		vec2_type() : x(), y() {}
		vec2_type(T value) : x(value), y(value) {}
		vec2_type(T x, T y) : x(x), y(y) {}
		vec2_type(const vec2_type<T>& other) : x(other.x), y(other.y) {}

		vec2_type<T> operator+() const { return vec2_type<T>(+x, +y); }
		vec2_type<T> operator-() const { return vec2_type<T>(-x, -y); }

		vec2_type<T> operator+(const vec2_type<T>& other) const { return vec2_type<T>(x + other.x, y + other.y); }
		vec2_type<T> operator-(const vec2_type<T>& other) const { return vec2_type<T>(x - other.x, y - other.y); }
		vec2_type<T> operator*(const vec2_type<T>& other) const { return vec2_type<T>(x*other.x, y*other.y); }
		vec2_type<T> operator/(const vec2_type<T>& other) const { return vec2_type<T>(x / other.x, y / other.y); }
		vec2_type<T> operator+(T other) const { return vec2_type<T>(x + other, y + other); }
		vec2_type<T> operator-(T other) const { return vec2_type<T>(x - other, y - other); }
		vec2_type<T> operator*(T other) const { return vec2_type<T>(x*other, y*other); }
		vec2_type<T> operator/(T other) const { return vec2_type<T>(x / other, y / other); }

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

		static float length(const vec2_type<T> &v) { return sqrtf(v.x * v.x + v.y * v.y); }
		static float dot(const vec2_type<T> &a, const vec2_type<T> &b) { return a.x * b.x + a.y * b.y; }
		static float max(const vec2_type<T> &v) { return fmaxf(v.x, v.y); }
		static float min(const vec2_type<T> &v) { return fminf(v.x, v.y); }
		static vec2_type<T> max(const vec2_type<T> &a, const vec2_type<T> &b) { return vec2_type<T>(fmaxf(a.x, b.x), fmaxf(a.y, b.y)); }
		static vec2_type<T> min(const vec2_type<T> &a, const vec2_type<T> &b) { return vec2_type<T>(fminf(a.x, b.x), fminf(a.y, b.y)); }
		static vec2_type<T> floor(const vec2_type<T> &v) { return vec2_type<T>(floorf(v.x), floorf(v.y)); }
		static vec2_type<T> ceil(const vec2_type<T> &v) { return vec2_type<T>(ceilf(v.x), ceilf(v.y)); }
		static vec2_type<T> abs(const vec2_type<T> &v) { return vec2_type<T>(fabsf(v.x), fabsf(v.y)); }
		static vec2_type<T> fract(const vec2_type<T> &v) { return v - floor(v); }
		static vec2_type<T> normalized(const vec2_type<T> &v) { return v / length(v); }

	};

	using vec2 = vec2_type<GLfloat>;
}
