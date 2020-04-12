#ifndef SANDBOX_2D_H
#define SANDBOX_2D_H

#include "QED.h"

namespace QED
{
	namespace Sandbox
	{
		class Sandbox2D : public Engine::Layer::Layer
		{
		public:
			Sandbox2D();

		public:	// Layer events
			// Override layer's OnAttach method
			virtual void OnAttach() override;

			// Override layer's OnDetach method
			virtual void OnDetach() override;

			// Override layer's OnUpdate method
			virtual void OnUpdate(Engine::Core::Time::TimeStep timeStep) override;

			// Override layer's OnUIRender method
			virtual void OnUIRender() override;

			// Override layer's OnEvent method
			virtual void OnEvent(Engine::Event::Event& event) override;

		public: // Module
			// Get name for module interface
			QED_MODULE_API virtual const char* GetName() const override
			{
				return "SandboxLayer";
			}

		private:
			Engine::Graphics::OrthographicCameraController cameraController;

			// TODO: Temporary
			Ref<Engine::Graphics::VertexArray> vertexArray;
			Ref<Engine::Graphics::Shader> shader;
			glm::vec4 squareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		};
	}
}



#endif // !SANDBOX_2D_H