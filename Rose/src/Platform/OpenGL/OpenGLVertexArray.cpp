#include "rspch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Rose {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Rose::ShaderDataType::Float:    return GL_FLOAT;
		case Rose::ShaderDataType::Float2:   return GL_FLOAT;
		case Rose::ShaderDataType::Float3:   return GL_FLOAT;
		case Rose::ShaderDataType::Float4:   return GL_FLOAT;
		case Rose::ShaderDataType::Mat3:     return GL_FLOAT;
		case Rose::ShaderDataType::Mat4:     return GL_FLOAT;
		case Rose::ShaderDataType::Int:      return GL_INT;
		case Rose::ShaderDataType::Int2:     return GL_INT;
		case Rose::ShaderDataType::Int3:     return GL_INT;
		case Rose::ShaderDataType::Int4:     return GL_INT;
		case Rose::ShaderDataType::Bool:     return GL_BOOL;
		}
		RS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) 
	{	
		RS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		uint32_t index = 0;
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetElementCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) 
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}