#pragma once

//////////////////////////////////////////////////////////////////////////

namespace math
{
	template<typename T>
	struct vec3
	{
		union
		{
			T value_[3];
			struct
			{
				T x;
				T y;
				T z;
			};
		};

		vec3() : value_{ 0 } {}
		vec3(T value) : value_{ value } {}
		vec3(T x, T y, T z) : value_{ x, y, z } {}

		inline T* ptr() { return value_; }
		inline const float dot(const vec3<T> other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		inline const float length()
		{
			return sqrtf(x*x + y*y + z*z);
		}

		inline const float length2()
		{
			return x*x + y*y + z*z;
		}

		inline vec3<T>& operator+=(const T& other)
		{
			x += other;
			y += other;
			z += other;
			return *this;
		}

		inline vec3<T>& operator+=(const vec3<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		inline const vec3<T> operator+(const T& other) const
		{
			return vec3<T>(x + other, y + other, z + other);
		}

		inline const vec3<T> operator+(const vec3<T>& other) const
		{
			return vec3<T>(x + other.x, y + other.y, z + other.z);
		}

		inline vec3<T>& operator-=(const T& other)
		{
			x -= other;
			y -= other;
			z -= other;
			return *this;
		}

		inline vec3<T>& operator-=(const vec3<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		inline const vec3<T> operator-(const T& other) const
		{
			return vec3<T>(x - other, y - other, z - other);
		}

		inline const vec3<T> operator-(const vec3<T>& other) const
		{
			return vec3<T>(x - other.x, y - other.y, z - other.z);
		}

		inline vec3<T>& operator*=(const T& other)
		{
			x *= other;
			y *= other;
			z *= other;
			return *this;
		}

		inline vec3<T>& operator*=(const vec3<T>& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		inline const vec3<T> operator*(const T& other) const
		{
			return vec3<T>(x * other, y * other, z * other);
		}

		inline const vec3<T> operator*(const vec3<T>& other) const
		{
			return vec3<T>(x * other.x, y * other.y, z * other.z);
		}

		inline vec3<T>& operator/=(const T& other)
		{
			x /= other;
			y /= other;
			z /= other;
			return *this;
		}

		inline vec3<T>& operator/=(const vec3<T>& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		inline const vec3<T> operator/(const T& other) const
		{
			return vec3<T>(x / other, y / other, z / other);
		}

		inline const vec3<T> operator/(const vec3<T>& other) const
		{
			return vec3<T>(x / other.x, y / other.y, z / other.z);
		}
	};

	using vec3d = vec3<GLint>;
	using vec3f = vec3<GLfloat>;
}
