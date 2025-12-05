#include "rspch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Rose {
    Ref<VertexArray> Rose::VertexArray::Create()
    {
		switch (Renderer::GetAPI())
		{
		default:
			break;
		case RendererAPI::API::None:
			RS_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}
		RS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}
