#include "Mad.h"
#include "madpch.h"

#include "Mad/ImGui/ImGuiLayer.h"

bool logging = false;

class ExampleLayer : public Mad::Layer {
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (logging)
		MAD_INFO("ExampleLayer::update");
	}

	void OnEvent(Mad::Event& event) override {
		if (logging)
		MAD_TRACE("{0}", event);
	}

};

class Sandbox : public Mad::Application {
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Mad::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Mad::Application* Mad::CreateApplication() {
	return new Sandbox();
}