#ifndef QED_H
#define QED_H


// Application
#include "Core/Application/Application.h"

// Log
#include "Core/Log/Log.h"

// Type
#include "Core/Type/Type.h"

// Time
#include "Core/Time/TimeStep.h"

// TODO: find out why cant include these
// Globals
//#include "Core/Registry/Registry.h"
//#include "Core/Globals.h"

// Input
#include "Input/CoreInput.h"
#include "Input/Keycodes.h"

//TODO: remove
#include "Event/ApplicationEvent.h"
#include "UI/ImGuiLayer.h"
#include <imgui.h>
#include "UI/ImGuiLayer.h"

// Module interfaces
#include "Module/Interfaces/ModuleInterface.h"


// Graphics
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Renderer/RenderCommand.h"
#include "Graphics/Renderer/Renderer2D.h"

#include "Graphics/Interface/Buffers/VertexBuffer.h"
#include "Graphics/Interface/Buffers/IndexBuffer.h"
#include "Graphics/Interface/Buffers/VertexArray.h"
#include "Graphics/Interface/Shaders/Shader.h"
#include "Graphics/Interface/Shaders/ShaderLibrary.h"
#include "Graphics/Interface/Textures/Texture2D.h"

#include "Graphics/Camera/OrthographicCamera.h"
#include "Graphics/Camera/OrthographicCameraController.h"
#include "Graphics/Camera/OrthographicCameraControllerInterface.h"

// Profiler
#include "Profiler/Instrumentor.h"

#endif // !QED_H
