#include "madpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Mad {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderData type) {
		switch (type) {
		case ShaderData::Float:    return GL_FLOAT;
		case ShaderData::Float2:   return GL_FLOAT;
		case ShaderData::Float3:   return GL_FLOAT;
		case ShaderData::Float4:   return GL_FLOAT;
		case ShaderData::Mat3:     return GL_FLOAT;
		case ShaderData::Mat4:     return GL_FLOAT;
		case ShaderData::Int3:     return GL_INT;
		case ShaderData::Bool:     return GL_BOOL;
		case ShaderData::Int:      return GL_INT;
		case ShaderData::Int2:     return GL_INT;
		case ShaderData::Int4:     return GL_INT;
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

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
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

	void OpenGLVertexArray::AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}


}