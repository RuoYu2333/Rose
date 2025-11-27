#pragma once
#include "Rose/Renderer/Shader.h"
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

typedef unsigned int GLenum;

namespace Rose {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& filepath);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		const std::string& GetName() const override { return m_Name; }

		// Set uniforms
		void UploadUniformInt(const std::string& name, int value) const;
		
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;

		
		void UploadUniformFloat(const std::string& name, float value) const;
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector) const;
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector) const;
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector) const;
	
	private:
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		std::unordered_map<GLenum,std::string> ParseShader(const std::string& source);
		std::string ReadFile(const std::string& filepath);

	private:
		uint32_t m_RendererID;
		std::string m_Name; 
	};
}