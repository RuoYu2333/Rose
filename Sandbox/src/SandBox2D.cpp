#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	RS_PROFILE_FUNCTION();

	m_CheckerboardTexture = Rose::Texture2D::Create("assets/texture/Checkerboard.png");
	m_LogoTexture = Rose::Texture2D::Create("assets/texture/Asuka.jpg");
}

void Sandbox2D::OnDetach()
{
	RS_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Rose::TimeStep ts)
{
	RS_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		Rose::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Rose::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 20.0f;
		Rose::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Rose::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Rose::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Rose::Renderer2D::DrawQuad({ 0.0f, 0.0f ,-0.1f }, { 10.0f, 10.0f }, m_LogoTexture, 10.0f);
		Rose::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f ,0.0f }, { 1.0f, 1.0f },rotation, { 0.8f, 0.2f, 0.3f, 1.0f });
		Rose::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f ,0.0f}, { 2.0f, 2.0f }, rotation, m_LogoTexture, 1.0f, glm::vec4(1.0f));
		Rose::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	RS_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Rose::Event& e)
{
	m_CameraController.OnEvent(e);
}