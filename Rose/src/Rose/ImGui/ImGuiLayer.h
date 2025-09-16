#pragma once

#include "Rose/Layer.h"
#include "Rose/Events/KeyEvent.h"
#include "Rose/Events/MouseEvent.h"
#include "Rose/Events/ApplicationEvent.h"

namespace Rose {

	class ROSE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate();
		void OnEvent(Event& event);

		void OnAttach();
		void OnDetach();
	private:

		float m_Time = 0.0f;
		
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);



	};
}