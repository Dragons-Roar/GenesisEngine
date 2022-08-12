#pragma once
// For use in Genesis Applications

#include <GenesisCore/Genesis.hpp>

#include "Window.hpp"
#include "Application.hpp"
#include "Application.hpp"
#include "Input.hpp"
#include "Window.hpp"
#include "CameraController.hpp"

// --- Renderer -------------------------------------------
#include "renderer/Buffer.hpp"
#include "renderer/Camera.hpp"
#include "renderer/RenderCommand.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/Shader.hpp"
#include "renderer/VertexArray.hpp"
#include "renderer/Texture.hpp"

// --- Platform Specifc -----------------------------------
#ifdef GE_WINDOWS
#	include "./platform/windows/WindowsWindow.hpp"
#endif
