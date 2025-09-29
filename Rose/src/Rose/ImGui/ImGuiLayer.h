#pragma once

#include "Rose/Layer.h"

#include "Rose/Events/ApplicationEvent.h"
#include "Rose/Events/KeyEvent.h"
#include "Rose/Events/MouseEvent.h"

namespace Rose {

	class ROSE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}