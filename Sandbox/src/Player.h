#pragma once

#include <Rose.h>

#include "Color.h"
#include "Random.h"

#include "ParticleSystem.h"

class Player
{
public:
	Player();

	void LoadAssets();

	void OnUpdate(Rose::TimeStep ts);
	void OnRender();

	void OnImGuiRender();

	uint32_t GetTotalScore() const {
		// 返回基础分数 + 位置奖励
		return m_BaseScore + (uint32_t)(m_Position.x + 10.0f) / 10.0f;
	}
	void SetBaseScore(uint32_t score) { m_BaseScore = score; }
	uint32_t GetBaseScore() const { return m_BaseScore; }

	void SaveCurrentScore() {
		// 将当前总分保存为基础分数
		m_BaseScore = GetTotalScore();
	}

	void ResetPositionOnly() {
		// 只重置位置，用于碰撞后
		m_Position = { -10.0f, 0.0f };
		m_Velocity = { 5.0f, 0.0f };
	}

	void ResetCompletely() {
		// 完全重置
		m_Position = { -10.0f, 0.0f };
		m_Velocity = { 5.0f, 0.0f };
		m_Health = m_MaxHealth;
		m_Alive = true;
		m_BaseScore = 0;
	}

	void ResetForRetry() {
		// 用于重新尝试
		m_Position = { -10.0f, 0.0f };
		m_Velocity = { 5.0f, 0.0f };
		m_Health = m_MaxHealth;
		m_Alive = true;
		// 不重置基础分数
	}

	float GetRotation() { return m_Velocity.y * 4.0f - 90.0f; }
	const glm::vec2& GetPosition() const { return m_Position; }
	void ReduceHealth(float amount) {
		m_Health -= amount;
		if (m_Health <= 0.0f) {
			m_Health = 0.0f;
			m_Alive = false;
		}
	}
	bool IsAlive() const { return m_Alive; }

	float GetHealth() const { return m_Health; }
	float GetMaxHealth() const { return m_MaxHealth; }

	void AddScore(uint32_t score) {
		m_BaseScore += score;
	}

private:
	glm::vec2 m_Position = { -10.0f, 0.0f };
	glm::vec2 m_Velocity = { 5.0f, 0.0f };

	float m_EnginePower = 0.5f;
	float m_Gravity = 0.4f;
	float m_Health = 100.0f;
	float m_MaxHealth = 100.0f;
	bool m_Alive = true;
	uint32_t m_BaseScore = 0;  // 基础分数

	float m_Time = 0.0f;
	float m_SmokeEmitInterval = 0.4f;
	float m_SmokeNextEmitTime = m_SmokeEmitInterval;

	ParticleProps m_SmokeParticle, m_EngineParticle;
	ParticleSystem m_ParticleSystem;

	Rose::Ref<Rose::Texture2D> m_ShipTexture;
};