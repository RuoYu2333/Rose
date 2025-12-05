#include "rspch.h"
#include <glad/glad.h>
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer2D.h"
namespace Rose
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::BeginScene(Camera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const Rose::Ref<VertexArray>& vertexArray, const Rose::Ref<Shader> shader,glm::mat4 trans)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader> (shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader> (shader)->UploadUniformMat4("u_Transform", trans);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
}