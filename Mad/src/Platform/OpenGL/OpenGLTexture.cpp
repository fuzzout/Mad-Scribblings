#include "madpch.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include "stb_image.h"

namespace Mad {



	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) 
		: m_Path(path)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		MAD_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;
		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		MAD_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, 0);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		if (stbi_failure_reason()) {
			std::string poo = stbi_failure_reason();
			if (poo == "can't fopen")
				MAD_CORE_FATAL("OpenGLTexture Failure: File Not Found/Incorrect path.");
			else if (poo == "outofmem")
				MAD_CORE_FATAL("OpenGLTexture Failure: Out of Memory.");
			else if (poo == "unsupported")
				MAD_CORE_FATAL("OpenGLTexture Failure: Unsupported format conversion.");
			else if (poo == "bad bits_per_channel")
				MAD_CORE_FATAL("OpenGLTexture Failure: PNG - Unsupported color depth.");
			else
				MAD_CORE_FATAL(poo);
				
		}
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}


}