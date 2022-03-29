#include "madpch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Mad {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderData type) {
		switch (type) {
		case Mad::ShaderData::Float:    return GL_FLOAT;
		case Mad::ShaderData::Float2:   return GL_FLOAT;
		case Mad::ShaderData::Float3:   return GL_FLOAT;
		case Mad::ShaderData::Float4:   return GL_FLOAT;
		case Mad::ShaderData::Mat3:     return GL_FLOAT;
		case Mad::ShaderData::Mat4:     return GL_FLOAT;
		case Mad::ShaderData::Int:      return GL_INT;
		case Mad::ShaderData::Int2:     return GL_INT;
		case Mad::ShaderData::Int3:     return GL_INT;
		case Mad::ShaderData::Int4:     return GL_INT;
		case Mad::ShaderData::Bool:     return GL_BOOL;
		}
		MAD_CORE_ASSERT(false, "Unknown ShaderDataTypeToOpenGL conversion.");
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
		MAD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);

			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}


}