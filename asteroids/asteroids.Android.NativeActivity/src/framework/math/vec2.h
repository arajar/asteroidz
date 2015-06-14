#pragma once

//////////////////////////////////////////////////////////////////////////

namespace math
{
	template<typename T>
	struct vec2
	{
		union
		{
			T value_[2];
			struct
			{
				T x;
				T y;
			};
		};

		vec2() : value_{ 0 } {}
		vec2(T value) : value_{ value } {}
		vec2(T x, T y) : value_{ x, y } {}

		inline T* ptr() { return value_; }
		inline const float dot(const vec2<T> other) const
		{
			return x * other.x + y * other.y;
		}

		inline const float length()
		{
			return sqrtf(x*x + y*y);
		}

		inline const float length2()
		{
			return x*x + y*y;
		}

		inline vec2<T>& operator+=(const T& other)
		{
			x += other;
			y += other;
			return *this;
		}

		inline vec2<T>& operator+=(const vec2<T>& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		inline const vec2<T> operator+(const T& other) const
		{
			return vec2<T>(x + other, y + other);
		}

		inline const vec2<T> operator+(const vec2<T>& other) const
		{
			return vec2<T>(x + other.x, y + other.y);
		}

		inline vec2<T>& operator-=(const T& other)
		{
			x -= other;
			y -= other;
			return *this;
		}

		inline vec2<T>& operator-=(const vec2<T>& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		inline const vec2<T> operator-(const T& other) const
		{
			return vec2<T>(x - other, y - other);
		}

		inline const vec2<T> operator-(const vec2<T>& other) const
		{
			return vec2<T>(x - other.x, y - other.y);
		}

		inline vec2<T>& operator*=(const T& other)
		{
			x *= other;
			y *= other;
			return *this;
		}

		inline vec2<T>& operator*=(const vec2<T>& other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		inline const vec2<T> operator*(const T& other) const
		{
			return vec2<T>(x * other, y * other);
		}

		inline const vec2<T> operator*(const vec2<T>& other) const
		{
			return vec2<T>(x * other.x, y * other.y);
		}

		inline vec2<T>& operator/=(const T& other)
		{
			x /= other;
			y /= other;
			return *this;
		}

		inline vec2<T>& operator/=(const vec2<T>& other)
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}

		inline const vec2<T> operator/(const T& other) const
		{
			return vec2<T>(x / other, y / other);
		}

		inline const vec2<T> operator/(const vec2<T>& other) const
		{
			return vec2<T>(x / other.x, y / other.y);
		}
	};

	using vec2d = vec2<GLint>;
	using vec2f = vec2<GLfloat>;
}
