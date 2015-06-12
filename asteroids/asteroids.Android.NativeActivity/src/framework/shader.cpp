#include "shader.h"
#include <string>

#if defined(EXTRA_DEBUG_INFO)
#define CHECK_SHADER_ERROR GLint error; \
glGetProgramiv(m_object, GL_INFO_LOG_LENGTH, &error); \
if (error != GL_TRUE) \
{ \
int len; \
char buffer[256]; \
glGetProgramInfoLog(m_object, sizeof(buffer), &len, buffer); \
if (len) \
{ \
util::log.error("Error {0}", log); \
} \
}
#else
#define CHECK_SHADER_ERROR
#endif

namespace gl
{
	void foo()
	{

	}

	Shader::Shader()
		: m_object(0)
	{
	}

	Shader::~Shader()
	{
		for (auto& stage : m_stages)
		{
			glDetachShader(m_object, stage);
			glDeleteShader(stage);
		}

		glDeleteProgram(m_object);
	}

	Shader& Shader::Vertex(const std::string& source)
	{
		return Add(ShaderType::Vertex, source);
	}

	Shader& Shader::Pixel(const std::string& source)
	{
		return Add(ShaderType::Pixel, source);
	}

	static std::string Error(const char* type, const char* error, const char* source = nullptr)
	{
		//std::stringstream ss;
		//if (source)
		//{
		//	ss << "#Source:\n";
		//	unsigned line = 0;
		//	while (source && *source)
		//	{
		//		ss << std::setw(3) << std::setfill('0') << (++line) << ": ";
		//		while (source && *source && *source != '\n')
		//		{
		//			ss << *source++;
		//		}

		//		if (source && *source)
		//		{
		//			ss << *source++;
		//		}
		//	}
		//}

		//ss << "\n#" << type << "\n";
		//ss << error << "\n";
		//return ss.str();

		return "";
	}

	std::string Shader::Link()
	{
		if (!m_object)
		{
			m_object = glCreateProgram();
		}

		for (auto& stage : m_stages)
		{
			glAttachShader(m_object, stage);
		}

		glLinkProgram(m_object);

		GLint linked;
		glGetProgramiv(m_object, GL_LINK_STATUS, &linked);
		if (linked != GL_TRUE)
		{
			char buffer[512];
			int len;
			glGetProgramInfoLog(m_object, sizeof(buffer), &len, buffer);
			if (len)
			{
				//util::log.error(Error("Link error", buffer));
			}
		}

		return m_errors;
	}

	void Shader::Begin() const
	{
		glUseProgram(m_object);
		CHECK_SHADER_ERROR;
	}

	void Shader::End() const
	{
		glUseProgram(0);
		CHECK_SHADER_ERROR;
	}

	unsigned int Shader::Attribute(const char* name) const
	{
		return glGetAttribLocation(m_object, name);
	}

	unsigned int Shader::Uniform(const char* name) const
	{
		return glGetUniformLocation(m_object, name);
	}

	void Shader::Uniform(const char* name, int i) const
	{
		glUniform1i(Uniform(name), i);
		CHECK_SHADER_ERROR;
	}

	void Shader::Uniform(const char* name, float f) const
	{
		glUniform1f(Uniform(name), f);
		CHECK_SHADER_ERROR
	}

	void Shader::Uniform(const char* name, const math::vec2f& v) const
	{
		glUniform2fv(Uniform(name), 1, v.value_);
		CHECK_SHADER_ERROR
	}

	Shader& Shader::Add(ShaderType type, const std::string source)
	{
		std::string data;
		//std::ifstream ifs(source.c_str());
		//if (ifs.good())
		//{
		//	std::stringstream ss;
		//	ss << ifs.rdbuf();
		//	data = ss.str();
		//}
		//else
		{
			data = source;
		}

		if (data.empty())
		{
			//util::log.error("Could not load shader \"{0}\"", source);
		}

		m_sources += data;

		const char* src = data.c_str();

		unsigned int shader = glCreateShader(static_cast<GLenum>(type));
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);
		m_stages.push_back(shader);

		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (compiled != GL_TRUE)
		{
			char buffer[512];
			int len;
			glGetShaderInfoLog(shader, sizeof(buffer), &len, buffer);
			if (len)
			{
				auto err = Error("Compile error", buffer, src);
				//util::log.error("Error {0}", err);
			}
		}

		return *this;
	}
}