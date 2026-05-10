#pragma once

#include "Rose/Core.h"
#include "Window.h"
#include "Rose/Events/Event.h"
#include "Rose/Events/ApplicationEvent.h"
#include "Rose/Core/LayerStack.h"
#include "Rose/ImGui/ImGuiLayer.h"
#include "Rose/Renderer/Shader.h"
#include "Rose/Renderer/Buffer.h"
#include "Rose/Renderer/VertexArray.h"
#include "Rose/Camera/Camera.h"
#include "Rose/Core/TimeStep.h"
namespace Rose {

	class ROSE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		void Close();
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Rose::Scope<Window> m_Window;
		ImGuiLayer *m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		Rose::Ref<Shader> m_Shader;
		Rose::Ref<VertexArray> m_VertexArray;

		Rose::Ref<VertexArray> m_SquareVertexArray;
		Rose::Ref<Shader> m_BlueShader;

		Rose::Ref<Camera> m_Camera;

		TimeStep m_TimeStep;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}