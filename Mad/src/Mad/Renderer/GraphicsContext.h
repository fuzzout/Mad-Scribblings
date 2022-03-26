#pragma once
namespace Mad {
	class GraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	};
}
