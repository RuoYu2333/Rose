#pragma once

#ifdef RS_PLATFORM_WINDOWS

extern Rose::Application* Rose::CreateApplication();

int main(int argc,char** argv) {
	
	std::cout << "Rose Engine INIT" << std::endl;
	auto app = Rose::CreateApplication();
	app->Run();
	delete app;

}

#endif // 
