#include "CameraController.hpp"
#include "Input.hpp"

namespace ge {
	namespace clientcore {
		OrthographicCameraController::OrthographicCameraController(float32 aspectRatio, bool rotation):
			aspectRatio(aspectRatio),
			camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel),
			useRotation(rotation) {
		}

		void OrthographicCameraController::onUpdate(ge::core::Timestep ts) {
			if(Input::isKeyDown(Key::A)) {
				position.x -= translationSpeed * ts;
			} else if(Input::isKeyDown(Key::D)) {
				position.x += translationSpeed * ts;
			}

			if(Input::isKeyDown(Key::W)) {
				position.y += translationSpeed * ts;
			} else if(Input::isKeyDown(Key::S)) {
				position.y -= translationSpeed * ts;
			}

			if(useRotation) {
				if(Input::isKeyDown(Key::Q)) {
					rotation += rotationSpeed * ts;
				} else if(Input::isKeyDown(Key::E)) {
					rotation -= rotationSpeed * ts;
				}
				camera.setRotation(rotation);
			}

			camera.setPosition(position);
			translationSpeed = zoomLevel * 2.f;
		}

		void OrthographicCameraController::onEvent(ge::core::Event& e) {
			ge::core::EventDispatcher dispatcher(e);
			dispatcher.dispatch<ge::core::MouseScrolledEvent>(GE_BindEventFunction(OrthographicCameraController::onMouseScrolled));
			dispatcher.dispatch<ge::core::WindowResizeEvent>(GE_BindEventFunction(OrthographicCameraController::onWindowResized));
		}

		bool OrthographicCameraController::onMouseScrolled(ge::core::MouseScrolledEvent& e) {
			zoomLevel -= e.getY() * 0.25f;
			zoomLevel = GE_Max(zoomLevel, 0.25f);
			camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);

			return false;
		}
		bool OrthographicCameraController::onWindowResized(ge::core::WindowResizeEvent& e) {
			aspectRatio = (float32) e.getWidth() / (float32) e.getHeight();
			camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);

			return false;
		}
	}
}
