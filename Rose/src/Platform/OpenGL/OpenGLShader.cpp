#include "rspch.h"
#include "OpenGLShader.h"
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>


namespace Rose {
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		RS_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}
	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		// Read file content
		std::string source = ReadFile(filepath);
		auto shaderSource = ParseShader(source);
		Compile(shaderSource);
		// Extract name from filepath
		size_t lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		size_t lastDot = filepath.rfind('.');
		size_t count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);  
	}
	OpenGLShader::OpenGLShader(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc)
		:m_Name(name)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(shaderSources);
	}
	std::unordered_map<GLenum, std::string> OpenGLShader::ParseShader(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			RS_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			RS_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] =
				source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));

		}

		return shaderSources;
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string code;
		std::ifstream in(filepath, std::ios::in, std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			code.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&code[0], code.size());
			in.close();
		}
		else RS_CORE_ERROR("Could not open file '{0}'", filepath);
		return code;
	}
	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
		// Create an empty vertex shader handle
		GLuint program = glCreateProgram();
		RS_CORE_ASSERT(shaderSources.size() <= 2, "Only support 2 shaders!");
		std::array<GLenum,2> shaderIDs;
		int index = 0;
		for (auto& kv : shaderSources) {
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint ShaderType = glCreateShader(type);

			const GLchar* sourceCstr = source.c_str();
			glShaderSource(ShaderType, 1, &sourceCstr, 0);

			// Compile the vertex shader
			glCompileShader(ShaderType);

			GLint isCompiled = 0;
			glGetShaderiv(ShaderType, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(ShaderType, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(ShaderType, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(ShaderType);

				// Use the infoLog as you see fit.
				RS_CORE_ERROR("{0}", infoLog.data());
				RS_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}
			glAttachShader(program, ShaderType);
			shaderIDs[index++] = ShaderType;
		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto id : shaderIDs) {
				glDeleteShader(id);
			}

			// Use the infoLog as you see fit.
			RS_CORE_ERROR("{0}", infoLog.data());
			RS_CORE_ASSERT(false, "OpenGLShader link failure!");
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		
		for (auto id : shaderIDs) {
			glDetachShader(program, id);
		}
		
		m_RendererID = program;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}
	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) const
	{
		GLint location = glGetUniformLocation(m_RendererID,  name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vector) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, vector.x, vector.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vector) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vector) const
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		UploadUniformMat4(name, matrix);
	}



}