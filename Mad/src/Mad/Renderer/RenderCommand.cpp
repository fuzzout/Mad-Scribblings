#include "madpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Mad {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}