#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
static const uint32_t s_MapWidth = 24;
static const char* s_MapTiles =
"WWWWWWWDWWWWWWWWDDWWWWWW"
"WWWWWWDWWWWWWWWWDDDWWWWW"
"WWWWDDDDWWWWWWWWDDDDWWWW"
"WWDDDWWWWWWWWWWWWWDDDWWW"	
"DDDWWWWWWWWWWWWWWWWWDDWW"	
"WDWWWWWWWWWWWWWWWWWWWDDW"	
"WWDWWWWWWWWWWWWWWWWWWDWW"	
"WWDWWWWWWWWWWWWWWWDDDDWW"	
"WDWWWWWWWWWWWWWWWWWDDWWW"	
"WWDDDWWWWWWWWWWWWWWDWWWW"	
"WWWDDWWWWWWWWWWWWWDWWWWW"	
"WWWWDDDDDDDDDDDDDDWWWWWW"	
;


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{	
}

void Sandbox2D::OnAttach()
{
	RS_PROFILE_FUNCTION();

	m_CheckerboardTexture = Rose::Texture2D::Create("assets/texture/Checkerboard.png");
	m_LogoTexture = Rose::Texture2D::Create("assets/texture/Asuka.jpg");
	m_SpriteShade = Rose::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");
	m_SubTextureGrass = Rose::SubTexture2D::CreateFromCoords(m_SpriteShade, { 0,1 }, { 128, 128 },{1,2});
	m_SubTextureWarter = Rose::SubTexture2D::CreateFromCoords(m_SpriteShade, { 11,11 }, { 128, 128 },{1,1});
	m_SubTextureDirt = Rose::SubTexture2D::CreateFromCoords(m_SpriteShade, { 6,11 }, { 128, 128 },{1,1});
	s_TextureMap['W'] = m_SubTextureWarter;
	s_TextureMap['D'] = m_SubTextureDirt;
	m_MapWidth = s_MapWidth;
	m_MapHeight = static_cast<uint32_t>(strlen(s_MapTiles)) / s_MapWidth;
	m_ParticleProps.ColorBegin = { 1.0f, 0.5f, 0.2f, 1.0f };
	m_ParticleProps.ColorEnd = { 0.2f, 0.3f, 1.0f, 1.0f };
	m_ParticleProps.SizeBegin = 0.01f;
	m_ParticleProps.SizeEnd = 0.0f;
	m_ParticleProps.SizeVariation = 0.003f;
	m_ParticleProps.LifeTime = 1.0f;
	m_ParticleProps.Velocity = { 0.3f, 0.4f };
	m_ParticleProps.VelocityVariation = { 3.0f, 1.0f };
	m_ParticleProps.Position = { 0.0f, 0.0f };
	m_CameraController.SetZoomLevel(2.0f);

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
	Rose::Renderer2D::ResetStats();
	// Render
	{
		Rose::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Rose::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 20.0f;
		Rose::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (uint32_t y = 0; y < m_MapHeight; y++) {
			for (uint32_t x = 0; x < m_MapWidth; x++) {
				char tiletype = s_MapTiles[x + y * m_MapWidth];
				Rose::Ref<Rose::SubTexture2D> texture;
				if (s_TextureMap.find(tiletype) != s_TextureMap.end()) {
					texture = s_TextureMap[tiletype];
				}
				else {
					texture = m_SubTextureGrass;
				}
				Rose::Renderer2D::DrawQuad({ (float)x-m_MapWidth, (float)y-m_MapHeight ,0.5f}, { 1.0f, 1.0f }, texture);
			}
		}
		Rose::Renderer2D::EndScene();
		if (Rose::Input::IsMouseButtonPressed(RS_MOUSE_BUTTON_LEFT)) {
			auto [x, y] = Rose::Input::GetMousePosition();
			auto width = Rose::Application::Get().GetWindow().GetWidth();
			auto height = Rose::Application::Get().GetWindow().GetHeight();
			auto bounds = m_CameraController.GetCameraBounds();
			auto pos = m_CameraController.GetCamera().GetPosition();
			x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
			y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
			m_ParticleProps.Position = { x + pos.x, y + pos.y };
			for (int i = 0; i < 50; i++)
				m_ParticleSystem.Emit(m_ParticleProps);
		}
			
		m_ParticleSystem.OnUpdate(ts);
		m_ParticleSystem.OnRender(m_CameraController.GetCamera());
	}
}

void Sandbox2D::OnImGuiRender()
{
	RS_PROFILE_FUNCTION();
	
	//static bool dockspaceOpen = true;
	//static bool opt_fullscreen = true;
	//static bool opt_padding = false;
	//static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	//// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	//// because it would be confusing to have two docking targets within each others.
	//ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	//if (opt_fullscreen)
	//{
	//	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	//	ImGui::SetNextWindowPos(viewport->WorkPos);
	//	ImGui::SetNextWindowSize(viewport->WorkSize);
	//	ImGui::SetNextWindowViewport(viewport->ID);
	//	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	//	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	//	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	//	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	//}
	//else
	//{
	//	dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	//}

	//// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	//// and handle the pass-thru hole, so we ask Begin() to not render a background.
	//if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
	//	window_flags |= ImGuiWindowFlags_NoBackground;

	//// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	//// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	//// all active windows docked into it will lose their parent and become undocked.
	//// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	//// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	//if (!opt_padding)
	//	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	//ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	//if (!opt_padding)
	//	ImGui::PopStyleVar();

	//if (opt_fullscreen)
	//	ImGui::PopStyleVar(2);

	//// Submit the DockSpace
	//ImGuiIO& io = ImGui::GetIO();
	//if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	//{
	//	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	//	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	//}

	//if (ImGui::BeginMenuBar())
	//{
	//	if (ImGui::BeginMenu("File"))
	//	{
	//		// Disabling fullscreen would allow the window to be moved to the front of other windows,
	//		// which we can't undo at the moment without finer window depth/z control.
	//		ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
	//		ImGui::MenuItem("Padding", NULL, &opt_padding);
	//		ImGui::Separator();

	//		if (ImGui::MenuItem("Exit"))
	//			Rose::Application::Get().Close();
	//		ImGui::EndMenu();
	//	}
	//	ImGui::EndMenuBar();
	//}
	//ImGui::Begin("Settings");

	//ImGui::Text("Renderer2D Stats:");
	//auto stats = Rose::Renderer2D::GetStats();
	//ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	//ImGui::Text("Quads: %d", stats.QuadCount);
	//ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	//ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	//ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	//uint32_t textureID = m_CheckerboardTexture->GetRendererID();
	//ImGui::Image((void*) textureID,ImVec2(64.0f,64.0f));
	//ImGui::End();
	//ImGui::End();
}

void Sandbox2D::OnEvent(Rose::Event& e)
{
	m_CameraController.OnEvent(e);
}