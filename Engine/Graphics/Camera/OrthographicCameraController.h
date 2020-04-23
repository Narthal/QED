#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_H
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_H

#include "Core/Type/Numeric.h"

#include "Core/Time/TimeStep.h"
#include "Event/MouseEvent.h"
#include "Event/WindowEvent.h"

#include "OrthographicCamera.h"


namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Camera
			{
				class OrthographicCameraController
				{
				public: // Ctor / Dtor
					OrthographicCameraController(float aspectRatio, bool rotationEnabled = false);

				public:
					void OnUpdate(Core::Time::TimeStep timeStep);
					void OnEvent(Event::Event& event);

				public:
					inline OrthographicCamera& GetCamera() { return camera; }
					inline const OrthographicCamera& GetCameraConst() const { return camera; }

					inline float GetZoomLevel() { return zoomLevel; }
					inline void SetZoomLevel(float zoomLevel) { this->zoomLevel = zoomLevel; }

				private:
					bool OnMouseScrolled(Event::MouseScrolledEvent& event);
					bool OnWindowResized(Event::WindowResizeEvent& event);

				private:
					float aspectRatio;
					bool rotationEnabled;
					float zoomLevel = 1.0f;
					OrthographicCamera camera;

					Vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };
					float cameraTranslationSpeed = 5.0f;
					float cameraRotation = 0.0f;
					float cameraRotationSpeed = 20.0f;
				};
			}
		}
	}
}

#endif // !ORTHOGRAPHIC_CAMERA_CONTROLLER_H





