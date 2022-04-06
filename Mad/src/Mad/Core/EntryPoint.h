#pragma once
#include "Mad/Core/Base.h"

#ifdef MAD_PLATFORM_WINDOWS

extern Mad::Application* Mad::CreateApplication();

int main(int argc, char** argv) {

	Mad::Log::Init();
	auto app = Mad::CreateApplication();
	app->Run();
	delete app;
}

#endif
