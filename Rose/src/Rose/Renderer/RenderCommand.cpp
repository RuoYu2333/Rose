#include "rspch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Rose {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}