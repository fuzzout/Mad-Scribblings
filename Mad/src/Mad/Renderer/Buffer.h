#pragma once

namespace Mad {
	
	enum class ShaderData {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataSize(ShaderData type) {
		switch (type) {
		case ShaderData::Float:		return 4;
		case ShaderData::Float2:	return 4 * 2;
		case ShaderData::Float3:	return 4 * 3;
		case ShaderData::Float4:	return 4 * 4;
		case ShaderData::Mat3:		return 4 * 3 * 3;
		case ShaderData::Mat4:		return 4 * 4 * 4;
		case ShaderData::Int:		return 4;
		case ShaderData::Int2:		return 4 * 2;
		case ShaderData::Int3:		return 4 * 3;
		case ShaderData::Int4:		return 4 * 4;
		case ShaderData::Bool:		return 1;
		}
		MAD_CORE_ASSERT(false, "Unknown ShaderData type.");
		return 0;
	}

	struct BufferElement {
		std::string Name;
		ShaderData Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		//BufferElement() { }

		BufferElement(ShaderData type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataSize(type)), Offset(0), Normalized(normalized)
		{

		}

		uint32_t GetComponentCount() const {
			switch (Type) {
				case ShaderData::Float:		return 1;
				case ShaderData::Float2:	return 2;
				case ShaderData::Float3:	return 3;
				case ShaderData::Float4:	return 4;
				case ShaderData::Int:		return 1;
				case ShaderData::Int2:		return 2;
				case ShaderData::Int3:		return 3;
				case ShaderData::Int4:		return 4;
				case ShaderData::Mat3:		return 3;// *3;
				case ShaderData::Mat4:		return 4;// *4;
				case ShaderData::Bool:		return 1;
			}
			MAD_CORE_ASSERT(false, "Unknown ShaderData type.");
			return 0;
		}

	};
	class BufferLayout {
	public:
		BufferLayout() { }

		BufferLayout(std::initializer_list<BufferElement> elements) : m_Elements(elements) {
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride() 
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
				
				//lol activate for wonky triangle
				//m_Stride = element.Size; 
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;
		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);

	};

}