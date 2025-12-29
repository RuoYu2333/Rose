#pragma once

#include "Rose.h"

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

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};