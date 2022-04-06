#pragma once

#include "Mad/Core/Layer.h"
#include <Mad/Events/MouseEvent.h>
#include <Mad/Events/KeyEvent.h>
#include <Mad/Events/ApplicationEvent.h>

namespace Mad {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		void SetDarkThemeColors();
		void Begin();
		void End();

		void SetBlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}