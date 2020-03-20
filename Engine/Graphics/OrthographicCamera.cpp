#include "EnginePCH.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
				: projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), viewMatrix(glm::identity<glm::mat4>())
			{
				viewProjectionMatrix = projectionMatrix * viewMatrix;
			}

			void OrthographicCamera::RecalculateViewMatrix()
			{
				// TODO: do it like learnopengl
				glm::mat4 transform =
					glm::translate(glm::identity<glm::mat4>(), position) * glm::rotate(glm::identity<glm::mat4>(), glm::radians(rotation), glm::vec3(0, 0, 1));
			
				viewMatrix = glm::inverse(transform);
				viewProjectionMatrix = projectionMatrix * viewMatrix;
			}
		}
	}
}



