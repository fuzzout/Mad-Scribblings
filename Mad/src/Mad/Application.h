#pragma once

#include "Core.h"

#include "Window.h"
#include "Mad/LayerStack.h"
#include "Mad/Events/Event.h"
#include "Mad/Events/ApplicationEvent.h"

namespace Mad {

	class MAD_API Application
	{
		public:
			Application();
			virtual ~Application();

			void Run();

			void OnEvent(Event& e);


		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);


		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	//ToDo in Client
	Application* CreateApplication();
}