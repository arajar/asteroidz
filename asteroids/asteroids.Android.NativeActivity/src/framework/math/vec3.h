#pragma once

//////////////////////////////////////////////////////////////////////////

namespace math
{
	template<typename T>
	struct vec3_type
	{
		union
		{
			T xyz[3];
			T uvw[3];
			T rgb[3];
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
		vec3_type<T> operator*(const vec3_type<T>& other) const { return vec3_type<T>(x * other.x, y * other.y, z * other.z); }
		vec3_type<T> operator/(const vec3_type<T>& other) const { return vec3_type<T>(x / other.x, y / other.y, z / other.z); }

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
	};

	using vec3 = vec3_type<GLfloat>;
}
