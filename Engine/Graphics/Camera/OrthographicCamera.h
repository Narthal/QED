#ifndef ORTHOGRAPHIC_CAMERA_H
#define ORTHOGRAPHIC_CAMERA_H


#include <glm/gtc/matrix_transform.hpp>

#include "Core/Type/Numeric.h"

namespace QED
{
	namespace Engine
	{
		namespace Graphics
		{
			namespace Camera
			{
				class OrthographicCamera
				{
				public: // Ctor
					OrthographicCamera(float left, float right, float bottom, float top);

				#pragma region GET_SET
				public:
					// Get Position
					inline const Vec3& GetPosition() const { return position; }
					// Set Position & recalculate viewMatrix
					inline void SetPosition(const Vec3& position) { this->position = position; RecalculateViewMatrix(); }

					// Get Rotation
					inline const float GetRotation() const { return rotation; }
					// Set Rotation & recalculate viewMatrix
					inline void SetRotation(float rotation) { this->rotation = rotation; RecalculateViewMatrix(); }

					// Get projectionMatrix
					inline const Mat4& GetProjectionMatrix() const { return projectionMatrix; }
					// Set projectionMatrix
					inline void SetProjection(float left, float right, float bottom, float top) { projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f); viewProjectionMatrix = projectionMatrix * viewMatrix; }

					// Get viewMatrix
					inline const Mat4& GetViewMatrix() const { return viewMatrix; }

					// Get viewProjectionMatrix
					inline const Mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }
				#pragma endregion

				private: // Internal
					void RecalculateViewMatrix();

				private:
					// Projection / view matrices
					Mat4 projectionMatrix;
					Mat4 viewMatrix;
					Mat4 viewProjectionMatrix;

					// Camera transform
					Vec3 position = { 0.0f, 0.0f, 0.0f };
					float rotation = 0.0f;
				};
			}
		}
	}
}


#endif // !ORTHOGRAPHIC_CAMERA_H
