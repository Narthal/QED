#ifndef CONTEXT_H
#define CONTEXT_H


namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class Context
			{
				public:
				// Initialize context
				// NOTE: Owner should call this after constructor
				virtual void Init() = 0;

				public:
				virtual void SwapBuffers() = 0;

				private:

			};
		}
	}
}



#endif // !CONTEXT_H
