#pragma once

//////////////////////////////////////////////////////////////////////////

namespace math
{
	template<typename T>
	struct vec3_type
	{
		union { T x, u, r; };
		union { T y, v, g; };
		union { T z, w, b; };

		vec3_type() : x(0), y(0), z(0) {}
		vec3_type(T value) : x(value), y(value), z(value) {}
		vec3_type(T x, T y, T z) : x(x), y(y), z(z) {}
		vec3_type(const vec3_type<T>& other) : x(other.x), y(other.y), z(other.z) {}

		T& operator[](int i) { return (&x)[i]; }
		const T& operator[](int i) const { return (&x)[i]; }

		vec3_type<T> operator+() const { return vec3_type<T>(+x, +y, +z); }
		vec3_type<T> operator-() const { return vec3_type<T>(-x, -y, -z); }

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

	template<typename T>
	vec3_type<T> operator+(const vec3_type<T>& a, const T& b)
	{
		return vec3_type<T>(a.x + b, a.y + b, a.z + b);
	}

	template<typename T>
	vec3_type<T> operator+(const T& a, const vec3_type<T>& b)
	{
		return vec3_type<T>(a + b.x, a + b.y, a + b.z);
	}

	template<typename T>
	vec3_type<T> operator+(const vec3_type<T>& a, const vec3_type<T>& b)
	{
		return vec3_type<T>(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	template<typename T>
	vec3_type<T> operator-(const vec3_type<T>& a, const T& b)
	{
		return vec3_type<T>(a.x - b, a.y - b, a.z - b);
	}

	template<typename T>
	vec3_type<T> operator-(const T& a, const vec3_type<T>& b)
	{
		return vec3_type<T>(a - b.x, a - b.y, a - b.z);
	}

	template<typename T>
	vec3_type<T> operator-(const vec3_type<T>& a, const vec3_type<T>& b)
	{
		return vec3_type<T>(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	template<typename T>
	vec3_type<T> operator*(const vec3_type<T>& a, const T& b)
	{
		return vec3_type<T>(a.x * b, a.y * b, a.z * b);
	}

	template<typename T>
	vec3_type<T> operator*(const T& a, const vec3_type<T>& b)
	{
		return vec3_type<T>(a * b.x, a * b.y, a * b.z);
	}

	template<typename T>
	vec3_type<T> operator*(const vec3_type<T>& a, const vec3_type<T>& b)
	{
		return vec3_type<T>(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	template<typename T>
	vec3_type<T> operator/(const vec3_type<T>& a, const T& b)
	{
		return vec3_type<T>(a.x / b, a.y / b, a.z / b);
	}

	template<typename T>
	vec3_type<T> operator/(const T& a, const vec3_type<T>& b)
	{
		return vec3_type<T>(a / b.x, a / b.y, a / b.z);
	}

	template<typename T>
	vec3_type<T> operator/(const vec3_type<T>& a, const vec3_type<T>& b)
	{
		return vec3_type<T>(a.x / b.x, a.y / b.y, a.z / b.z);
	}
}
