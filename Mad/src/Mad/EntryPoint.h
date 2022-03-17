#pragma once

#ifdef MAD_PLATFORM_WINDOWS

extern Mad::Application* Mad::CreateApplication();

int main(int argc, char** argv) {

	auto app = Mad::CreateApplication();
	app->Run();
	delete app;
}

#endif
