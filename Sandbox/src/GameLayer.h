#pragma once

#include "Rose.h"

#include "Level.h"
#include <imgui/imgui.h>

class GameLayer : public Rose::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Rose::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Rose::Event& e) override;
	bool OnMouseButtonPressed(Rose::MouseButtonPressedEvent& e);
	bool OnWindowResize(Rose::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Rose::Scope<Rose::Camera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;
	uint32_t m_HighScore = 0;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};