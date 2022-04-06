#include "Mad.h"
#include <../imgui/imgui.h>
#include <Mad/Core/EntryPoint.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EditorLayer.h"

namespace Mad {
	class MadWorld : public Mad::Application {
	public:
		MadWorld()
			: Application("Madworld")
		{
			PushLayer(new EditorLayer());
		}

		~MadWorld() {

		}
	};

	Application* CreateApplication() {
		return new MadWorld();
	}
}