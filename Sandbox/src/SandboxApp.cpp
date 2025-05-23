#include <Rose.h>

class Sandbox : public Rose::Application {

    public:
		Sandbox() {
		}
		~Sandbox() {
		}

};
Rose::Application* Rose::CreateApplication() {
	return new Sandbox();
}