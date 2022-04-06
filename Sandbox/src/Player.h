#pragma once
#include "Mad/Core/Timestep.h"
#include "glm/glm.hpp"
#include <Mad/Events/KeyEvent.h>
#include <Mad/Core/KeyCodes.h>
namespace Mad {

	class Player {
	public:
		Player();

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		
		void SetSpeed(float speed);
		void SetPosition(glm::vec2 position);

		glm::vec2 GetPos();
		float GetSpeed();
		glm::vec3 GetDir();

		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
	private:

	private:
		std::string playerName;
		glm::vec2 playerPos;
		glm::vec2 playerDir;
		float playerSpeed = 0.05f;
		bool up, down, left, right = false;
	};
}