#pragma once
#include "Rose/Renderer/Buffer.h"
//抽象类，继承自VertexBuffer，用于实现OpenGL的顶点缓冲区功能
namespace Rose {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const BufferLayout& GetLayout() const { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
	class OpenGLIndexBuffer : public IndexBuffer
	{	
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual uint32_t GetCount() const override { return m_Count; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
		BufferLayout m_Layout;
	};


}