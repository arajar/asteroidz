#include "shader.h"

namespace gfx
{
	shader::~shader()
	{
		for (auto& stage : m_stages)
		{
			glDetachShader(m_object, stage);
			glDeleteShader(stage);
		}

		glDeleteProgram(m_object);
	}

	shader& shader::vertex(const std::string& source)
	{
		return add(ShaderType::Vertex, source);
	}

	shader& shader::pixel(const std::string& source)
	{
		return add(ShaderType::Pixel, source);
	}

	bool shader::link()
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
				//int a = 42343;
			}
		}
		return linked == GL_TRUE;
	}

	void shader::begin()
	{
		glUseProgram(m_object);
	}

	void shader::end()
	{
		glUseProgram(0);
	}

	unsigned int shader::attribute(const char* name) const
	{
		return glGetAttribLocation(m_object, name);
	}

	unsigned int shader::uniform(const char* name) const
	{
		return glGetUniformLocation(m_object, name);
	}

	void shader::uniform(const char* name, int v) const
	{
		glUniform1i(uniform(name), v);
	}

	void shader::uniform(const char* name, float v) const
	{
		glUniform1f(uniform(name), v);
	}

	void shader::uniform(const char* name, const m::vec2& v) const
	{
		glUniform2fv(uniform(name), 1, v.xy);
	}

	void shader::uniform(const char* name, const m::vec3& v) const
	{
		glUniform3fv(uniform(name), 1, &(v.x));
	}

	void shader::uniform(const char* name, const m::vec4& v) const
	{
		glUniform4fv(uniform(name), 1, &(v.x));
	}

	void shader::uniform(const char* name, const m::mat4& m, bool transpose) const
	{
		glUniformMatrix4fv(uniform(name), 1, transpose, &(m[0].x));
	}

	shader& shader::add(ShaderType type, const std::string& source)
	{
		std::string data = "#version 100\n";
		if (type == ShaderType::Pixel)
		{
			data += "#ifdef GL_FRAGMENT_PRECISION_HIGH\n";
			data += "precision highp float;\n";
			data += "#else\n";
			data += "precision mediump float;\n";
			data += "#endif\n";
		}

		// check if the source is the name of a file or shader code
		FILE* fp = util::android_fopen(source.c_str(), "r");
		if (fp)
		{
			char line[1024];
			while (fgets(line, 1024, fp) != nullptr)
			{
				data += line;
			}

			fclose(fp);
			fp = nullptr;
		}
		else
		{
			data += source;
		}

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
				//int a = 5433;
			}
		}

		// HANDLE ERROR OR SOMETHING
		return *this;
	}
}