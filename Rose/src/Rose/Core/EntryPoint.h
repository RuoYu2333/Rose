#pragma once
#include "Application.h"
#include "Log.h"

#ifdef RS_PLATFORM_WINDOWS

extern Rose::Application* Rose::CreateApplication();

int main(int argc,char** argv) {
	
	Rose::Log::Init();
	RS_CORE_ERROR("Initialized Log!");
	int a = 5;
	RS_INFO("Hello Log! Var={0}",a);
	std::cout << "Rose Engine INIT" << std::endl;
	auto app = Rose::CreateApplication();
	app->Run();
	delete app;

}




#endif // 
