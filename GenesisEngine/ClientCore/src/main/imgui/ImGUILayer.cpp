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

			io.KeyMap[ImGuiKey_Space] = ge::core::Key::Space;
			io.KeyMap[ImGuiKey_Apostrophe] = ge::core::Key::Apostrophe;
			io.KeyMap[ImGuiKey_Comma] = ge::core::Key::Comma;
			io.KeyMap[ImGuiKey_Minus] = ge::core::Key::Minus;
			io.KeyMap[ImGuiKey_Period] = ge::core::Key::Period;
			io.KeyMap[ImGuiKey_Slash] = ge::core::Key::Slash;

			io.KeyMap[ImGuiKey_0] = ge::core::Key::D0;
			io.KeyMap[ImGuiKey_1] = ge::core::Key::D1;
			io.KeyMap[ImGuiKey_2] = ge::core::Key::D2;
			io.KeyMap[ImGuiKey_3] = ge::core::Key::D3;
			io.KeyMap[ImGuiKey_4] = ge::core::Key::D4;
			io.KeyMap[ImGuiKey_5] = ge::core::Key::D5;
			io.KeyMap[ImGuiKey_6] = ge::core::Key::D6;
			io.KeyMap[ImGuiKey_7] = ge::core::Key::D7;
			io.KeyMap[ImGuiKey_8] = ge::core::Key::D8;
			io.KeyMap[ImGuiKey_9] = ge::core::Key::D9;

			io.KeyMap[ImGuiKey_Semicolon] = ge::core::Key::Semicolon;
			io.KeyMap[ImGuiKey_Equal] = ge::core::Key::Equal;

			io.KeyMap[ImGuiKey_A] = ge::core::Key::A;
			io.KeyMap[ImGuiKey_B] = ge::core::Key::B;
			io.KeyMap[ImGuiKey_C] = ge::core::Key::C;
			io.KeyMap[ImGuiKey_D] = ge::core::Key::D;
			io.KeyMap[ImGuiKey_E] = ge::core::Key::E;
			io.KeyMap[ImGuiKey_F] = ge::core::Key::F;
			io.KeyMap[ImGuiKey_G] = ge::core::Key::G;
			io.KeyMap[ImGuiKey_H] = ge::core::Key::H;
			io.KeyMap[ImGuiKey_I] = ge::core::Key::I;
			io.KeyMap[ImGuiKey_J] = ge::core::Key::J;
			io.KeyMap[ImGuiKey_K] = ge::core::Key::K;
			io.KeyMap[ImGuiKey_L] = ge::core::Key::L;
			io.KeyMap[ImGuiKey_M] = ge::core::Key::M;
			io.KeyMap[ImGuiKey_N] = ge::core::Key::N;
			io.KeyMap[ImGuiKey_O] = ge::core::Key::O;
			io.KeyMap[ImGuiKey_P] = ge::core::Key::P;
			io.KeyMap[ImGuiKey_Q] = ge::core::Key::Q;
			io.KeyMap[ImGuiKey_R] = ge::core::Key::R;
			io.KeyMap[ImGuiKey_S] = ge::core::Key::S;
			io.KeyMap[ImGuiKey_T] = ge::core::Key::T;
			io.KeyMap[ImGuiKey_U] = ge::core::Key::U;
			io.KeyMap[ImGuiKey_V] = ge::core::Key::V;
			io.KeyMap[ImGuiKey_W] = ge::core::Key::W;
			io.KeyMap[ImGuiKey_X] = ge::core::Key::X;
			io.KeyMap[ImGuiKey_Y] = ge::core::Key::Y;
			io.KeyMap[ImGuiKey_Z] = ge::core::Key::Z;

			io.KeyMap[ImGuiKey_LeftBracket] = ge::core::Key::LeftBracket;
			io.KeyMap[ImGuiKey_Backslash] = ge::core::Key::Backslash;
			io.KeyMap[ImGuiKey_RightBracket] = ge::core::Key::RightBracket;
			io.KeyMap[ImGuiKey_GraveAccent] = ge::core::Key::GraveAccent;

			io.KeyMap[ImGuiKey_Escape] = ge::core::Key::Escape;
			io.KeyMap[ImGuiKey_Enter] = ge::core::Key::Enter;
			io.KeyMap[ImGuiKey_Backspace] = ge::core::Key::Backspace;
			io.KeyMap[ImGuiKey_Insert] = ge::core::Key::Insert;
			io.KeyMap[ImGuiKey_Delete] = ge::core::Key::Delete;
			io.KeyMap[ImGuiKey_RightArrow] = ge::core::Key::Right;
			io.KeyMap[ImGuiKey_LeftArrow] = ge::core::Key::Left;
			io.KeyMap[ImGuiKey_DownArrow] = ge::core::Key::Down;
			io.KeyMap[ImGuiKey_UpArrow] = ge::core::Key::Up;
			io.KeyMap[ImGuiKey_PageUp] = ge::core::Key::PageUp;
			io.KeyMap[ImGuiKey_PageDown] = ge::core::Key::PageDown;
			io.KeyMap[ImGuiKey_Home] = ge::core::Key::Home;
			io.KeyMap[ImGuiKey_End] = ge::core::Key::End;
			io.KeyMap[ImGuiKey_CapsLock] = ge::core::Key::CapsLock;
			io.KeyMap[ImGuiKey_ScrollLock] = ge::core::Key::ScrollLock;
			io.KeyMap[ImGuiKey_NumLock] = ge::core::Key::NumLock;
			io.KeyMap[ImGuiKey_PrintScreen] = ge::core::Key::PrintScreen;
			io.KeyMap[ImGuiKey_Pause] = ge::core::Key::Pause;

			io.KeyMap[ImGuiKey_F1] = ge::core::Key::F1;
			io.KeyMap[ImGuiKey_F2] = ge::core::Key::F2;
			io.KeyMap[ImGuiKey_F3] = ge::core::Key::F3;
			io.KeyMap[ImGuiKey_F4] = ge::core::Key::F4;
			io.KeyMap[ImGuiKey_F5] = ge::core::Key::F5;
			io.KeyMap[ImGuiKey_F6] = ge::core::Key::F6;
			io.KeyMap[ImGuiKey_F7] = ge::core::Key::F7;
			io.KeyMap[ImGuiKey_F8] = ge::core::Key::F8;
			io.KeyMap[ImGuiKey_F9] = ge::core::Key::F9;
			io.KeyMap[ImGuiKey_F10] = ge::core::Key::F10;
			io.KeyMap[ImGuiKey_F11] = ge::core::Key::F11;
			io.KeyMap[ImGuiKey_F12] = ge::core::Key::F12;

			io.KeyMap[ImGuiKey_Keypad0] = ge::core::Key::KP0;
			io.KeyMap[ImGuiKey_Keypad1] = ge::core::Key::KP1;
			io.KeyMap[ImGuiKey_Keypad2] = ge::core::Key::KP2;
			io.KeyMap[ImGuiKey_Keypad3] = ge::core::Key::KP3;
			io.KeyMap[ImGuiKey_Keypad4] = ge::core::Key::KP4;
			io.KeyMap[ImGuiKey_Keypad5] = ge::core::Key::KP5;
			io.KeyMap[ImGuiKey_Keypad6] = ge::core::Key::KP6;
			io.KeyMap[ImGuiKey_Keypad7] = ge::core::Key::KP7;
			io.KeyMap[ImGuiKey_Keypad8] = ge::core::Key::KP8;
			io.KeyMap[ImGuiKey_Keypad9] = ge::core::Key::KP9;

			io.KeyMap[ImGuiKey_KeypadDecimal] = ge::core::Key::KPDecimal;
			io.KeyMap[ImGuiKey_KeypadDivide] = ge::core::Key::KPDivide;
			io.KeyMap[ImGuiKey_KeypadMultiply] = ge::core::Key::KPMultiply;
			io.KeyMap[ImGuiKey_KeypadSubtract] = ge::core::Key::KPSubtract;
			io.KeyMap[ImGuiKey_KeypadAdd] = ge::core::Key::KPAdd;
			io.KeyMap[ImGuiKey_KeypadEnter] = ge::core::Key::KPEnter;
			io.KeyMap[ImGuiKey_KeypadEqual] = ge::core::Key::KPEqual;

			io.KeyMap[ImGuiKey_LeftShift] = ge::core::Key::LeftShift;
			io.KeyMap[ImGuiKey_LeftCtrl] = ge::core::Key::LeftControl;
			io.KeyMap[ImGuiKey_LeftAlt] = ge::core::Key::LeftAlt;
			io.KeyMap[ImGuiKey_LeftSuper] = ge::core::Key::LeftSuper;
			io.KeyMap[ImGuiKey_RightShift] = ge::core::Key::RightShift;
			io.KeyMap[ImGuiKey_RightCtrl] = ge::core::Key::RightControl;
			io.KeyMap[ImGuiKey_RightAlt] = ge::core::Key::RightAlt;
			io.KeyMap[ImGuiKey_RightSuper] = ge::core::Key::RightSuper;
			io.KeyMap[ImGuiKey_Menu] = ge::core::Key::Menu;

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
			GE_GetImGuiIO();
			std::cout << "Key: " << e.getKeyCode() << std::endl;
			io.KeysDown[e.getKeyCode()] = true;
			io.KeyCtrl = io.KeysDown[ge::core::Key::LeftControl] || io.KeysDown[ge::core::Key::RightControl];
			io.KeyShift = io.KeysDown[ge::core::Key::LeftShift] || io.KeysDown[ge::core::Key::RightShift];
			io.KeyAlt = io.KeysDown[ge::core::Key::LeftAlt] || io.KeysDown[ge::core::Key::RightAlt];
			io.KeySuper = io.KeysDown[ge::core::Key::LeftSuper] || io.KeysDown[ge::core::Key::RightSuper];

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
