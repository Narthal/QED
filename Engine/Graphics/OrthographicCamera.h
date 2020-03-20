#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H

#include <glm/glm.hpp>

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			class OrthographicCamera
			{
			public: // Ctor
				OrthographicCamera(float left, float right, float bottom, float top);

			#pragma region GET_SET
			public:
				// Get Position
				inline const glm::vec3& GetPosition() const { return position; }
				// Set Position & recalculate viewMatrix
				inline void SetPosition(const glm::vec3& position) { this->position = position; RecalculateViewMatrix(); }

				// Get Rotation
				inline const float GetRotation() const { return rotation; }
				// Set Rotation & recalculate viewMatrix
				inline void SetRotation(float rotation) { this->rotation = rotation; RecalculateViewMatrix(); }

				// Get projectionMatrix
				inline const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }

				// Get viewMatrix
				inline const glm::mat4& GetViewMatrix() const { return viewMatrix; }

				// Get viewProjectionMatrix
				inline const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }
			#pragma endregion

			private:
				void RecalculateViewMatrix();



			private:
				// Projection / view matrices
				glm::mat4 projectionMatrix;
				glm::mat4 viewMatrix;
				glm::mat4 viewProjectionMatrix;

				// Camera transform
				glm::vec3 position = { 0.0f, 0.0f, 0.0f };
				float rotation = 0.0f;
			};
		}
	}
}


#endif // !ORTHOGRAPHIC_CAMERA_H
