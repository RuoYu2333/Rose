#include <Rose.h>

class ExampleLayer : public Rose::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//RS_INFO("ExampleLayer::Update");

		if (Rose::Input::IsKeyPressed(RS_KEY_TAB)) {
			RS_INFO("TAB PRESSED");
		}
	}

	void OnEvent(Rose::Event& event) override
	{
		//RS_TRACE("{0}", event);
		if(event.GetEventType()== Rose::EventType::MouseMoved)
		{
			Rose::MouseMovedEvent& e = (Rose::MouseMovedEvent&)event;
			RS_INFO("MouseMovedEvent: {0}, {1}", e.GetX(), e.GetY());
		}
		else if (event.GetEventType() == Rose::EventType::MouseScrolled)
		{
			Rose::MouseScrolledEvent& e = (Rose::MouseScrolledEvent&)event;
			RS_INFO("MouseScrolledEvent: {0}, {1}", e.GetXOffset(),e.GetYOffset());
		}
		else if (event.GetEventType() == Rose::EventType::KeyPressed)
		{
			Rose::KeyPressedEvent& e = (Rose::KeyPressedEvent&)event;
			RS_INFO("KeyPressedEvent: {0} ({1} repeats)", char(e.GetKeyCode()), char(e.GetRepeatCount()));
		}
		else if (event.GetEventType() == Rose::EventType::KeyReleased)
		{
			Rose::KeyReleasedEvent& e = (Rose::KeyReleasedEvent&)event;
			RS_INFO("KeyReleasedEvent: {0}", char(e.GetKeyCode()));
		}
		else if (event.GetEventType() == Rose::EventType::WindowResize)
		{
			Rose::WindowResizeEvent& e = (Rose::WindowResizeEvent&)event;
			RS_INFO("WindowResizeEvent: {0}, {1}", e.GetWidth(), e.GetHeight());
		}
	}

};

class Sandbox : public Rose::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Rose::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

Rose::Application* Rose::CreateApplication()
{
	return new Sandbox();
}