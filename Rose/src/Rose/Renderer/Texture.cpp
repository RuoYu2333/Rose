#include "rspch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace Rose
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		default:
			break;
		case RendererAPI::API::None:
			RS_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(width, height);
		}
		RS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
		
	}
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		default:
			break;
		case RendererAPI::API::None:
			RS_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}
		RS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	
	}
}