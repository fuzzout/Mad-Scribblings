#include "Mad.h"
#include "madpch.h"
#include "Mad/ImGui/ImGuiLayer.h"
#include "../imgui/imgui.h"

bool logging = false;

class ExampleLayer : public Mad::Layer {
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
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
	}

	~Sandbox() {

	}
};

Mad::Application* Mad::CreateApplication() {
	return new Sandbox();
}