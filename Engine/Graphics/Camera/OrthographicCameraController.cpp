#include "EnginePCH.h"
#include "OrthographicCameraController.h"

#include "../Input/CoreInput.h"
#include "../Input/Keycodes.h"

#include "Profiler/Instrumentor.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Camera
			{
				OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotationEnabled)
					: aspectRatio(aspectRatio), rotationEnabled(rotationEnabled),
					camera(-aspectRatio * zoomLevel, aspectRatio* zoomLevel, -zoomLevel, zoomLevel)
				{
				}

				void OrthographicCameraController::OnUpdate(Core::Time::TimeStep timeStep)
				{
					QED_PROFILE_FUNCTION();

					// Move camera
					// Left / right
					if (Input::CoreInput::IsKeyPressed(Input::key_A))
					{
						cameraPosition.x -= cameraTranslationSpeed * timeStep;
					}
					else if (Input::CoreInput::IsKeyPressed(Input::key_D))
					{
						cameraPosition.x += cameraTranslationSpeed * timeStep;
					}

					// Up / down
					if (Input::CoreInput::IsKeyPressed(Input::key_W))
					{
						cameraPosition.y += cameraTranslationSpeed * timeStep;
					}
					else if (Input::CoreInput::IsKeyPressed(Input::key_S))
					{
						cameraPosition.y -= cameraTranslationSpeed * timeStep;
					}

					camera.SetPosition(cameraPosition);

					// Rotation
					if (rotationEnabled)
					{
						if (Input::CoreInput::IsKeyPressed(Input::key_Q))
						{
							cameraRotation -= cameraRotationSpeed * timeStep;
						}

						if (Input::CoreInput::IsKeyPressed(Input::key_E))
						{
							cameraRotation += cameraRotationSpeed * timeStep;
						}

						camera.SetRotation(cameraRotation);
					}
				}

				void OrthographicCameraController::OnEvent(Event::Event& event)
				{
					QED_PROFILE_FUNCTION();

					Event::EventDispatcher dispatcher(event);
					dispatcher.Dispatch<Event::MouseScrolledEvent>(BIND_EVENT_FUCTION(OrthographicCameraController::OnMouseScrolled));
					dispatcher.Dispatch<Event::WindowResizeEvent>(BIND_EVENT_FUCTION(OrthographicCameraController::OnWindowResized));
				}

				bool OrthographicCameraController::OnMouseScrolled(Event::MouseScrolledEvent& event)
				{
					QED_PROFILE_FUNCTION();

					zoomLevel -= event.GetYOffset();
					camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
					return false;
				}

				bool OrthographicCameraController::OnWindowResized(Event::WindowResizeEvent& event)
				{
					QED_PROFILE_FUNCTION();

					aspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
					camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
					return false;
				}
			}
		}
	}
}

