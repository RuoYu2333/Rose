#pragma once
#include <glm/glm.hpp>
#include "Rose/Renderer/VertexArray.h"
#include "RendererAPI.h"
namespace Rose
{
	class RenderCommand {
	public:
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}