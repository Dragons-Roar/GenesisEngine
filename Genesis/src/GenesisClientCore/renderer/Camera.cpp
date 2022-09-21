#include "Camera.hpp"
#include <GenesisCore/Logger.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ge {
	namespace clientcore {
		/***********************
		 * Orthographic Camera *
		 ***********************/

		OrthographicCamera::OrthographicCamera(float32 left, float32 right, float32 bottom, float32 top): projectionMatrix(glm::ortho(left, right, bottom, top, -1.f, 1.f)),
		                                                                                                  viewMatrix(1.f),
		                                                                                                  position(0.f) {
			viewProjectionMatrix = projectionMatrix * viewMatrix;
		}

		void OrthographicCamera::setProjection(float32 left, float32 right, float32 bottom, float32 top) {
			projectionMatrix = glm::ortho(left, right, bottom, top, -1.f, 1.f);
			viewProjectionMatrix = projectionMatrix * viewMatrix;
		}

		void OrthographicCamera::update() {
			glm::mat4 transform = glm::translate(glm::mat4(1.f), position) *
			    glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0, 0, 1));

			viewMatrix = glm::inverse(transform);
			viewProjectionMatrix = projectionMatrix * viewMatrix;
		}

		/**********************
		 * Perspective Camera *
		 **********************/

		PerspectiveCamera::PerspectiveCamera(float32 aspectRatio, float32 fov) {
			setPerspective(aspectRatio, fov);
		}
		void PerspectiveCamera::setPerspective(float32 aspectRatio, float32 fov) {
			this->aspectRatio = aspectRatio; this->fov = fov;
			projectionMatrix = glm::perspective(glm::radians(fov * 0.5f), aspectRatio, 0.1f, 100000.f);
			update();
			updateRotation();
		}

		void PerspectiveCamera::update() {
			viewMatrix = glm::lookAt(pos, pos + forward, up);
			viewProjectionMatrix = projectionMatrix * viewMatrix;
		}
		void PerspectiveCamera::updateRotation() {
			pitch = GE_Clamp(pitch, -89.f, 89.f);

			float32 yawR = glm::radians(yaw);
			float32 pitchR = glm::radians(pitch);

			forward.x = cos(yawR) * cos(pitchR);
			forward.y = sin(pitchR);
			forward.z = sin(yawR) * cos(pitchR);
			forward = glm::normalize(forward);

			right = glm::normalize(glm::cross(forward, up));
		}

		void PerspectiveCamera::moveUp(float32 amount) {
			pos.y += amount;
		}
		void PerspectiveCamera::moveRight(float32 amount) {
			pos += right * amount;
		}
		void PerspectiveCamera::moveForward(float32 amount) {
			pos += forward * glm::vec3(amount, 0.f, amount);
		}
	}
}
