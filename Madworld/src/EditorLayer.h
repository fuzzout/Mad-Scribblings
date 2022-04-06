#pragma once
#include "Mad.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Mad/Renderer/EditorCamera.h"
namespace Mad {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();
		int m_GizmoType = -1;
	private:
		OrthographicCameraController m_CameraController;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Texture2D> m_BeeHappy;
		Ref<Framebuffer> m_Framebuffer;
		Ref<Texture2D> m_Spritesheet;

		bool m_ViewPortFocused = false;
		bool m_ViewPortHovered = false;

		Ref<SubTexture2D> m_GrassTopLeft, m_GrassTopMid, m_GrassTopRight,
			m_GrassLeft, m_GrassMid, m_GrassRight,
			m_GrassLowLeft, m_GrassLowMid, m_GrassLowRight, m_Barrel;
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };


		Ref<Scene> m_ActiveScene;
		Entity m_Square;
		Entity m_CameraEntity;
		Entity m_SecondCamera;
		SceneHierarchyPanel m_SceneHierarchyPanel;
		bool m_PrimaryCamera = true; 
		EditorCamera m_EditorCamera;
		uint32_t m_MapWidth, m_MapHeight;
		std::unordered_map<char, Ref<SubTexture2D>> s_TexMap;

	};
}