#include "rspch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Rose {
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		default:
			break;
		case RendererAPI::API::None:
			RS_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}
		RS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		default:
			break;
		case RendererAPI::API::None:
			RS_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return  std::make_shared<OpenGLShader>(name,vertexSrc,fragmentSrc);
		}
		RS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	ShaderLab::ShaderLab()
	{
	}

	ShaderLab::~ShaderLab()
	{
	}
	void ShaderLab::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		RS_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLab::Add(const std::string& name, const Ref<Shader>& shader)
	{
		RS_CORE_ASSERT(!isExits(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLab::Load(const std::string& filepath)
	{
		auto shader = Ref<Shader>(Shader::Create(filepath));
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLab::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Ref<Shader>(Shader::Create(filepath));
		Add(name,shader);
		return shader;
	}

	Ref<Shader> ShaderLab::Get(const std::string& name)
	{
		RS_CORE_ASSERT(isExits(name), "Shader not found!");
		return m_Shaders[name];
	}



}