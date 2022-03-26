#include "madpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Mad {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:		MAD_CORE_ASSERT(false, "No renderer API selected.");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		MAD_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}


	/*
	
	INDEX BUFFER
	
	*/
	IndexBuffer* IndexBuffer::Create(uint32_t* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:		MAD_CORE_ASSERT(false, "No renderer API selected.");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(vertices, size);
		}
		MAD_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}