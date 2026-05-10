#pragma once
#include <Rose.h>

struct ParticleProps
{
    glm::vec2 Position = glm::vec2(0.0f);
    glm::vec2 Velocity = glm::vec2(1.0f), VelocityVariation = glm::vec2(0.5f);
    glm::vec4 ColorBegin = glm::vec4(1.0f), ColorEnd = glm::vec4(0.0f);
    float SizeBegin = 3.0f, SizeEnd = 0.0f, SizeVariation =0.3f;
    float LifeTime = 1.0f;
};
// ParticleSystem.h
class ParticleSystem
{
public:
    ParticleSystem(uint32_t MaxParticles = 100000);
    void OnUpdate(Rose::TimeStep ts);
    void OnRender(Rose::Camera& Camera);
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
    uint32_t m_PoolIndex;
};
