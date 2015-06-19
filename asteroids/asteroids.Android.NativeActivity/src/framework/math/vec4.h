#pragma once

//////////////////////////////////////////////////////////////////////////

namespace m
{
	template<typename T>
	struct vec4_type
	{
		union
		{
			struct { T x; T y; T z; T w; };
			struct { T r; T g; T b; T a; };
		};

		vec4_type() : x(), y(), z(), w() {}
		vec4_type(T value) : x(value), y(value), z(value), w(value) {}
		vec4_type(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		vec4_type(const vec2_type<T>& other) : x(other.x), y(other.y), z(0), w(0) {}
		vec4_type(const vec3_type<T>& other) : x(other.x), y(other.y), z(other.z), w(0) {}
		vec4_type(const vec4_type<T>& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

		T& operator[](int i) { return (&x)[i]; }
		const T& operator[](int i) const { return (&x)[i]; }

		vec4_type<T> operator+() const { return vec4_type<T>(+x, +y, +z, +w); }
		vec4_type<T> operator-() const { return vec4_type<T>(-x, -y, -z, -w); }

		vec4_type<T> operator+(const vec4_type<T>& other) const { return vec4_type<T>(x + other.x, y + other.y, z + other.z, w + other.w); }
		vec4_type<T> operator-(const vec4_type<T>& other) const { return vec4_type<T>(x - other.x, y - other.y, z - other.z, w - other.w); }
		vec4_type<T> operator*(const vec4_type<T>& other) const { return vec4_type<T>(x*other.x, y*other.y, z*other.z, w*other.w); }
		vec4_type<T> operator/(const vec4_type<T>& other) const { return vec4_type<T>(x / other.x, y / other.y, z / other.z, w / other.w); }

		friend vec4_type<T> operator+(float s, const vec4_type<T>& vec) { return vec4_type<T>(s + vec.x, s + vec.y, s + vec.z, s + vec.w); }
		friend vec4_type<T> operator-(float s, const vec4_type<T>& vec) { return vec4_type<T>(s - vec.x, s - vec.y, s - vec.z, s - vec.w); }
		friend vec4_type<T> operator*(float s, const vec4_type<T>& vec) { return vec4_type<T>(s * vec.x, s * vec.y, s * vec.z, s * vec.w); }
		friend vec4_type<T> operator/(float s, const vec4_type<T>& vec) { return vec4_type<T>(s / vec.x, s / vec.y, s / vec.z, s / vec.w); }
		friend vec4_type<T> operator+(const vec4_type<T>& vec, float s) { return vec4_type<T>(s + vec.x, s + vec.y, s + vec.z, s + vec.w); }
		friend vec4_type<T> operator-(const vec4_type<T>& vec, float s) { return vec4_type<T>(vec.x - s, vec.y - s, vec.z - s, vec.w - s); }
		friend vec4_type<T> operator*(const vec4_type<T>& vec, float s) { return vec4_type<T>(s * vec.x, s * vec.y, s * vec.z, s * vec.w); }
		friend vec4_type<T> operator/(const vec4_type<T>& vec, float s) { return vec4_type<T>(vec.x / s, vec.y / s, vec.z / s, vec.w / s); }

		vec4_type<T>& operator+=(const vec4_type<T>& other) { return *this = *this + other; }
		vec4_type<T>& operator-=(const vec4_type<T>& other) { return *this = *this - other; }
		vec4_type<T>& operator*=(const vec4_type<T>& other) { return *this = *this * other; }
		vec4_type<T>& operator/=(const vec4_type<T>& other) { return *this = *this / other; }
		vec4_type<T>& operator+=(T other) { return *this = *this + other; }
		vec4_type<T>& operator-=(T other) { return *this = *this - other; }
		vec4_type<T>& operator*=(T other) { return *this = *this * other; }
		vec4_type<T>& operator/=(T other) { return *this = *this / other; }

		bool operator==(const vec4_type<T>& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
		bool operator!=(const vec4_type<T>& other) const { return x != other.x || y != other.y || z != other.z || w != other.w; }

		friend float length(const vec4_type<T> &v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
		friend float dot(const vec4_type<T> &a, const vec4_type<T> &b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
		friend float max(const vec4_type<T> &v) { return fmaxf(fmaxf(v.x, v.y), fmaxf(v.z, v.w)); }
		friend float min(const vec4_type<T> &v) { return fminf(fminf(v.x, v.y), fminf(v.z, v.w)); }
		friend vec4_type<T> max(const vec4_type<T> &a, const vec4_type<T> &b) { return vec4_type<T>(fmaxf(a.x, b.x), fmaxf(a.y, b.y), fmaxf(a.z, b.z), fmaxf(a.w, b.w)); }
		friend vec4_type<T> min(const vec4_type<T> &a, const vec4_type<T> &b) { return vec4_type<T>(fminf(a.x, b.x), fminf(a.y, b.y), fminf(a.z, b.z), fminf(a.w, b.w)); }
		friend vec4_type<T> floor(const vec4_type<T> &v) { return vec4_type<T>(floorf(v.x), floorf(v.y), floorf(v.z), floorf(v.w)); }
		friend vec4_type<T> ceil(const vec4_type<T> &v) { return vec4_type<T>(ceilf(v.x), ceilf(v.y), ceilf(v.z), ceilf(v.w)); }
		friend vec4_type<T> abs(const vec4_type<T> &v) { return vec4_type<T>(fabsf(v.x), fabsf(v.y), fabsf(v.z), fabsf(v.w)); }
		friend vec4_type<T> fract(const vec4_type<T> &v) { return v - floor(v); }
		friend vec4_type<T> normalized(const vec4_type<T> &v) { return v / length(v); }

	};

	using vec4 = vec4_type<GLfloat>;
}
