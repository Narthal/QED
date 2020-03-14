#ifndef RENDERER_H
#define RENDERER_H

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			enum class RendererAPI
			{
				NONE = 0,
				OpenGL = 1,
			};

			class Renderer
			{
				public:
				inline static RendererAPI GetAPI() { return rendererAPI; }

				private:
				static RendererAPI rendererAPI;
			};
		}
	}
}


#endif // !RENDERER_H
