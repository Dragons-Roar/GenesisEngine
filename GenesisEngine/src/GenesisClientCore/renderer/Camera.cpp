#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace ge {
	namespace clientcore {
		OrthographicCamera::OrthographicCamera(float32 left, float32 right, float32 bottom, float32 top):
			projectionMatrix(glm::ortho(left, right, bottom, top, -1.f, 1.f)),
			viewMatrix(1.f)
		{
			viewProjectionMatrix = projectionMatrix * viewMatrix;
		}

		void OrthographicCamera::recalculateViewMatrix() {
			glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * 
				glm::rotate(glm::mat4(1.f), rotation, glm::vec3(0, 0, 1));

			viewMatrix = glm::inverse(transform);
			viewProjectionMatrix = projectionMatrix * viewMatrix;
		}
	}
}
