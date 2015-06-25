#pragma once

//////////////////////////////////////////////////////////////////////////

namespace m
{
	template<typename T>
	struct vec3_type
	{
		union
		{
			struct { T x; T y; T z; };
			struct { T u; T v; T w; };
			struct { T r; T g; T b; };
		};

		vec3_type() : x(), y(), z() {}
		vec3_type(T value) : x(value), y(value), z(value) {}
		vec3_type(T x, T y, T z) : x(x), y(y), z(z) {}
		vec3_type(const vec2_type<T>& other) : x(other.x), y(other.y), z(0) {}
		vec3_type(const vec3_type<T>& other) : x(other.x), y(other.y), z(other.z) {}

		T& operator[](int i) { return (&x)[i]; }
		const T& operator[](int i) const { return (&x)[i]; }

		vec3_type<T> operator+() const { return vec3_type<T>(+x, +y, +z); }
		vec3_type<T> operator-() const { return vec3_type<T>(-x, -y, -z); }

		vec3_type<T> operator+(const vec3_type<T>& other) const { return vec3_type<T>(x + other.x, y + other.y, z + other.z); }
		vec3_type<T> operator-(const vec3_type<T>& other) const { return vec3_type<T>(x - other.x, y - other.y, z - other.z); }
		vec3_type<T> operator*(const vec3_type<T>& other) const { return vec3_type<T>(x*other.x, y*other.y, z*other.z); }
		vec3_type<T> operator/(const vec3_type<T>& other) const { return vec3_type<T>(x / other.x, y / other.y, z / other.z); }
		vec3_type<T> operator+(T other) const { return vec3_type<T>(x + other, y + other, z + other); }
		vec3_type<T> operator-(T other) const { return vec3_type<T>(x - other, y - other, z - other); }
		vec3_type<T> operator*(T other) const { return vec3_type<T>(x*other, y*other, z*other); }
		vec3_type<T> operator/(T other) const { return vec3_type<T>(x / other, y / other, z / other); }

		friend vec3_type<T> operator+(float s, const vec3_type<T>& vec) { return vec3_type<T>(s + vec.x, s + vec.y, s + vec.z); }
		friend vec3_type<T> operator-(float s, const vec3_type<T>& vec) { return vec3_type<T>(s - vec.x, s - vec.y, s - vec.z); }
		friend vec3_type<T> operator*(float s, const vec3_type<T>& vec) { return vec3_type<T>(s * vec.x, s * vec.y, s * vec.z); }
		friend vec3_type<T> operator/(float s, const vec3_type<T>& vec) { return vec3_type<T>(s / vec.x, s / vec.y, s / vec.z); }

		vec3_type<T>& operator+=(const vec3_type<T>& other) { return *this = *this + other; }
		vec3_type<T>& operator-=(const vec3_type<T>& other) { return *this = *this - other; }
		vec3_type<T>& operator*=(const vec3_type<T>& other) { return *this = *this * other; }
		vec3_type<T>& operator/=(const vec3_type<T>& other) { return *this = *this / other; }
		vec3_type<T>& operator+=(T other) { return *this = *this + other; }
		vec3_type<T>& operator-=(T other) { return *this = *this - other; }
		vec3_type<T>& operator*=(T other) { return *this = *this * other; }
		vec3_type<T>& operator/=(T other) { return *this = *this / other; }

		bool operator==(const vec3_type<T>& other) const { return x == other.x && y == other.y && z == other.z; }
		bool operator!=(const vec3_type<T>& other) const { return x != other.x || y != other.y || z != other.z; }

		friend float length(const vec3_type<T> &v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }
		friend float dot(const vec3_type<T> &a, const vec3_type<T> &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
		friend float max(const vec3_type<T> &v) { return fmaxf(fmaxf(v.x, v.y), v.z); }
		friend float min(const vec3_type<T> &v) { return fminf(fminf(v.x, v.y), v.z); }
		friend vec3_type<T> max(const vec3_type<T> &a, const vec3_type<T> &b) { return vec3_type<T>(fmaxf(a.x, b.x), fmaxf(a.y, b.y), fmaxf(a.z, b.z)); }
		friend vec3_type<T> min(const vec3_type<T> &a, const vec3_type<T> &b) { return vec3_type<T>(fminf(a.x, b.x), fminf(a.y, b.y), fminf(a.z, b.z)); }
		friend vec3_type<T> floor(const vec3_type<T> &v) { return vec3_type<T>(floorf(v.x), floorf(v.y), floorf(v.z)); }
		friend vec3_type<T> ceil(const vec3_type<T> &v) { return vec3_type<T>(ceilf(v.x), ceilf(v.y), ceilf(v.z)); }
		friend vec3_type<T> abs(const vec3_type<T> &v) { return vec3_type<T>(fabsf(v.x), fabsf(v.y), fabsf(v.z)); }
		friend vec3_type<T> fract(const vec3_type<T> &v) { return v - floor(v); }
		friend vec3_type<T> normalized(const vec3_type<T> &v) { return v / length(v); }

		static vec3_type<T> cross(const vec3_type<T>& x, const vec3_type<T>& y)
		{
			return vec3_type<T>(
				x.y * y.z - y.y * x.z,
				x.z * y.x - y.z * x.x,
				x.x * y.y - y.x * x.y);
		}
	};

	using vec3 = vec3_type<GLfloat>;
}
