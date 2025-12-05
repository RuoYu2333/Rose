#include "rspch.h"
#include "OpenGLTexture.h"

#include <iostream>
#include <filesystem>
#include <stb_image.h>
#include "glad/glad.h"

namespace Rose {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		:m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		RS_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}
	Rose::OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* stu = stbi_load(path.c_str(), &width, &height, &channels, 0);
		//--------------------DEBUG INFO-----------------------------------
		/*std::cerr << "stbi_failure_reason: " << (stbi_failure_reason() ? stbi_failure_reason() : "none") << "\n";
		std::cerr << "cwd: " << std::filesystem::current_path().string() << "\n";
		std::cerr << "exists assets/texture/Checkerboard.png: "
			<< std::filesystem::exists("assets/texture/Checkerboard.png") << "\n";*/
			//---------------------------------------------------------------
		RS_CORE_ASSERT(stu, "Failed to load image!");
		m_Width = width;
		m_Height = height;
		
		GLenum internalFormat = channels == 4 ? GL_RGBA8 : GL_RGB8;
		GLenum dataFormat = channels == 4 ? GL_RGBA : GL_RGB;

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		RS_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, stu);
		stbi_image_free(stu);
	}

	Rose::OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Rose::OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void Rose::OpenGLTexture2D::Unbind(uint32_t slot) const
	{
		glBindTextureUnit(slot, 0);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp= (m_DataFormat == GL_RGBA ? 4 : 3);
		RS_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!"); 
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}


}