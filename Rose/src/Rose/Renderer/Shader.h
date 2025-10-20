#pragma once
#include <string>
namespace Rose {
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
		// Set uniforms

	private:
		uint32_t m_RendererID;


	};


}