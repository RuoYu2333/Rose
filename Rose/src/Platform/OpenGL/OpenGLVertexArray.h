#pragma once
#include "Rose/Renderer/VertexArray.h"

namespace Rose {
	class OpenGLVertexArray :public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		void Bind() const override;
		void Unbind() const override;
		void AddVertexBuffer(const Rose::Ref<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const Rose::Ref<IndexBuffer>& indexBuffer) override;
		virtual const std::vector<Rose::Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Rose::Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::vector<Rose::Ref<VertexBuffer>> m_VertexBuffers;
		Rose::Ref<IndexBuffer> m_IndexBuffer;
	};
}