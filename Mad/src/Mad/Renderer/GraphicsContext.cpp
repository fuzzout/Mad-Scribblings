#include "madpch.h"
#include "Mad/Renderer/GraphicsContext.h"

#include "Mad/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Mad {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MAD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		MAD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}