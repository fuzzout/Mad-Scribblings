#pragma once

#include "Mad.h"

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

	// Temp
	Mad::Ref<Mad::VertexArray> m_SquareVA;
	Mad::Ref<Mad::Shader> m_FlatColorShader;
	Mad::Ref<Mad::Texture2D> m_BeeHappy;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};