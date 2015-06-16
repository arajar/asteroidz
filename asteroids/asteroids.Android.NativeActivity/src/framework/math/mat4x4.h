#pragma once

namespace m
{
	template<typename T>
	struct mat4_type
	{
		vec4_type<T> val[4];

		mat4_type()
		{
			val[0] = vec4_type<T>(1, 0, 0, 0);
			val[1] = vec4_type<T>(0, 1, 0, 0);
			val[2] = vec4_type<T>(0, 0, 1, 0);
			val[3] = vec4_type<T>(0, 0, 0, 1);
		}

		mat4_type(T s) { val[0] = s; val[1] = s, val[2] = s; val[3] = s; }
		mat4_type(const vec4_type<T>& r0, const vec4_type<T>& r1, const vec4_type<T>& r2, const vec4_type<T>& r3)
		{
			val[0] = r0; val[1] = r1; val[2] = r2; val[3] = r3;
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

		vec4_type<T>& operator[](int i) { return val[i]; }
		const vec4_type<T>& operator[](int i) const { return val[i]; }

		mat4_type<T>& operator=(const mat4_type<T>& m)
		{
			val[0] = m[0];
			val[1] = m[1];
			val[2] = m[2];
			val[3] = m[3];
			return *this;
		}

		mat4_type<T>& operator+=(T s)
		{
			val[0] += s;
			val[1] += s;
			val[2] += s;
			val[3] += s;
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

		mat4_type<T>& operator-=(T s)
		{
			val[0] -= s;
			val[1] -= s;
			val[2] -= s;
			val[3] -= s;
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

		mat4_type<T>& operator*=(T s)
		{
			val[0] *= s;
			val[1] *= s;
			val[2] *= s;
			val[3] *= s;
			return *this;
		}

		mat4_type<T>& operator*=(const mat4_type<T>& m) { return (*this = *this * m); }
		mat4_type<T>& operator/=(const mat4_type<T>& m) { return (*this = *this * inverse(m)); }
		mat4_type<T>& operator/=(T s)
		{
			val[0] /= s;
			val[1] /= s;
			val[2] /= s;
			val[3] /= s;
			return *this;
		}

		friend vec4_type<T> operator*(const mat4_type<T>& m, const vec4_type<T>& v)
		{
			const vec4_type<T> Mov0(v[0]);
			const vec4_type<T> Mov1(v[1]);
			const vec4_type<T> Mul0 = m[0] * Mov0;
			const vec4_type<T> Mul1 = m[1] * Mov1;
			const vec4_type<T> Add0 = Mul0 + Mul1;
			const vec4_type<T> Mov2(v[2]);
			const vec4_type<T> Mov3(v[3]);
			const vec4_type<T> Mul2 = m[2] * Mov2;
			const vec4_type<T> Mul3 = m[3] * Mov3;
			const vec4_type<T> Add1 = Mul2 + Mul3;
			const vec4_type<T> Add2 = Add0 + Add1;
			return Add2;
		}

		friend mat4_type<T> operator+(const mat4_type<T>& m, T s) { return mat4_type<T>(m[0] + s, m[1] + s, m[2] + s, m[3] + s); }
		friend mat4_type<T> operator+(T s, const mat4_type<T>& m) { return mat4_type<T>(m[0] + s, m[1] + s, m[2] + s, m[3] + s); }
		friend mat4_type<T> operator+(const mat4_type<T>& m1, const mat4_type<T>& m2) { return mat4_type<T>(m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3]); }
		friend mat4_type<T> operator-(const mat4_type<T>& m, T s) { return mat4_type<T>(m[0] - s, m[1] - s, m[2] - s, m[3] - s); }
		friend mat4_type<T> operator-(T s, const mat4_type<T>& m) { return mat4_type<T>(s - m[0], s - m[1], s - m[2], s - m[3]); }
		friend mat4_type<T> operator-(const mat4_type<T>& m1, const mat4_type<T>& m2) { return mat4_type<T>(m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3]); }
		friend mat4_type<T> operator*(const mat4_type<T>& m, T s) { return mat4_type<T>(m[0] * s, m[1] * s, m[2] * s, m[3] * s); }
		friend mat4_type<T> operator*(T s, const mat4_type<T>& m) { return mat4_type<T>(m[0] * s, m[1] * s, m[2] * s, m[3] * s); }
		friend mat4_type<T> operator*(const mat4_type<T>& m1, const mat4_type<T>& m2)
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
		friend mat4_type<T> operator/(const mat4_type<T>& m, T s) { return mat4_type<T>(m[0] / s, m[1] / s, m[2] / s, m[3] / s); }
		friend mat4_type<T> operator/(T s, const mat4_type<T>& m) { return mat4_type<T>(s / m[0], s / m[1], s / m[2], s / m[3]); }
		friend mat4_type<T> operator/(const mat4_type<T>& m1, const mat4_type<T>& m2) { auto temp(m1); return temp /= m2; }

		static mat4_type<T> inverse(const mat4_type<T>& m)
		{
			T c00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
			T c02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
			T c03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

			T c04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
			T c06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
			T c07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

			T c08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
			T c10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
			T c11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

			T c12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
			T c14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
			T c15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

			T c16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
			T c18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
			T c19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

			T c20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
			T c22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
			T c23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

			vec4_type<T> f0(c00, c00, c02, c03);
			vec4_type<T> f1(c04, c04, c06, c07);
			vec4_type<T> f2(c08, c08, c10, c11);
			vec4_type<T> f3(c12, c12, c14, c15);
			vec4_type<T> f4(c16, c16, c18, c19);
			vec4_type<T> f5(c20, c20, c22, c23);

			vec4_type<T> v0(m[1][0], m[0][0], m[0][0], m[0][0]);
			vec4_type<T> v1(m[1][1], m[0][1], m[0][1], m[0][1]);
			vec4_type<T> v2(m[1][2], m[0][2], m[0][2], m[0][2]);
			vec4_type<T> v3(m[1][3], m[0][3], m[0][3], m[0][3]);

			vec4_type<T> inv0(v1 * f0 - v2 * f1 + v3 * f2);
			vec4_type<T> inv1(v0 * f0 - v2 * f3 + v3 * f4);
			vec4_type<T> inv2(v0 * f1 - v1 * f3 + v3 * f5);
			vec4_type<T> inv3(v0 * f2 - v1 * f4 + v2 * f5);

			vec4_type<T> signA(+1, -1, +1, -1);
			vec4_type<T> signB(-1, +1, -1, +1);
			mat4_type<T> inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

			vec4_type<T> row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

			vec4_type<T> dot0(m[0] * row0);
			T dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

			T oneOverDeterminant = static_cast<T>(1) / dot1;

			return inverse * oneOverDeterminant;
		}

		static mat4_type<T> translate(const mat4_type<T>& m, const vec3_type<T>& v)
		{
			mat4_type<T> res = m;
			res[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
			return res;
		}

		static mat4_type<T> rotate(const mat4_type<T>& m, T angle, const vec3_type<T>& v)
		{
			const T a = angle;
			const T c = std::cos(a);
			const T s = std::sin(a);

			auto axis(normalized(v));
			auto temp((T(1) - c) * axis);

			mat4_type<T> rot;
			rot[0][0] = c + temp[0] * axis[0];
			rot[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
			rot[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

			rot[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
			rot[1][1] = c + temp[1] * axis[1];
			rot[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

			rot[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
			rot[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
			rot[2][2] = c + temp[2] * axis[2];

			mat4_type<T> res;
			res[0] = m[0] * rot[0][0] + m[1] * rot[0][1] + m[2] * rot[0][2];
			res[1] = m[0] * rot[1][0] + m[1] * rot[1][1] + m[2] * rot[1][2];
			res[2] = m[0] * rot[2][0] + m[1] * rot[2][1] + m[2] * rot[2][2];
			res[3] = m[3];
			return res;
		}

		static mat4_type<T> scale(const mat4_type<T>& m, const vec3_type<T>& v)
		{
			mat4_type<T> res;
			res[0] = m[0] * v[0];
			res[1] = m[1] * v[1];
			res[2] = m[2] * v[2];
			res[3] = m[3];
			return res;
		}

		static mat4_type<T> perspective(T fov, T aspect, T near, T far)
		{
			const T tanHalfFov = std::tan(fov / static_cast<T>(2));
			mat4_type<T> res(static_cast<T>(0));
			res[0][0] = static_cast<T>(1) / (aspect * tanHalfFov);
			res[1][1] = static_cast<T>(1) / (tanHalfFov);
			res[2][2] = -(far + near) / (far - near);
			res[2][3] = -static_cast<T>(1);
			res[3][2] = -(static_cast<T>(2) * far * near) / (far - near);
			return res;
		}
	};

	using mat4 = mat4_type<GLfloat>;
}
