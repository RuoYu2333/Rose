#include <Rose.h>

#include "imgui/imgui.h"
#include <Rose/Input.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Rose::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f/720.0f,true)
	{
		m_VertexArray.reset(Rose::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Rose::Ref<Rose::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Rose::VertexBuffer::Create(vertices, sizeof(vertices)));
		Rose::BufferLayout layout = {
			{ Rose::ShaderDataType::Float3, "a_Position" },
			{ Rose::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Rose::Ref<Rose::IndexBuffer> indexBuffer;
		indexBuffer.reset(Rose::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(Rose::VertexArray::Create());

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
		m_SquareVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Rose::Ref<Rose::IndexBuffer> squareIB;
		squareIB.reset(Rose::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Rose::Shader::Create("TriangleShader", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color,1.0);
			}
		)";

		m_FlatColorShader=Rose::Shader::Create("FlatColorShader", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLab.Load("assets/shaders/Texture.glsl");

		m_AsukaTexture = Rose::Texture2D::Create("assets/texture/Asuka.jpg");
		m_Texture = Rose::Texture2D::Create("assets/texture/Rose.png");
		
		std::dynamic_pointer_cast<Rose::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Rose::OpenGLShader>(textureShader)->UploadUniformInt("u_Color", 0);
	}

	void OnUpdate(Rose::TimeStep timeStep) override
	{
		m_CameraController.OnUpdate(timeStep);
		Rose::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Rose::RenderCommand::Clear();

		Rose::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		/*Rose::MaterialRef material = new Rose::Material(m_FlatColorShader);
		Rose::MaterialInstanceRef mi = new Rose::MaterialInstanceRef(material);
		 
		mi->SetFloat4("u_Color", redColor);
		squareMesh->SetMaterial(mi);*/
		std::dynamic_pointer_cast<Rose::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Rose::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int j = 0; j < 5; ++j) { 
			for (int i = 0; i < 5; ++i) {
				glm::vec3 pos(i * 0.25f, j*0.25f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Rose::Renderer::Submit(m_SquareVertexArray, m_FlatColorShader, transform);

			}
		}
		auto textureShader = m_ShaderLab.Get("Texture");

		m_Texture->Bind();
		Rose::Renderer::Submit(m_SquareVertexArray, textureShader,glm::scale(glm::mat4(1.0f),glm::vec3(1.5f)));

		m_AsukaTexture->Bind();
		Rose::Renderer::Submit(m_SquareVertexArray, textureShader, 
			glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

		Rose::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		
		ImGui::ColorEdit3("Square Color",glm::value_ptr(m_SquareColor));
		
		ImGui::End();
	}

	void OnEvent(Rose::Event& event) override
	{
		m_CameraController.OnEvent(event);
		Rose::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Rose::KeyPressedEvent>([this](Rose::KeyPressedEvent& e) {
			/*RS_INFO("KeyPressedEvent: {0}", e.GetKeyCode());
			if(e.GetKeyCode() == RS_KEY_LEFT)
			{
				m_CameraPosition.x -= m_CameraSpeed;
			}
			else if (e.GetKeyCode() == RS_KEY_RIGHT)
			{
				m_CameraPosition.x += m_CameraSpeed;
			}
			else if (e.GetKeyCode() == RS_KEY_UP)
			{
				m_CameraPosition.y += m_CameraSpeed;
			}
			else if (e.GetKeyCode() == RS_KEY_DOWN)
			{
				m_CameraPosition.y -= m_CameraSpeed;
			}
			else if(e.GetKeyCode()==RS_KEY_C)
			{
				m_CameraRotation += (45.0f*m_CameraRotateSpeed)/360.f;
			}
			m_Camera->SetPosition(m_CameraPosition);
			m_Camera->SetRotation(m_CameraRotation);*/
			return false;
			});
		
	}
private:
	Rose::ShaderLab m_ShaderLab;
	//Rose::Ref<Rose::Camera> m_Camera;
	Rose::Ref<Rose::Shader> m_Shader;
	Rose::Ref<Rose::Shader> m_FlatColorShader;
	Rose::Ref<Rose::VertexArray> m_VertexArray;
	Rose::Ref<Rose::VertexArray> m_SquareVertexArray;
	Rose::Ref<Rose::Texture2D> m_Texture,m_AsukaTexture;
	Rose::CameraController m_CameraController{ 16.0f / 9.0f };
	glm::vec3 m_CameraPosition{ 0.0f };
	glm::vec3 m_SquarePosition{ 0.0f };
	glm::mat4 m_Transform = glm::translate(glm::mat4(1.0f),m_SquarePosition);
	float m_CameraRotation = 0.0f;
	float m_CameraSpeed = 1.0f;
	float m_CameraRotateSpeed = 10.0f;
	float m_SquareSpeed = 1.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	Rose::Window* m_Window = &Rose::Application::Get().GetWindow();
};

class Sandbox : public Rose::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Rose::Application* Rose::CreateApplication()
{
	return new Sandbox();
}