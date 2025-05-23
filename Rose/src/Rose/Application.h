#pragma once
#include "Core.h"
namespace Rose {

	class ROSE_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

	};
	// To be defined in CLIENT
	Application* CreateApplication();
}