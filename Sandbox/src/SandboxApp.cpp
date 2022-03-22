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

	}

	void OnEvent(Mad::Event& event) override {
		if (logging)
			MAD_TRACE("{0}", event);

		if (event.GetEventType() == Mad::EventType::KeyPressed)
		{
			Mad::KeyPressedEvent& e = (Mad::KeyPressedEvent&)event;
			if (e.GetKeyCode() == MAD_KEY_TAB) {
				MAD_TRACE("Tab key pressed.");
			} else
			MAD_TRACE("EVENT: Key pressed: {0}", (char)e.GetKeyCode());
		}
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