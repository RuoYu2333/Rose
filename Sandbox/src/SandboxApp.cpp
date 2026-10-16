#include <Rose.h>
#include <Rose/Core/EntryPoint.h>

#include "GameLayer.h"

class Sandbox : public Rose::Application
{
public:
	Sandbox()
	{
		PushLayer(new GameLayer());
	}
};

Rose::Application* Rose::CreateApplication()
{
	return new Sandbox();
}
