#include "rspch.h"

#include "Renderer2D.h"

#include "Rose/Renderer/RenderCommand.h"

#include "VertexArray.h"
#include "Rose/Renderer/Shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Rose {
	struct Renderer2DData
	{
		Ref<VertexArray> VertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> DefaultTexture;
	};
	static Renderer2DData* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DData();
		s_Data->VertexArray = Rose::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,0.0f,0.0f,
			 0.5f, -0.5f, 0.0f,1.0f,0.0f,
			 0.5f,  0.5f, 0.0f,1.0f,1.0f,
			-0.5f,  0.5f, 0.0f,0.0f,1.0f
		};

		Rose::Ref<Rose::VertexBuffer> squareVB;
		squareVB.reset(Rose::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Rose::ShaderDataType::Float3, "a_Position" },
			{ Rose::ShaderDataType::Float2, "a_TexCoord" }
			});
		s_Data->VertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Rose::Ref<Rose::IndexBuffer> squareIB;
		squareIB.reset(Rose::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_Data->VertexArray->SetIndexBuffer(squareIB);

		s_Data->DefaultTexture = Rose::Texture2D::Create(1,1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->DefaultTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		//s_Data->FlatColorShader = Rose::Shader::Create("assets/shaders/FlatColor.glsl");
		s_Data->TextureShader = Rose::Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}
	void Renderer2D::Shutdown()
	{
		RS_PROFILE_FUNCTION();
		delete s_Data;
	}
	void Renderer2D::BeginScene(const Camera& camera)
	{
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	
	}
	void Renderer2D::EndScene()
	{
		RS_PROFILE_FUNCTION();
		Flush();
	}
	void Renderer2D::Flush()
	{
		RS_PROFILE_FUNCTION();
		//m_Data->QuadIndexCount = 0;
	}

	void Rose::Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->DefaultTexture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)*
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->VertexArray);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);

	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture)
	{
		s_Data->TextureShader->SetFloat4("u_Color",glm::vec4(1.0f));
		texture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		s_Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->VertexArray);
		texture->Unbind();
	}
}
