#pragma once

#include "Rose.h"

class ExampleLayer : public Rose::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Rose::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Rose::Event& e) override;
private:
	Rose::ShaderLab m_ShaderLibrary;
	Rose::Ref<Rose::Shader> m_Shader;
	Rose::Ref<Rose::VertexArray> m_VertexArray;

	Rose::Ref<Rose::Shader> m_FlatColorShader;
	Rose::Ref<Rose::VertexArray> m_SquareVA;

	Rose::Ref<Rose::Texture2D> m_Texture, m_ChernoLogoTexture;

	Rose::CameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
