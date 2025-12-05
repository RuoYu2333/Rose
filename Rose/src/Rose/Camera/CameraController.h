#pragma once
#include "Rose/Camera/Camera.h"
#include "Rose/Core/Input.h"

#include "Rose/Events/MouseEvent.h"
#include "Rose/Events/ApplicationEvent.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Rose/Core/KeyCodes.h"
#include "Rose/Core/TimeStep.h"

namespace Rose {
	class CameraController {
	public:
		CameraController(float aspectRatio, bool rotation = false);
		
		void OnUpdate(TimeStep deltaTime);
		void OnEvent(class Event& e);
		inline class Camera& GetCamera() { return m_Camera; }
		inline const class Camera& GetCamera() const { return m_Camera; }
		void Resize(float width, float height);
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		void GetZoomLevel(float level)  { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(class MouseScrolledEvent& e);
		bool OnWindowResized(class WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		Camera m_Camera;
		bool m_Rotation;
		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};
}