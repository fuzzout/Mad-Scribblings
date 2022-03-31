#include "madpch.h"
#include "Mad/Renderer/RenderCommand.h"

namespace Mad {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}