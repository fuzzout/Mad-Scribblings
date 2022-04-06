#pragma once

#include "Mad.h"
#include "Player.h"

class Sandbox2D : public Mad::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Mad::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Mad::Event& e) override;
private:
	Mad::OrthographicCameraController m_CameraController;

	Mad::Player m_Player;
	// Temp
	Mad::Ref<Mad::VertexArray> m_SquareVA;
	Mad::Ref<Mad::Shader> m_FlatColorShader;
	Mad::Ref<Mad::Texture2D> m_BeeHappy;
	Mad::Ref<Mad::Texture2D> m_Spritesheet;

	glm::vec2 barrelDir = { 0.0f, 0.0f };
	glm::vec3 barrelPos = { 0.0f, 0.0f, 1.0f };

	Mad::Ref<Mad::SubTexture2D> m_GrassTopLeft, m_GrassTopMid, m_GrassTopRight,
								m_GrassLeft, m_GrassMid, m_GrassRight, 
								m_GrassLowLeft, m_GrassLowMid, m_GrassLowRight, m_Barrel;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	uint32_t m_MapWidth, m_MapHeight;
	std::unordered_map<char, Mad::Ref<Mad::SubTexture2D>> s_TexMap;
};