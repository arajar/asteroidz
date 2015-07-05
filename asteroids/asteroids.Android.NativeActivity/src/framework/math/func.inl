
namespace m
{
	template<typename T>
	inline T pi()
	{
		return static_cast<T>(3.14159265358979323846264338327950288);
	}
	
	template<typename T>
	inline T toDeg(T angle)
	{
		return (angle * (static_cast<T>(180)) / pi<T>());
	}
	
	template<typename T>
	inline T toRad(T angle)
	{
		return angle * (pi<T>() / static_cast<T>(180));
	}

	template<typename T>
	mat4_type<T> perspective(T fov, T aspect, T near, T far)
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

	template<typename T>
	mat4_type<T> ortho(T left, T right, T bottom, T top)
	{
		mat4_type<T> res(static_cast<T>(1));
		res[0][0] = static_cast<T>(2) / (right - left);
		res[1][1] = static_cast<T>(2) / (top - bottom);
		res[2][2] = -static_cast<T>(1);
		res[3][0] = -(right + left) / (right - left);
		res[3][1] = -(top + bottom) / (top - bottom);
		return res;
	}

	template<typename T>
	mat4_type<T> lookAt(const m::vec3_type<T>& eye, const m::vec3_type<T>& center, const m::vec3_type<T>& up)
	{
		const m::vec3_type<T> f(normalized(center - eye));
		const m::vec3_type<T> s(normalized(m::vec3::cross(f, up)));
		const m::vec3_type<T> u(m::vec3::cross(s, f));

		mat4_type<T> res(static_cast<T>(1));
		res[0][0] = s.x;
		res[1][0] = s.y;
		res[2][0] = s.z;
		res[0][1] = u.x;
		res[1][1] = u.y;
		res[2][1] = u.z;
		res[0][2] = -f.x;
		res[1][2] = -f.y;
		res[2][2] = -f.z;
		res[3][0] = -dot(s, eye);
		res[3][1] = -dot(u, eye);
		res[3][2] = dot(f, eye);
		return res;
	}

}
