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
		RS_INFO("ExampleLayer::Update");
	}

	void OnEvent(Rose::Event& event) override
	{
		RS_TRACE("{0}", event);
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