#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_INTERFACE_H
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_INTERFACE_H

#include "Module/QEDApi.h"


#include "Module/QEDApi.h"
#include "Core/Time/TimeStep.h"
#include "Event/MouseEvent.h"
#include "Event/WindowEvent.h"

#include "OrthographicCamera.h"

namespace QED::Engine::Graphics::Camera
{
	class OrthographicCameraController;
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

				extern "C"
				{
					QED_ENGINE_API OrthographicCameraController* CreateOrthographicCameraController(float aspectRatio, bool rotationEnabled = false);

					QED_ENGINE_API void DeleteOrthographicCameraController(OrthographicCameraController* orthographicCameraController);
				}
			}
		}
	}
}

#endif