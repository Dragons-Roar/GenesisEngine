#pragma once
#include "../Defines.hpp"
#include <glm/glm.hpp>

namespace ge {
	namespace clientcore {
		class OrthographicCamera {
		public:
			OrthographicCamera(float32 left, float32 right, float32 bottom, float32 top);

			void setPosition(const glm::vec3& position) { this->position = position; recalculateViewMatrix(); }
			void setRotation(const float32 rotation) { this->rotation = rotation; recalculateViewMatrix(); }

			const glm::vec3& getPosition() const { return position; }
			float32 getRotation() const { return rotation; }

			const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
			const glm::mat4& getViewMatrix() const { return viewMatrix; }
			const glm::mat4& getViewProjectionMatrix() const { return viewProjectionMatrix; }
			
		private:
			void recalculateViewMatrix();

		private:
			glm::mat4 projectionMatrix;
			glm::mat4 viewMatrix;
			glm::mat4 viewProjectionMatrix;

			glm::vec3 position;
			float32 rotation = 0.f;
		};
	}
}
