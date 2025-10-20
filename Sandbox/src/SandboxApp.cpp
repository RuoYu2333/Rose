#include <Rose.h>

#include "imgui/imgui.h"

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

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Rose::Event& event) override
	{
		if (event.GetEventType() == Rose::EventType::KeyPressed)
		{
			Rose::KeyPressedEvent& e = (Rose::KeyPressedEvent&)event;
			if (e.GetKeyCode() == RS_KEY_TAB)
				RS_TRACE("Tab key is pressed (event)!");
			RS_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

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