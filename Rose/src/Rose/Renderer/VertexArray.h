#pragma once
#include "Rose/Renderer/Buffer.h"
#include <memory>

namespace Rose {
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Rose::Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Rose::Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Rose::Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Rose::Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};


}