#pragma once

#include "Player.h"

struct Pillar
{
	glm::vec3 TopPosition = { 0.0f, 10.0f, 0.0f };
	glm::vec2 TopScale = { 15.0f, 20.0f };

	glm::vec3 BottomPosition = { 10.0f, 10.0f, 0.0f };
	glm::vec2 BottomScale = { 15.0f, 20.0f };
};

class Level
{
public:
	void Init();

	void OnUpdate(Rose::TimeStep ts);
	void OnRender();

	void OnImGuiRender();

	bool IsGameOver() const { return m_GameOver; }
	void Reset();
	void Reset(bool keepScore);

	Player& GetPlayer() { return m_Player; }
private:
	void CreatePillar(int index, float offset);
	bool CollisionTest();

	void GameOver();
private:
	Player m_Player;

	bool m_GameOver = false;
	float m_MinPillarHeight = 5.0f;   // 柱子最小高度
	float m_MaxPillarHeight = 30.0f;  // 柱子最大高度
	float m_MinGapSize = 2.0f;        // 最小间隙大小
	float m_MaxGapSize = 8.0f;        // 最大间隙大小
	bool m_ShowDebug = false;         // 是否显示调试信息
	float m_PillarTarget = 30.0f;
	int m_PillarIndex = 0;
	glm::vec3 m_PillarHSV = { 0.0f, 0.8f, 0.8f };

	std::vector<Pillar> m_Pillars;

	Rose::Ref<Rose::Texture2D> m_TriangleTexture;
};