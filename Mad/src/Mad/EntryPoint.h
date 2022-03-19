#pragma once

#ifdef MAD_PLATFORM_WINDOWS

extern Mad::Application* Mad::CreateApplication();

int main(int argc, char** argv) {

	Mad::Log::Init();
	MAD_CORE_ERROR("I hear screaming... Core logger live.");
	MAD_CORE_TRACE("I hear screaming... Core logger live.");
	MAD_CORE_WARN("I hear screaming... Core logger live.");
	MAD_INFO("I hear cats meowing... Client logger live.");

	auto app = Mad::CreateApplication();
	app->Run();
	delete app;
}

#endif
