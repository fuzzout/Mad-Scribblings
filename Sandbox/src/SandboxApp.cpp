#include "Mad.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Mad/ImGui/ImGuiLayer.h"
#include "../imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool logging = false;

class ExampleLayer : public Mad::Layer {
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Mad::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Mad::Ref<Mad::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Mad::VertexBuffer::Create(vertices, sizeof(vertices)));
		Mad::BufferLayout layout = {
			{ Mad::ShaderData::Float3, "a_Position" },
			{ Mad::ShaderData::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Mad::Ref<Mad::IndexBuffer> indexBuffer;
		indexBuffer.reset(Mad::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->AddIndexBuffer(indexBuffer);

		m_SquareVA.reset(Mad::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Mad::Ref<Mad::VertexBuffer> squareVB;
		squareVB.reset(Mad::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Mad::ShaderData::Float3, "a_Position" },
			{ Mad::ShaderData::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Mad::Ref<Mad::IndexBuffer> squareIB;
		squareIB.reset(Mad::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->AddIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Mad::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Mad::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("src/assets/shaders/Texture.glsl");

		m_Texture = Mad::Texture2D::Create("src/asdf1.png");

		std::dynamic_pointer_cast<Mad::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Mad::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Mad::Timestep ts) override
	{
		Mad::RenderCommand::SetClearColor({ 1, 1, 0, 1 });
		Mad::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Mad::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Mad::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Mad::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		
				glm::vec3 pos(0.9f, 0.9, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Mad::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Mad::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Hazel::Renderer::Submit(m_Shader, m_VertexArray);

		Mad::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::SliderFloat("Pos X", &m_CameraPosition.x, 0.01f, 2.0f);
		ImGui::SliderFloat("Pos Y", &m_CameraPosition.y, 0.01f, 2.0f);
		ImGui::End();
	}

	void OnEvent(Mad::Event& event) override {
		Mad::EventDispatcher dispatch(event);
		dispatch.Dispatch<Mad::KeyPressedEvent>(MAD_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));

	}
	bool OnKeyPressedEvent(Mad::KeyPressedEvent& event) {

		if (event.GetKeyCode() == MAD_KEY_PAGE_DOWN) {
			if (cameraSpeed > 0.01f)
				cameraSpeed -= 0.01f;
		}
		if (event.GetKeyCode() == MAD_KEY_PAGE_UP) {
			if (cameraSpeed < 0.8f)
				cameraSpeed += 0.01f;
		}
		return false;
	}

private:
		//openGL temps
		Mad::Ref<Mad::VertexArray> m_VertexArray;
		Mad::Ref<Mad::Shader> m_Shader;

		Mad::Ref<Mad::VertexArray> m_SquareVA;
		Mad::Ref<Mad::Shader> m_FlatColorShader;
		Mad::Ref<Mad::Shader> m_TextureShader;

		Mad::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;

		glm::vec3 m_SquareTransform;
		Mad::ShaderLibrary m_ShaderLibrary;
		glm::vec3 m_SquareColor = {0.2, 0.3f, 0.8f};

		Mad::Ref<Mad::Texture2D> m_Texture, m_SecondTex;

		float cameraSpeed = 0.01f;
		float m_CameraRotation = 0.0f;
};

class Sandbox : public Mad::Application {
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Mad::Application* Mad::CreateApplication() {
	return new Sandbox();
}