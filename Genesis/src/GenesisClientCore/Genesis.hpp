#pragma once
// For use in Genesis Applications

#include <GenesisCore/Genesis.hpp>

#include "GenesisClientCore/Window.hpp"
#include "GenesisClientCore/Application.hpp"
#include "GenesisClientCore/Application.hpp"
#include "GenesisClientCore/Input.hpp"
#include "GenesisClientCore/Window.hpp"
#include "GenesisClientCore/CameraController.hpp"

// --- Renderer -------------------------------------------
#include "GenesisClientCore/renderer/Buffer.hpp"
#include "GenesisClientCore/renderer/Camera.hpp"
#include "GenesisClientCore/renderer/RenderCommand.hpp"
#include "GenesisClientCore/renderer/Renderer.hpp"
#include "GenesisClientCore/renderer/Shader.hpp"
#include "GenesisClientCore/renderer/VertexArray.hpp"
#include "GenesisClientCore/renderer/Texture.hpp"

// --- Platform Specifc -----------------------------------
#ifdef GE_WINDOWS
#	include "GenesisClientCore/platform/windows/WindowsWindow.hpp"
#endif
