#pragma once
#include "Rose/Renderer/RendererAPI.h"
namespace Rose
{
	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void Init() override;
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void DrawIndexed(const Rose::Ref<VertexArray>& vertexArray) override;

	};
}