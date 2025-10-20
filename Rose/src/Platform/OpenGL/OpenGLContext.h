 #pragma once

#include "Rose/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Rose {
	class OpenGLContext :public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext();
		
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}  