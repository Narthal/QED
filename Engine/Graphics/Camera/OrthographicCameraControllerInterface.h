#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_INTERFACE_H
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_INTERFACE_H

#include "Module/QEDApi.h"

namespace QED::Engine::Graphics::Camera
{
	class OrthographicCameraController;
	class OrthographicCamera;
}

namespace QED::Engine::Core::Time
{
	class TimeStep;
}

namespace QED::Engine::Event
{
	class Event;
}

namespace QED
{
	namespace Interface
	{
		namespace Graphics
		{
			namespace Camera
			{
				class QED_ENGINE_API OrthographicCameraController
				{
				public: // Ctor / Dtor
					OrthographicCameraController(float aspectRatio, bool rotationEnabled = false);
					~OrthographicCameraController();

				public:
					void OnUpdate(Engine::Core::Time::TimeStep timeStep);
					void OnEvent(Engine::Event::Event& event);

				public:
					Engine::Graphics::Camera::OrthographicCamera& GetCamera();
					const Engine::Graphics::Camera::OrthographicCamera& GetCamera() const;

				private:
					Engine::Graphics::Camera::OrthographicCameraController* orthographicCameraController;
				};
			}
		}
	}
}

#endif