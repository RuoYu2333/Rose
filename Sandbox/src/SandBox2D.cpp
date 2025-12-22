#include "SandBox2D.h"
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SandBox2D::SandBox2D()
	:Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void SandBox2D::OnAttach()
{
	//m_SquareVertexArray = Rose::VertexArray::Create();
	m_BackGroundTexture = Rose::Texture2D::Create("assets/texture/Checkerboard.png");
	/*float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,0.0f,0.0f,
		 0.5f, -0.5f, 0.0f,1.0f,0.0f,
		 0.5f,  0.5f, 0.0f,1.0f,1.0f,
		-0.5f,  0.5f, 0.0f,0.0f,1.0f
	};

	Rose::Ref<Rose::VertexBuffer> squareVB;
	squareVB.reset(Rose::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ Rose::ShaderDataType::Float3, "a_Position" },
		{ Rose::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVertexArray->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Rose::Ref<Rose::IndexBuffer> squareIB;
	squareIB.reset(Rose::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVertexArray->SetIndexBuffer(squareIB);

	m_FlatColorShader = Rose::Shader::Create("assets/shaders/FlatColor.glsl");*/
}

void SandBox2D::OnDetach()
{

}

void SandBox2D::OnUpdate(Rose::TimeStep timestep)
{
	m_CameraController.OnUpdate(timestep);
	Rose::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Rose::RenderCommand::Clear();
	Rose::Renderer2D::BeginScene(m_CameraController.GetCamera());
	/*std::dynamic_pointer_cast<Rose::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Rose::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
	for (int j = 0; j < 5; ++j) {
		for (int i = 0; i < 5; ++i) {
			glm::vec3 pos(i * 0.25f, j * 0.25f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Rose::Renderer::Submit(m_SquareVertexArray, m_FlatColorShader, transform);
		}
	}*/
	Rose::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 0.8f,0.8f }, { 0.8f,0.2f,0.3f,1.0f });
	Rose::Renderer2D::DrawQuad({ 1.0f,0.0f }, { 1.5f,1.2f }, { 0.2f,0.8f,0.7f,1.0f });
<<<<<<< HEAD
=======
	Rose::Renderer2D::DrawQuad({ 0.0f,0.0f,-0.1f }, { 5.0f,5.0f }, m_BackGroundTexture);
>>>>>>> 2bd6f8eca5e005fa2018892ff22c4880e641969c
	Rose::Renderer2D::EndScene();

}

void SandBox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void SandBox2D::OnEvent(Rose::Event& event)
{
	m_CameraController.OnEvent(event);
}
