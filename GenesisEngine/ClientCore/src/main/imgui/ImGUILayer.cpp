#include <GenesisClientCore/imgui/ImGUILayer.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GenesisClientCore/Application.hpp>
#include <glad/glad.h>

#define GE_GetImGuiIO() ImGuiIO& io = ImGui::GetIO();

namespace ge {
	namespace clientcore {
		void ImGUILayer::onAttach() {
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			GE_GetImGuiIO(); (void) io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

			io.KeyMap[ImGuiKey_Space] = ge::Key::Space;
			io.KeyMap[ImGuiKey_Apostrophe] = ge::Key::Apostrophe;
			io.KeyMap[ImGuiKey_Comma] = ge::Key::Comma;
			io.KeyMap[ImGuiKey_Minus] = ge::Key::Minus;
			io.KeyMap[ImGuiKey_Period] = ge::Key::Period;
			io.KeyMap[ImGuiKey_Slash] = ge::Key::Slash;

			io.KeyMap[ImGuiKey_0] = ge::Key::D0;
			io.KeyMap[ImGuiKey_1] = ge::Key::D1;
			io.KeyMap[ImGuiKey_2] = ge::Key::D2;
			io.KeyMap[ImGuiKey_3] = ge::Key::D3;
			io.KeyMap[ImGuiKey_4] = ge::Key::D4;
			io.KeyMap[ImGuiKey_5] = ge::Key::D5;
			io.KeyMap[ImGuiKey_6] = ge::Key::D6;
			io.KeyMap[ImGuiKey_7] = ge::Key::D7;
			io.KeyMap[ImGuiKey_8] = ge::Key::D8;
			io.KeyMap[ImGuiKey_9] = ge::Key::D9;

			io.KeyMap[ImGuiKey_Semicolon] = ge::Key::Semicolon;
			io.KeyMap[ImGuiKey_Equal] = ge::Key::Equal;

			io.KeyMap[ImGuiKey_A] = ge::Key::A;
			io.KeyMap[ImGuiKey_B] = ge::Key::B;
			io.KeyMap[ImGuiKey_C] = ge::Key::C;
			io.KeyMap[ImGuiKey_D] = ge::Key::D;
			io.KeyMap[ImGuiKey_E] = ge::Key::E;
			io.KeyMap[ImGuiKey_F] = ge::Key::F;
			io.KeyMap[ImGuiKey_G] = ge::Key::G;
			io.KeyMap[ImGuiKey_H] = ge::Key::H;
			io.KeyMap[ImGuiKey_I] = ge::Key::I;
			io.KeyMap[ImGuiKey_J] = ge::Key::J;
			io.KeyMap[ImGuiKey_K] = ge::Key::K;
			io.KeyMap[ImGuiKey_L] = ge::Key::L;
			io.KeyMap[ImGuiKey_M] = ge::Key::M;
			io.KeyMap[ImGuiKey_N] = ge::Key::N;
			io.KeyMap[ImGuiKey_O] = ge::Key::O;
			io.KeyMap[ImGuiKey_P] = ge::Key::P;
			io.KeyMap[ImGuiKey_Q] = ge::Key::Q;
			io.KeyMap[ImGuiKey_R] = ge::Key::R;
			io.KeyMap[ImGuiKey_S] = ge::Key::S;
			io.KeyMap[ImGuiKey_T] = ge::Key::T;
			io.KeyMap[ImGuiKey_U] = ge::Key::U;
			io.KeyMap[ImGuiKey_V] = ge::Key::V;
			io.KeyMap[ImGuiKey_W] = ge::Key::W;
			io.KeyMap[ImGuiKey_X] = ge::Key::X;
			io.KeyMap[ImGuiKey_Y] = ge::Key::Y;
			io.KeyMap[ImGuiKey_Z] = ge::Key::Z;

			io.KeyMap[ImGuiKey_LeftBracket] = ge::Key::LeftBracket;
			io.KeyMap[ImGuiKey_Backslash] = ge::Key::Backslash;
			io.KeyMap[ImGuiKey_RightBracket] = ge::Key::RightBracket;
			io.KeyMap[ImGuiKey_GraveAccent] = ge::Key::GraveAccent;

			io.KeyMap[ImGuiKey_Escape] = ge::Key::Escape;
			io.KeyMap[ImGuiKey_Enter] = ge::Key::Enter;
			io.KeyMap[ImGuiKey_Backspace] = ge::Key::Backspace;
			io.KeyMap[ImGuiKey_Insert] = ge::Key::Insert;
			io.KeyMap[ImGuiKey_Delete] = ge::Key::Delete;
			io.KeyMap[ImGuiKey_RightArrow] = ge::Key::Right;
			io.KeyMap[ImGuiKey_LeftArrow] = ge::Key::Left;
			io.KeyMap[ImGuiKey_DownArrow] = ge::Key::Down;
			io.KeyMap[ImGuiKey_UpArrow] = ge::Key::Up;
			io.KeyMap[ImGuiKey_PageUp] = ge::Key::PageUp;
			io.KeyMap[ImGuiKey_PageDown] = ge::Key::PageDown;
			io.KeyMap[ImGuiKey_Home] = ge::Key::Home;
			io.KeyMap[ImGuiKey_End] = ge::Key::End;
			io.KeyMap[ImGuiKey_CapsLock] = ge::Key::CapsLock;
			io.KeyMap[ImGuiKey_ScrollLock] = ge::Key::ScrollLock;
			io.KeyMap[ImGuiKey_NumLock] = ge::Key::NumLock;
			io.KeyMap[ImGuiKey_PrintScreen] = ge::Key::PrintScreen;
			io.KeyMap[ImGuiKey_Pause] = ge::Key::Pause;

			io.KeyMap[ImGuiKey_F1] = ge::Key::F1;
			io.KeyMap[ImGuiKey_F2] = ge::Key::F2;
			io.KeyMap[ImGuiKey_F3] = ge::Key::F3;
			io.KeyMap[ImGuiKey_F4] = ge::Key::F4;
			io.KeyMap[ImGuiKey_F5] = ge::Key::F5;
			io.KeyMap[ImGuiKey_F6] = ge::Key::F6;
			io.KeyMap[ImGuiKey_F7] = ge::Key::F7;
			io.KeyMap[ImGuiKey_F8] = ge::Key::F8;
			io.KeyMap[ImGuiKey_F9] = ge::Key::F9;
			io.KeyMap[ImGuiKey_F10] = ge::Key::F10;
			io.KeyMap[ImGuiKey_F11] = ge::Key::F11;
			io.KeyMap[ImGuiKey_F12] = ge::Key::F12;

			io.KeyMap[ImGuiKey_Keypad0] = ge::Key::KP0;
			io.KeyMap[ImGuiKey_Keypad1] = ge::Key::KP1;
			io.KeyMap[ImGuiKey_Keypad2] = ge::Key::KP2;
			io.KeyMap[ImGuiKey_Keypad3] = ge::Key::KP3;
			io.KeyMap[ImGuiKey_Keypad4] = ge::Key::KP4;
			io.KeyMap[ImGuiKey_Keypad5] = ge::Key::KP5;
			io.KeyMap[ImGuiKey_Keypad6] = ge::Key::KP6;
			io.KeyMap[ImGuiKey_Keypad7] = ge::Key::KP7;
			io.KeyMap[ImGuiKey_Keypad8] = ge::Key::KP8;
			io.KeyMap[ImGuiKey_Keypad9] = ge::Key::KP9;

			io.KeyMap[ImGuiKey_KeypadDecimal] = ge::Key::KPDecimal;
			io.KeyMap[ImGuiKey_KeypadDivide] = ge::Key::KPDivide;
			io.KeyMap[ImGuiKey_KeypadMultiply] = ge::Key::KPMultiply;
			io.KeyMap[ImGuiKey_KeypadSubtract] = ge::Key::KPSubtract;
			io.KeyMap[ImGuiKey_KeypadAdd] = ge::Key::KPAdd;
			io.KeyMap[ImGuiKey_KeypadEnter] = ge::Key::KPEnter;
			io.KeyMap[ImGuiKey_KeypadEqual] = ge::Key::KPEqual;

			io.KeyMap[ImGuiKey_LeftShift] = ge::Key::LeftShift;
			io.KeyMap[ImGuiKey_LeftCtrl] = ge::Key::LeftControl;
			io.KeyMap[ImGuiKey_LeftAlt] = ge::Key::LeftAlt;
			io.KeyMap[ImGuiKey_LeftSuper] = ge::Key::LeftSuper;
			io.KeyMap[ImGuiKey_RightShift] = ge::Key::RightShift;
			io.KeyMap[ImGuiKey_RightCtrl] = ge::Key::RightControl;
			io.KeyMap[ImGuiKey_RightAlt] = ge::Key::RightAlt;
			io.KeyMap[ImGuiKey_RightSuper] = ge::Key::RightSuper;
			io.KeyMap[ImGuiKey_Menu] = ge::Key::Menu;

			float32 fontSize = 24.f; // *2
			io.Fonts->AddFontFromFileTTF("assets/font/roboto/Roboto-Bold.ttf", fontSize);
			io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/font/roboto/Roboto-Regular.ttf", fontSize);

			ImGui::StyleColorsDark();
			ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(ge::clientcore::Application::getInstance().getWindow().getNativeWindow()), false);
			ImGui_ImplOpenGL3_Init("#version 410");
		}
		void ImGUILayer::onDetach() {
		}
		void ImGUILayer::onUpdate() {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			bool showDemoWindow = true;
			ImGui::ShowDemoWindow(&showDemoWindow);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		void ImGUILayer::onEvent(ge::core::Event& e) {
			ge::core::EventDispatcher dispatcher(e);
			dispatcher.dispatch<ge::core::MouseButtonDownEvent>(GE_BindEventFunction(ImGUILayer::onMouseButtonDownEvent));
			dispatcher.dispatch<ge::core::MouseButtonUpEvent>(GE_BindEventFunction(ImGUILayer::onMouseButtonUpEvent));
			dispatcher.dispatch<ge::core::MouseMovedEvent>(GE_BindEventFunction(ImGUILayer::onMouseMovedEvent));
			dispatcher.dispatch<ge::core::MouseScrolledEvent>(GE_BindEventFunction(ImGUILayer::onMouseScrolledEvent));
			dispatcher.dispatch<ge::core::KeyDownEvent>(GE_BindEventFunction(ImGUILayer::onKeyDownEvent));
			dispatcher.dispatch<ge::core::KeyUpEvent>(GE_BindEventFunction(ImGUILayer::onKeyUpEvent));
			dispatcher.dispatch<ge::core::KeyTypedEvent>(GE_BindEventFunction(ImGUILayer::onKeyTypedEvent));
			dispatcher.dispatch<ge::core::WindowResizeEvent>(GE_BindEventFunction(ImGUILayer::onWindowResizeEvent));
		}

		bool ImGUILayer::onMouseButtonDownEvent(ge::core::MouseButtonDownEvent& e) {
			GE_GetImGuiIO();
			io.MouseDown[e.getButton()] = true;

			return false;
		}
		bool ImGUILayer::onMouseButtonUpEvent(ge::core::MouseButtonUpEvent& e) {
			GE_GetImGuiIO();
			io.MouseDown[e.getButton()] = false;

			return false;
		}
		bool ImGUILayer::onMouseMovedEvent(ge::core::MouseMovedEvent& e) {
			GE_GetImGuiIO();
			io.MousePos = ImVec2(e.getX(), e.getY());

			return false;
		}
		bool ImGUILayer::onMouseScrolledEvent(ge::core::MouseScrolledEvent& e) {
			GE_GetImGuiIO();
			io.MouseWheel += e.getY();
			io.MouseWheelH += e.getX();

			return false;
		}
		bool ImGUILayer::onKeyDownEvent(ge::core::KeyDownEvent& e) {
			GE_GetImGuiIO()
			io.KeysDown[e.getKeyCode()] = true;
			io.KeyCtrl = io.KeysDown[ge::Key::LeftControl] || io.KeysDown[ge::Key::RightControl];
			io.KeyShift = io.KeysDown[ge::Key::LeftShift] || io.KeysDown[ge::Key::RightShift];
			io.KeyAlt = io.KeysDown[ge::Key::LeftAlt] || io.KeysDown[ge::Key::RightAlt];
			io.KeySuper = io.KeysDown[ge::Key::LeftSuper] || io.KeysDown[ge::Key::RightSuper];

			return false;
		}
		bool ImGUILayer::onKeyUpEvent(ge::core::KeyUpEvent& e) {
			GE_GetImGuiIO();
			io.KeysDown[e.getKeyCode()] = false;

			return false;
		}
		bool ImGUILayer::onKeyTypedEvent(ge::core::KeyTypedEvent& e) {
			GE_GetImGuiIO();
			int32 keycode = e.getKeyCode();
			if(keycode > 0 && keycode < 0x10000) {
				io.AddInputCharacter((unsigned short) keycode);
			}

			return false;
		}
		bool ImGUILayer::onWindowResizeEvent(ge::core::WindowResizeEvent& e) {
			GE_GetImGuiIO();
			io.DisplaySize = ImVec2(e.getWidth(), e.getHeight());
			io.DisplayFramebufferScale = ImVec2(1.f, 1.f);

			glViewport(0, 0, e.getWidth(), e.getHeight());

			return false;
		}
	}
}
