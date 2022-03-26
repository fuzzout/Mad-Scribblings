#include "madpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"

namespace Mad {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		MAD_CORE_ASSERT(windowHandle, "Window handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MAD_CORE_ASSERT(status, "Failed to initialize Glad.");

		MAD_CORE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
		MAD_CORE_INFO("Shader Version: {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));
		MAD_CORE_INFO("Graphics Device: {0}", glGetString(GL_RENDERER));
	}
	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}