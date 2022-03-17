#pragma once

#include "Core.h"

namespace Mad {

	class MAD_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

	};
	//ToDo in Client
	Application* CreateApplication();
}