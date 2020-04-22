#ifndef CONTEXT_H
#define CONTEXT_H


namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Interface
			{
				namespace API
				{
					class Context
					{
					public:
						// Initialize context
						// NOTE: Owner should call this after constructor
						virtual void Init() = 0;

						virtual void SwapBuffers() = 0;
					};
				}
			}
		}
	}
}



#endif // !CONTEXT_H
