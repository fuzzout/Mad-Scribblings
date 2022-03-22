#pragma once

#include "Mad/Layer.h"
#include <Mad/Events/MouseEvent.h>
#include <Mad/Events/KeyEvent.h>
#include <Mad/Events/ApplicationEvent.h>

namespace Mad {

	class MAD_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
			float m_Time = 0.0f;
	};
}