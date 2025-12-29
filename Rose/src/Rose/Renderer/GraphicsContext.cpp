#include "rspch.h"
#include "Rose/Renderer/GraphicsContext.h"

#include "Rose/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Rose {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    RS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		RS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}