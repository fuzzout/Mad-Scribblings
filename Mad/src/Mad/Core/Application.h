#pragma once

#include "Mad/Core/Base.h"
#include "Mad/Core/Window.h"
#include "Mad/Core/LayerStack.h"
#include "Mad/Events/Event.h"
#include "Mad/Events/ApplicationEvent.h"
#include "Mad/Core/Timestep.h"
#include "Mad/ImGui/ImGuiLayer.h"



namespace Mad {

	class Application
	{
		public:
			Application(const std::string& name = "Mad Client");
			virtual ~Application();
			void Close();
			void Run();

			void OnEvent(Event& e);


		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);


		Window& GetWindow() { return *m_Window; }

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	//ToDo in Client
	Application* CreateApplication();
}