#pragma once
#include "Mad/Core.h"
#include "Mad/Events/Event.h"

#include "Mad/Core/Timestep.h"

namespace Mad {

	class MAD_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}