#pragma once

namespace gfx
{
	struct texture
	{
		GLuint m_id = 0;

		~texture();

		bool load(const std::string& path);

		void begin();
		void end();

		void enableBlending();
		void disableBlending();
	};
}