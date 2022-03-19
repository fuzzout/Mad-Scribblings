#include "Mad.h"
#include "madpch.h"
class Sandbox : public Mad::Application {
public:
	Sandbox()
	{

	}

	~Sandbox() {

	}
};

Mad::Application* Mad::CreateApplication() {
	return new Sandbox();
}