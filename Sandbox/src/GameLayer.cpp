#include "GameLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Random.h"

using namespace Rose;

GameLayer::GameLayer()
	: Layer("GameLayer"), m_State(GameState::MainMenu)
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Random::Init();
}

void GameLayer::OnAttach()
{
	m_Level.Init();

	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/fonts/OpenSans-Regular.ttf", 120.0f);
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(Rose::TimeStep ts)
{
	m_Time += ts;
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;

	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });

	switch (m_State)
	{
	case GameState::Play:
	{
		m_Level.OnUpdate(ts);
		break;
	}
	}

	// Render
	Rose::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	Rose::RenderCommand::Clear();

	Rose::Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	Rose::Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
	//ImGui::Begin("Settings");
	//m_Level.OnImGuiRender();
	//ImGui::End();

	// UI?

	switch (m_State)
	{
	case GameState::Play:
	{
		uint32_t playerScore = m_Level.GetPlayer().GetTotalScore();

		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		
		ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
		std::string healthStr = std::string("Health: ") + std::to_string((int)m_Level.GetPlayer().GetHealth());
		ImVec2 healthPos = ImGui::GetWindowPos();
		healthPos.y += 60.0f;  // 向下偏移60像素
		ImGui::GetForegroundDrawList()->AddText(m_Font, 36.0f, healthPos, 0xffff00ff, healthStr.c_str());
		break;
	}
	case GameState::MainMenu:
	{
		auto pos = ImGui::GetWindowPos();
		auto width = Application::Get().GetWindow().GetWidth();
		auto height = Application::Get().GetWindow().GetHeight();
		pos.x += width * 0.5f - 300.0f;
		pos.y += 50.0f;
		if (m_Blink)
			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
		break;
	}
	case GameState::GameOver:
	{
		auto pos = ImGui::GetWindowPos();
		auto width = Application::Get().GetWindow().GetWidth();
		auto height = Application::Get().GetWindow().GetHeight();
		pos.x += width * 0.5f - 300.0f;
		pos.y += 50.0f;
		if (m_Blink)
			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");

		pos.x += 200.0f;
		pos.y += 150.0f;

		// 显示最终分数
		uint32_t playerScore = m_Level.GetPlayer().GetTotalScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());

		// 更新高分
		if (playerScore > m_HighScore) {
			m_HighScore = playerScore;
			pos.y += 100.0f;
			std::string highScoreStr = std::string("New High Score!");
			ImGui::GetForegroundDrawList()->AddText(m_Font, 36.0f, pos, 0xFFFFFF00, highScoreStr.c_str());
		}
		break;
	}
	}
}

void GameLayer::OnEvent(Rose::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(RS_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(RS_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnMouseButtonPressed(Rose::MouseButtonPressedEvent& e)
{
	switch (m_State)
	{
	case GameState::MainMenu:
		// 主菜单点击开始游戏，重置分数
		m_State = GameState::Play;
		m_Level.Reset(false); // 不保留分数
		RS_INFO("Starting new game. Score reset.");
		break;

	case GameState::GameOver:
		// 游戏结束点击重新开始，保留分数
		m_State = GameState::Play;
		m_Level.Reset(false); // 保留分数
		RS_INFO("Restarting game. Score retained.");
		break;

	case GameState::Play:
		// 游戏进行中点击，不改变状态
		break;
	}

	return false;
}
bool GameLayer::OnWindowResize(Rose::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = CreateScope<Camera>(left, right, bottom, top);
}