#pragma once

//////////////////////////////////////////////////////////////////////////

#define ToRad(x) ((x) * M_PI / 180.0f)
#define ToDeg(x) ((x) * 180.0f / M_PI)

//////////////////////////////////////////////////////////////////////////

namespace math
{
	template<typename T>
	struct mat4
	{
		vec4<T> m[4];

		mat4()
		{
			identity();
		}

		void identity()
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					m[i][j] = i == j ? 1.f : 0.f;
				}
			}
		}

		inline void operator+(const mat4<T>& other)
		{
			for (int i = 0; i < 4; ++i)
			{
				m[i] += other[i];
			}
		}

		inline mat4<T>& operator+=(const mat4<T>& other)
		{
			for (int i = 0; i < 4; ++i)
			{
				m[i] += other[i];
			}

			return *this;
		}

		inline void operator-(const mat4<T>& other)
		{
			for (int i = 0; i < 4; ++i)
			{
				m[i] -= other[i];
			}
		}

		inline mat4<T>& operator-=(const mat4<T>& other)
		{
			for (int i = 0; i < 4; ++i)
			{
				m[i] -= other[i];
			}

			return *this;
		}

		inline void operator*(const mat4<T>& other)
		{
			int k, r, c;
			for (c = 0; c < 4; ++c)
			{
				for (r = 0; r < 4; ++r)
				{
					m[c][r] = 0.f;
					for (k = 0; k < 4; ++k)
					{
						m[c][r] += m[k][r] * other[c][k];
					}
				}
			}
		}

		inline mat4<T>& operator*=(const mat4<T>& other)
		{
			int k, r, c;
			for (c = 0; c < 4; ++c)
			{
				for (r = 0; r < 4; ++r)
				{
					m[c][r] = 0.f;
					for (k = 0; k < 4; ++k)
					{
						m[c][r] += m[k][r] * other[c][k];
					}
				}
			}

			return *this;
		}

		inline vec4<T> operator*=(const vec4<T>& other)
		{
			vec4<T> res;

			for (int j = 0; j < 4; ++j)
			{
				res[j] = 0.f;
				for (int i = 0; i < 4; ++i)
				{
					res[j] += m[i][j] * other[i];
				}
			}

			return res;
		}

		inline void scale(float k)
		{
			for (int i = 0; i < 4; ++i)
			{
				m[i] *= k;
			}
		}

		inline void scale(const vec3<T>& other)
		{
			m[0] *= other.x;
			m[1] *= other.y;
			m[2] *= other.z;
		}

		inline void translate(const vec3<T>& pos)
		{
			identity();

			m[3][0] = pos.x;
			m[3][1] = pos.y;
			m[3][2] = pos.z;
		}

		inline void rotate(const vec3<T>& rot)
		{
			mat4<T> rx, ry, rz;

			const float x = ToRad(rot.x);
			const float y = ToRad(rot.y);
			const float z = ToRad(rot.z);

			rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f; rx.m[0][2] = 0.0f; rx.m[0][3] = 0.0f;
			rx.m[1][0] = 0.0f; rx.m[1][1] = std::cos(x); rx.m[1][2] = -std::sin(x); rx.m[1][3] = 0.0f;
			rx.m[2][0] = 0.0f; rx.m[2][1] = std::sin(x); rx.m[2][2] = std::cos(x); rx.m[2][3] = 0.0f;
			rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f; rx.m[3][2] = 0.0f; rx.m[3][3] = 1.0f;

			ry.m[0][0] = std::cos(y); ry.m[0][1] = 0.0f; ry.m[0][2] = -std::sin(y); ry.m[0][3] = 0.0f;
			ry.m[1][0] = 0.0f; ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f; ry.m[1][3] = 0.0f;
			ry.m[2][0] = std::sin(y); ry.m[2][1] = 0.0f; ry.m[2][2] = std::cos(y); ry.m[2][3] = 0.0f;
			ry.m[3][0] = 0.0f; ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f; ry.m[3][3] = 1.0f;

			rz.m[0][0] = std::cos(z); rz.m[0][1] = -std::sin(z); rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
			rz.m[1][0] = std::sin(z); rz.m[1][1] = std::cos(z); rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
			rz.m[2][0] = 0.0f; rz.m[2][1] = 0.0f; rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
			rz.m[3][0] = 0.0f; rz.m[3][1] = 0.0f; rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

			*this = rz * ry * rx;
		}
	};
}