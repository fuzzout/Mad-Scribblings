#include "Sandbox2D.h"
#include "../imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_BeeHappy = Mad::Texture2D::Create("src/asdf1.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Mad::Timestep ts)
{
	static float rotation = 0.0f;
	rotation += ts * 50.0f;
	// Update
	m_CameraController.OnUpdate(ts);
	Mad::Renderer2D::ResetStats();

	glm::vec4 poo = { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec3 pee = { 1.0f, 1.0f, 1.0f };
	glm::vec2 pop = { 1.0f, 1.0f };
	glm::vec2 pope = { 0.0f, 0.0f };
	// Render
	Mad::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Mad::RenderCommand::Clear();

	Mad::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Mad::Renderer2D::DrawRotoQuad(pee, rotation, pop, 4.0f, m_BeeHappy);
	Mad::Renderer2D::EndScene();

	Mad::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (float y = -5.0f; y < 5.0f; y += 0.5f)
	{
		for (float x = -5.0f; x < 5.0f; x += 0.5f)
		{
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
			Mad::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		}
	}
	Mad::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	
	ImGui::Begin("Settings");
	auto stats = Mad::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();
	
}

void Sandbox2D::OnEvent(Mad::Event& e)
{
	m_CameraController.OnEvent(e);
}