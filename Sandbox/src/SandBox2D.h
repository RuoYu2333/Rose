#pragma once

#include "Rose.h"
#include "ParticleSystem.h"

class Sandbox2D : public Rose::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Rose::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Rose::Event& e) override;
private:
	Rose::CameraController m_CameraController;

	// Temp
	Rose::Ref<Rose::VertexArray> m_SquareVA;
	Rose::Ref<Rose::Shader> m_FlatColorShader;

	Rose::Ref<Rose::Texture2D> m_CheckerboardTexture;
	Rose::Ref<Rose::Texture2D> m_LogoTexture;
	Rose::Ref<Rose::Texture2D> m_SpriteShade;
	Rose::Ref<Rose::SubTexture2D> m_SubTextureGrass;
	Rose::Ref<Rose::SubTexture2D> m_SubTextureWarter;
	Rose::Ref<Rose::SubTexture2D> m_SubTextureDirt;
	ParticleSystem m_ParticleSystem;
	ParticleProps m_ParticleProps;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	uint32_t m_MapWidth = 24;
	uint32_t m_MapHeight = 12;
	std::unordered_map<char, Rose::Ref<Rose::SubTexture2D>> s_TextureMap;
};