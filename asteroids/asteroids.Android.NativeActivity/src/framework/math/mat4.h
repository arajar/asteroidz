#pragma once

namespace math
{
	template<typename T>
	struct mat4_type
	{
		vec4_type<T> val[4];

		mat4_type() : mat4_type(1) {}

		mat4_type(const T& s)
		{
			identity(s);
		}

		mat4_type(const mat4_type<T>& m)
		{
			val[0] = m[0];
			val[1] = m[1];
			val[2] = m[2];
			val[3] = m[3];
		}

		mat4_type(const vec4_type<T>& r0, const vec4_type<T>& r1, const vec4_type<T>& r2, const vec4_type<T>& r3)
		{
			val[0] = r0;
			val[1] = r1;
			val[2] = r2;
			val[3] = r3;
		}

		mat4_type(
			T m00, T m01, T m02, T m03,
			T m10, T m11, T m12, T m13,
			T m20, T m21, T m22, T m23,
			T m30, T m31, T m32, T m33)
		{
			val[0] = vec4_type<T>(m00, m01, m02, m03);
			val[1] = vec4_type<T>(m10, m11, m12, m13);
			val[2] = vec4_type<T>(m20, m21, m22, m23);
			val[3] = vec4_type<T>(m30, m31, m32, m33);
		}

		vec4_type<T>& operator[](int i)
		{
			return val[i];
		}

		const vec4_type<T>& operator[](int i) const
		{
			return val[i];
		}

		void identity(T v = 1)
		{
			val[0] = vec4_type<T>(static_cast<T>(v), 0, 0, 0);
			val[1] = vec4_type<T>(0, static_cast<T>(v), 0, 0);
			val[2] = vec4_type<T>(0, 0, static_cast<T>(v), 0);
			val[3] = vec4_type<T>(0, 0, 0, static_cast<T>(v));
		}

		mat4_type<T>& operator=(const mat4_type<T>& m)
		{
			val[0] = m[0];
			val[1] = m[1];
			val[2] = m[2];
			val[3] = m[3];
			return *this;
		}

		mat4_type<T>& operator+=(const mat4_type<T>& m)
		{
			val[0] += m[0];
			val[1] += m[1];
			val[2] += m[2];
			val[3] += m[3];
			return *this;
		}

		mat4_type<T>& operator-=(const mat4_type<T>& m)
		{
			val[0] -= m[0];
			val[1] -= m[1];
			val[2] -= m[2];
			val[3] -= m[3];
			return *this;
		}

		mat4_type<T>& operator*=(const mat4_type<T>& m)
		{
			return *this = *this * m;
		}

		mat4_type<T>& operator/=(const mat4_type<T>& m)
		{
			return *this = *this * inverse(m);
		}
	};

	using mat4 = mat4_type<GLfloat>;

	template<typename T>
	mat4_type<T> operator*(const mat4_type<T>& m1, const mat4_type<T>& m2)
	{
		const auto a0 = m1[0];
		const auto a1 = m1[1];
		const auto a2 = m1[2];
		const auto a3 = m1[3];

		const auto b0 = m2[0];
		const auto b1 = m2[1];
		const auto b2 = m2[2];
		const auto b3 = m2[3];

		mat4_type<T> res;
		res[0] = a0 * b0[0] + a1 * b0[1] + a2 * b0[2] + a3 * b0[3];
		res[1] = a0 * b1[0] + a1 * b1[1] + a2 * b1[2] + a3 * b1[3];
		res[2] = a0 * b2[0] + a1 * b2[1] + a2 * b2[2] + a3 * b2[3];
		res[3] = a0 * b3[0] + a1 * b3[1] + a2 * b3[2] + a3 * b3[3];
		return res;
	}
}
