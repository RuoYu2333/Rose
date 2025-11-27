#include "rspch.h"
#include "CameraController.h"


namespace Rose {
	CameraController::CameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel,
			-m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}
	void CameraController::OnUpdate(TimeStep deltaTime)
	{
		//RS_TRACE("Delta time :{0}s {1}ms",timeStep.GetSeconds(),timeStep.GetMilliseconds());
		if (Input::IsKeyPressed(RS_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraTranslationSpeed * deltaTime;
		}
		else if (Input::IsKeyPressed(RS_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraTranslationSpeed * deltaTime;
		}
		if (Input::IsKeyPressed(RS_KEY_UP))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * deltaTime;
		}
		else if (Input::IsKeyPressed(RS_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * deltaTime;
		}
		if (m_Rotation) {
			if (Input::IsKeyPressed(RS_KEY_C))
			{
				m_CameraRotation += m_AspectRatio * m_CameraRotationSpeed * deltaTime;
			}
			else if (Input::IsKeyPressed(RS_KEY_Z))
			{
				m_CameraRotation -= m_AspectRatio * m_CameraRotationSpeed * deltaTime;
			}
			m_Camera.SetRotation(m_CameraRotation);
		}
		m_Camera.SetPosition(m_CameraPosition);
		
	}
	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(RS_BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(RS_BIND_EVENT_FN(CameraController::OnWindowResized));
	}
	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		Resize(m_AspectRatio * 2.0f * m_ZoomLevel, 2.0f * m_ZoomLevel);
		return false;
	}
	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		Resize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
	void CameraController::Resize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
			-m_ZoomLevel, m_ZoomLevel);
	}
}