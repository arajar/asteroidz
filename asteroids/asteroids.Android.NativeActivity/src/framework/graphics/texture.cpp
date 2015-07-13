#include "texture.h"

namespace gfx
{
	// helper class to load BMP files and create OpenGL textures
	texture::~texture()
	{
		if (m_id != 0)
		{
			glDeleteTextures(1, &m_id);
			m_id = 0;
		}
	}

	bool texture::load(const std::string& path)
	{
		// if we already have a valid id, return
		if (m_id != 0)
		{
			return true;
		}

		unsigned char header[54];
		unsigned int dataPos = 0;
		unsigned int imageSize = 0;
		unsigned char* data = nullptr;

		FILE* fp = util::android_fopen(path.c_str(), "rb");
		if (!fp)
		{
			LOGE("Can't open %s", path.c_str());
			return false;
		}

		// if less than 54 bytes are read, problem
		if (fread(header, 1, 54, fp) != 54)
		{
			LOGE("BMP header error");
			fclose(fp);
			return false;
		}

		// a BMP file always begins with "BM"
		if (header[0] != 'B' && header[1] != 'M')
		{
			LOGE("BMP header error");
			fclose(fp);
			return false;
		}

		// Make sure this is a 24bpp file
		if (*(int*)&(header[0x1E]) != 0)
		{
			LOGE("BMP header error");
			fclose(fp);
			return false;
		}

		if (*(int*)&(header[0x1C]) != 24)
		{
			LOGE("BMP header error");
			fclose(fp);
			return false;
		}

		// read the info
		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		m_size.x = *(int*)&(header[0x12]);
		m_size.y = *(int*)&(header[0x16]);

		if (!imageSize) { imageSize = m_size.x * m_size.y * 3; } // 3 for every component (RGB)
		if (!dataPos) { dataPos = 54; } // we know that

		data = new unsigned char[imageSize];
		fread(data, 1, imageSize, fp);
		fclose(fp);

		// create the opengl texture
		glGenTextures(1, &m_id);

		// convert from BGR to RGB
		unsigned char ubTemp;
		for (long x = 0; x < imageSize; x += 3)
		{

			ubTemp = data[x];
			data[x] = data[x + 2];
			data[x + 2] = ubTemp;
		}

		begin();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_size.x, m_size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		delete[] data;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		end();

		return true;
	}

	void texture::begin()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void texture::end()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void texture::enableBlending()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}

	void texture::disableBlending()
	{
		glDisable(GL_BLEND);
	}

	math::vec2 texture::getSize() const
	{
		return m_size;
	}
}
