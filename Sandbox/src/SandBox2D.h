#pragma once

#include "Rose.h"

class SandBox2D : public Rose::Layer
{
	public:
	 SandBox2D();
	 virtual ~SandBox2D() = default;
	 virtual void OnAttach() override;
	 virtual void OnDetach() override;
	 virtual void OnUpdate(Rose::TimeStep timestep) override;
	 virtual void OnImGuiRender() override;
	 void OnEvent(Rose::Event& event) override;
private:
	 Rose::ShaderLab m_ShaderLab;
	 Rose::Ref<Rose::VertexArray> m_VertexArray;
	 Rose::Ref<Rose::VertexArray> m_SquareVertexArray;
	 Rose::Ref<Rose::Shader> m_FlatColorShader;
	 Rose::Ref<Rose::Texture2D> m_Texture;
	 Rose::Ref<Rose::Texture2D> m_BackGroundTexture;
	 Rose::CameraController m_CameraController;
	 glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f ,1.0f};

};