#include "madpch.h"
#include "Mad/Renderer/Buffer.h"

#include "Mad/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Mad {
		Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
		{
			switch (Renderer::GetAPI())
			{
			case RendererAPI::API::None:    MAD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(size);
			}

			MAD_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}

		Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		MAD_CORE_ASSERT(false, "No renderer API selected.");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		MAD_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}


	/*
	
	INDEX BUFFER
	
	*/
		Ref<IndexBuffer> IndexBuffer::Create(uint32_t * vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		MAD_CORE_ASSERT(false, "No renderer API selected.");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(vertices, size);
		}
		MAD_CORE_ASSERT(false, "Unknown RendererAPI.");
		return nullptr;
	}
}