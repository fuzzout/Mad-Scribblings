#pragma once

#include "Mad/Core/Layer.h"
#include <Mad/Events/MouseEvent.h>
#include <Mad/Events/KeyEvent.h>
#include <Mad/Events/ApplicationEvent.h>

namespace Mad {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
			float m_Time = 0.0f;
	};
}