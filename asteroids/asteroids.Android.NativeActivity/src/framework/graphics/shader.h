#pragma once
#include <string>
#include <vector>

namespace gfx
{
	enum class ShaderType : GLenum
	{
		Vertex = GL_VERTEX_SHADER,
		Pixel = GL_FRAGMENT_SHADER,
	};

	struct shader
	{
		~shader();

		shader& vertex(const std::string& source);
		shader& pixel(const std::string& source);

		bool link();

		void begin();
		void end();

		unsigned int attribute(const char* name) const;
		unsigned int uniform(const char* name) const;

		void uniform(const char* name, int v) const;
		void uniform(const char* name, float v) const;
		void uniform(const char* name, const math::vec2& v) const;
		void uniform(const char* name, const math::vec3& v) const;
		void uniform(const char* name, const math::vec4& v) const;
		void uniform(const char* name, const math::mat4& m, bool transpose = GL_FALSE) const;

	protected:
		shader& add(ShaderType type, const std::string& source);

	protected:
		unsigned int m_object = 0;
		std::vector<unsigned int> m_stages;
	};
}