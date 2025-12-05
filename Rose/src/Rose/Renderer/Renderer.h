#pragma once
#include "RenderCommand.h"
#include "Rose/Camera/Camera.h"
#include "Shader.h"
namespace Rose {

	class Renderer
	{
	public:
		static void Init();
		static void BeginScene(Camera& camera);
		static void EndScene();
		static void Submit(const Rose::Ref<VertexArray>& vertexArray, const Rose::Ref<Shader> shader, glm::mat4 trans = glm::mat4{1.0f});
		static void OnWindowResize(uint32_t width, uint32_t height);
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};

}