#include "Sandbox2D.h"
#include "../imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController( 1920.0f / 1080.0f )
{
}

void Sandbox2D::OnAttach()
{

}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Mad::Timestep ts)
{



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
	

void Sandbox2D::OnEvent(Mad::Event& e) {

	m_CameraController.OnEvent(e);
	m_Player.OnEvent(e);
}
