#include "madpch.h"
#include "Mad/Renderer/VertexArray.h"

#include "Mad/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Mad {
		Ref<VertexArray> VertexArray::Create()
		{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: MAD_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}

		MAD_CORE_ASSERT(false, "UnknownRendererAPI!");
		return nullptr;
	}
}