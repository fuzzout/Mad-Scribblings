#include "madpch.h"
#include "Player.h"
namespace Mad {

    Player::Player() {
        Player::SetPosition({ 0.0f, 0.0f });
        Player::SetSpeed(0.001f);
        right = false;
        left = false;
        up = false;
        down = false;
    }

    void Player::OnUpdate(Timestep ts)
    {
    }

    void Player::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(MAD_BIND_EVENT_FN(Player::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(MAD_BIND_EVENT_FN(Player::OnKeyReleasedEvent));
    }

    void Player::SetSpeed(float speed)
    {
        Player::playerSpeed = speed;
    }

    void Player::SetPosition(glm::vec2 position)
    {
        Player::playerPos = position;
    }

    glm::vec2 Player::GetPos()
    {
        return Player::playerPos;
    }

    float Player::GetSpeed()
    {
        return Player::playerSpeed;
    }

    glm::vec3 Player::GetDir()
    {
        if (up)
            return { 0.0f, playerSpeed, 1.0f};
        else if (down)
            return { 0.0f, -playerSpeed , 1.0f };
        else if (left)
            return { -playerSpeed, 0.0f , 1.0f };
        else if (right)
            return { playerSpeed, 0.0f , 1.0f };
        else
            return { 0.0f, 0.0f, 1.0f };
    }

    


    bool Player::OnKeyPressedEvent(KeyPressedEvent& event)
    {
        if (event.GetKeyCode() == MAD_KEY_LEFT) {
            if (right)
                right = false;
            left = true;
        }
        if (event.GetKeyCode() == MAD_KEY_RIGHT) {
            if (left)
                left = false;
            right = true;
        }
        if (event.GetKeyCode() == MAD_KEY_UP) {
            if (down)
                down = false;
            up = true;
        }
        if (event.GetKeyCode() == MAD_KEY_DOWN) {
            if (up)
                up = false;
            down = true;
        }
        return false;
    }

    bool Player::OnKeyReleasedEvent(KeyReleasedEvent& event)
    {
        if (event.GetKeyCode() == MAD_KEY_LEFT) {
            left = false;
        }
        if (event.GetKeyCode() == MAD_KEY_RIGHT) {
            right = false;
        }
        if (event.GetKeyCode() == MAD_KEY_UP) {
            up = false;
        }
        if (event.GetKeyCode() == MAD_KEY_DOWN) {
            down = false;
        }
        return false;
    }

}