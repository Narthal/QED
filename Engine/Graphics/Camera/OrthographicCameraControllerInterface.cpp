#include "EnginePCH.h"
#include "OrthographicCameraControllerInterface.h"

#include "OrthographicCameraController.h"

namespace QED
{
	namespace Interface
	{
		namespace Graphics
		{
			namespace Camera
			{
				OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotationEnabled)
				{
					orthographicCameraController = new Engine::Graphics::Camera::OrthographicCameraController(aspectRatio, rotationEnabled);
				}

				OrthographicCameraController::~OrthographicCameraController()
				{
					delete orthographicCameraController;
				}

				void OrthographicCameraController::OnUpdate(Engine::Core::Time::TimeStep timeStep)
				{
					orthographicCameraController->OnUpdate(timeStep);
				}

				void OrthographicCameraController::OnEvent(Engine::Event::Event& event)
				{
					orthographicCameraController->OnEvent(event);
				}

				Engine::Graphics::Camera::OrthographicCamera& OrthographicCameraController::GetCamera()
				{
					return orthographicCameraController->GetCamera();
				}

				const Engine::Graphics::Camera::OrthographicCamera& OrthographicCameraController::GetCamera() const
				{
					return orthographicCameraController->GetCamera();
				}

				QED_ENGINE_API OrthographicCameraController* CreateOrthographicCameraController(float aspectRatio, bool rotationEnabled)
				{
					return new OrthographicCameraController(aspectRatio, rotationEnabled);
				}

				QED_ENGINE_API void DeleteOrthographicCameraController(OrthographicCameraController* orthographicCameraController)
				{
					delete orthographicCameraController;
				}
			}
		}
	}
}


