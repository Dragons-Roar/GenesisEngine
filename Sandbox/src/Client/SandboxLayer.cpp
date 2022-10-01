#include "SandboxLayer.hpp"
#include <GenesisClientCore/Genesis.hpp>
#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

namespace sb {
	void SandboxLayer::onAttach() {
	}
	void SandboxLayer::onDetach() {
		GE_Info("Sandbox Layer has been detached!");
	}
	void SandboxLayer::onUpdate(ge::core::Timestep ts) {
		glBegin(GL_LINES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(1.f, 0.f, 0.f);
		
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.f, 1.f, 0.f);
		
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.f, 1.f);
		glEnd();
	}
	void SandboxLayer::onImGUIRender() {
	}

	void SandboxLayer::onEvent(ge::core::Event& e) {
		camera.onEvent(e);
	}
}
