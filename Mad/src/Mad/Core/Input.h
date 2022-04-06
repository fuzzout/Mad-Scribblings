#pragma once

#include <glm/glm.hpp>

#include "Mad/Core/KeyCodes.h"
#include "Mad/Core/MouseCodes.h"

namespace Mad {


	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}