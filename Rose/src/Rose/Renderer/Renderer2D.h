#pragma once
#include <glm/glm.hpp>
#include "Rose/Camera/Camera.h"
#include "Rose/Renderer/Texture.h"

namespace Rose {
	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();
		static void BeginScene(const Camera& camera);
		static void EndScene();
		static void Flush();
		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture);
	};
}