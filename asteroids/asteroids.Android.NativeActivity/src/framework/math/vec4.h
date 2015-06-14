#pragma once

//////////////////////////////////////////////////////////////////////////

namespace math
{
	template<typename T>
	struct vec4
	{
		union
		{
			T value_[4];
			struct
			{
				T x;
				T y;
				T z;
				T w;
			};
		};

		vec4() : value_{ 0 } {}
		vec4(T value) : value_{ value } {}
		vec4(T x, T y, T z, T w) : value_{ x, y, z, w } {}

		T& operator[](int index)
		{
			return value_[index];
		}

		inline T* ptr() { return value_; }
		inline const float dot(const vec4<T> other) const
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		inline const float length()
		{
			return sqrtf(x*x + y*y + z*z + w*w);
		}

		inline const float length2()
		{
			return x*x + y*y + z*z + w*w;
		}

		inline vec4<T>& operator+=(const T& other)
		{
			x += other;
			y += other;
			z += other;
			w += other;
			return *this;
		}

		inline vec4<T>& operator+=(const vec4<T>& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		inline const vec4<T> operator+(const T& other) const
		{
			return vec4<T>(x + other, y + other, z + other, w + other);
		}

		inline const vec4<T> operator+(const vec4<T>& other) const
		{
			return vec4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		inline vec4<T>& operator-=(const T& other)
		{
			x -= other;
			y -= other;
			z -= other;
			w -= other;
			return *this;
		}

		inline vec4<T>& operator-=(const vec4<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		inline const vec4<T> operator-(const T& other) const
		{
			return vec4<T>(x - other, y - other, z - other), w - other;
		}

		inline const vec4<T> operator-(const vec4<T>& other) const
		{
			return vec4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		inline vec4<T>& operator*=(const T& other)
		{
			x *= other;
			y *= other;
			z *= other;
			w *= other;
			return *this;
		}

		inline vec4<T>& operator*=(const vec4<T>& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;
		}

		inline const vec4<T> operator*(const T& other) const
		{
			return vec4<T>(x * other, y * other, z * other, w * other);
		}

		inline const vec4<T> operator*(const vec4<T>& other) const
		{
			return vec4<T>(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		inline vec4<T>& operator/=(const T& other)
		{
			x /= other;
			y /= other;
			z /= other;
			w /= other;
			return *this;
		}

		inline vec4<T>& operator/=(const vec4<T>& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return *this;
		}

		inline const vec4<T> operator/(const T& other) const
		{
			return vec4<T>(x / other, y / other, z / other, w / other);
		}

		inline const vec4<T> operator/(const vec4<T>& other) const
		{
			return vec4<T>(x / other.x, y / other.y, z / other.z, w / other.w);
		}
	};

	using vec4d = vec4<GLint>;
	using vec4f = vec4<GLfloat>;
}
