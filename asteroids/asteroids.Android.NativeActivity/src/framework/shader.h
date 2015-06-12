#pragma once

#include <string>
#include <vector>
#include "vec2.h"

namespace gl
{
	enum class ShaderType : GLenum
	{
		Vertex = GL_VERTEX_SHADER,
		Pixel = GL_FRAGMENT_SHADER,
	};

	class Shader
	{
	public:
		Shader();
		~Shader();

	public:
		Shader& Vertex(const std::string& source);
		Shader& Pixel(const std::string& source);

		std::string Link();

	public:
		void Begin() const;
		void End() const;

	public:
		unsigned int Attribute(const char* name) const;
		unsigned int Uniform(const char* name) const;

		void Uniform(const char* name, int i) const;
		void Uniform(const char* name, float f) const;
		void Uniform(const char* name, const math::vec2f& v) const;

	protected:
		Shader& Add(ShaderType type, const std::string);

	protected:
		unsigned int m_object;
		std::vector<unsigned int> m_stages;
		std::string m_sources;
		std::string m_errors;
	};
}