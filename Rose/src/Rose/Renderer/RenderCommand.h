#pragma once
#include <glm/glm.hpp>
#include "Rose/Renderer/VertexArray.h"
#include "RendererAPI.h"
namespace Rose
{
	class RenderCommand {
	public:
		inline static void Init() 
		{
			s_RendererAPI->Init();
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void DrawIndexed(const Rose::Ref<VertexArray>& vertexArray, uint32_t count = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray,count);
		}
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x,y,width, height);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}