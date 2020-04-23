#include "EnginePCH.h"
#include "OrthographicCamera.h"

#include "Profiler/Instrumentor.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Camera
			{
				OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
					: projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), viewMatrix(glm::identity<Mat4>())
				{
					viewProjectionMatrix = projectionMatrix * viewMatrix;
				}

				void OrthographicCamera::RecalculateViewMatrix()
				{
					QED_PROFILE_FUNCTION();

					// TODO: do it like learnopengl
					Mat4 transform =
						glm::translate(glm::identity<Mat4>(), position) * glm::rotate(glm::identity<Mat4>(), glm::radians(rotation), Vec3(0, 0, 1));

					viewMatrix = glm::inverse(transform);
					viewProjectionMatrix = projectionMatrix * viewMatrix;
				}
			}
		}
	}
}



