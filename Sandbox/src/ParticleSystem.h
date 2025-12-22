#pragma once
#include <Rose.h>

struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;
};
// ParticleSystem.h
class ParticleSystem
{
public:
    ParticleSystem();
    void OnUpdate(Rose::TimeStep ts);
    void OnRender();
    void Emit(const ParticleProps& particleProps);
    void Reset();  // 添加 Reset 函数

private:
    struct Particle
    {
        glm::vec2 Position;
        glm::vec2 Velocity;
        glm::vec4 ColorBegin, ColorEnd;
        float Rotation = 0.0f;
        float SizeBegin, SizeEnd;
        float LifeTime = 1.0f;
        float LifeRemaining = 0.0f;
        bool Active = false;
    };
    std::vector<Particle> m_ParticlePool;
    uint32_t m_PoolIndex = 999;
};

