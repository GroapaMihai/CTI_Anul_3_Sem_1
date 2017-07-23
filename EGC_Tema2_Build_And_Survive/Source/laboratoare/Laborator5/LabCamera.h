#pragma once
#include <iostream>
#include <include/glm.h>
#include <include/math.h>

namespace Laborator
{
	class Camera
	{
		public:
			Camera()
			{
				position = glm::vec3(0, 2, 5);
				forward = glm::vec3(0, 0, -1);
				up		= glm::vec3(0, 1, 0);
				right	= glm::vec3(1, 0, 0);
				distanceToTarget = 4;
			}

			Camera(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
			{
				Set(position, center, up);
			}

			~Camera()
			{ }

			// Update camera
			void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
			{
				this->position = position;
				forward = glm::normalize(center - position);
				right	= glm::cross(forward, up);
				this->up = glm::cross(right,forward);
			}

			void MoveForward(float distance)
			{
				glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
			}

			void TranslateForward(float distance)
			{
				position += glm::normalize(forward) * distance;
			}

			void TranslateToTarget(float distance)
			{
				position += glm::normalize(position) * distance;
			}


			void TranslateUpword(float distance)
			{
				position += glm::normalize(up) * distance;
			}

			void TranslateRight(float distance)
			{
				position += glm::normalize(right) * distance;
			}

			void RotateFirstPerson_OX(float angle)
			{
				glm::vec4 newVector1 = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(right)) * glm::vec4(forward, 1);
				forward = glm::normalize(glm::vec3(newVector1));

				up = glm::cross(right, forward);
			}

			void RotateFirstPerson_OY(float angle)
			{
				glm::vec4 newVector1 = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1);
				forward = glm::normalize(glm::vec3(newVector1));

				glm::vec4 newVector2 = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1);
				right = glm::normalize(glm::vec3(newVector2));

				up = glm::cross(right, forward);
			}

			void RotateThirdPerson_OX(float angle)
			{
				// TODO
				// Rotate the camera in Third Person mode - OX axis
				// Use distanceToTarget as translation distance
				TranslateToTarget(distanceToTarget);
				RotateFirstPerson_OX(angle);
				TranslateToTarget(-distanceToTarget);
			}

			void RotateThirdPerson_OY(float angle)
			{
				// TODO
				// Rotate the camera in Third Person mode - OY axis
				TranslateToTarget(distanceToTarget);
				RotateFirstPerson_OY(angle);
				TranslateToTarget(-distanceToTarget);
			}

			glm::mat4 GetViewMatrix()
			{
				// Returns the View Matrix
				return glm::lookAt(position, position + forward, up);
			}

			glm::vec3 GetTargetPosition()
			{
				return position + forward * distanceToTarget;
			}

		public:
			float distanceToTarget;
			glm::vec3 position;
			glm::vec3 forward;
			glm::vec3 right;
			glm::vec3 up;
		};
}
