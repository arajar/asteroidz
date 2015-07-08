#pragma once

//////////////////////////////////////////////////////////////////////////

namespace math
{
	template<typename T>
	struct vec4_type
	{
		union { T x; T r; };
		union { T y; T g; };
		union { T z; T b; };
		union { T w; T a; };

		vec4_type() : x(0), y(0), z(0), w(0) {}
		vec4_type(T value) : x(value), y(value), z(value), w(value) {}
		vec4_type(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		vec4_type(const vec4_type<T>& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

		T& operator[](int i) { return (&x)[i]; }
		const T& operator[](int i) const { return (&x)[i]; }

		vec4_type<T> operator+() const { return vec4_type<T>(+x, +y, +z, +w); }
		vec4_type<T> operator-() const { return vec4_type<T>(-x, -y, -z, -w); }

		vec4_type<T> operator+(const vec4_type<T>& other) const
		{
			return vec4_type<T>(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		vec4_type<T> operator-(const vec4_type<T>& other) const
		{
			return vec4_type<T>(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		vec4_type<T> operator*(const vec4_type<T>& other) const
		{
			return vec4_type<T>(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		vec4_type<T> operator/(const vec4_type<T>& other) const
		{
			return vec4_type<T>(x / other.x, y / other.y, z / other.z, w / other.w);
		}

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
	};

	using vec4 = vec4_type<GLfloat>;
}
