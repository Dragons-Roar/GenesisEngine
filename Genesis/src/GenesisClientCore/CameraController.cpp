#include "CameraController.hpp"
#include "GenesisClientCore/Input.hpp"
#include "GenesisClientCore/Application.hpp"

namespace ge {
	namespace clientcore {
		/**********************************
		 * Orthographic Camera Controller *
		 **********************************/

		OrthographicCameraController::OrthographicCameraController(float32 aspectRatio, bool rotation): aspectRatio(aspectRatio),
		                                                                                                camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel),
		                                                                                                useRotation(rotation) {
		}

		void OrthographicCameraController::onUpdate(ge::core::Timestep ts) {
			GE_ProfileFunction();

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
			GE_ProfileFunction();

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

		/*********************************
		 * Perspective Camera Controller *
		 *********************************/

		PerspectiveCameraController::PerspectiveCameraController(float32 aspectRatio, float32 fov): camera(aspectRatio, fov) {
		}

		void PerspectiveCameraController::onUpdate(ge::core::Timestep ts) {
			GE_ProfileFunction();

			if(Input::isKeyDown(Key::W)) {
				camera.moveForward(ts * translationSpeed);
			} else if(Input::isKeyDown(Key::S)) {
				camera.moveForward(ts * -translationSpeed);
			}

			if(Input::isKeyDown(Key::A)) {
				camera.moveRight(ts * -translationSpeed);
			} else if(Input::isKeyDown(Key::D)) {
				camera.moveRight(ts * translationSpeed);
			}

			if(Input::isKeyDown(Key::Space)) {
				camera.moveUp(ts * translationSpeed);
			} else if(Input::isKeyDown(Key::LeftShift)) {
				camera.moveUp(ts * -translationSpeed);
			}

			camera.update();
		}
		void PerspectiveCameraController::onEvent(ge::core::Event& e) {
			GE_ProfileFunction();

			ge::core::EventDispatcher dispatcher(e);
			dispatcher.dispatch<ge::core::WindowResizeEvent>(GE_BindEventFunction(PerspectiveCameraController::onWindowResize));
			dispatcher.dispatch<ge::core::MouseMovedEvent>(GE_BindEventFunction(PerspectiveCameraController::onMouseMoved));
			dispatcher.dispatch<ge::core::KeyDownEvent>(GE_BindEventFunction(PerspectiveCameraController::onKeyDown));
		}
		bool PerspectiveCameraController::onMouseMoved(ge::core::MouseMovedEvent& e) {
			if(Application::getInstance().getWindow().isCursorGrabbed()) {
				float32 xRel = e.getXRel();
				float32 yRel = e.getYRel();
	
				camera.setYaw(camera.getYaw() + e.getXRel() * rotationSpeed);
				camera.setPitch(camera.getPitch() - e.getYRel() * rotationSpeed);
				camera.updateRotation();
			}

			return false;
		}
		bool PerspectiveCameraController::onWindowResize(ge::core::WindowResizeEvent& e) {
			camera.setPerspective((float32) e.getWidth() / (float32) e.getHeight(), camera.getFov());

			return false;
		}
		bool PerspectiveCameraController::onKeyDown(ge::core::KeyDownEvent& e) {
			if(e.getKeyCode() == Key::Escape) {
				Application::getInstance().getWindow().setCursorGrabbed(!Application::getInstance().getWindow().isCursorGrabbed());
			}

			return false;
		}
	}
}
