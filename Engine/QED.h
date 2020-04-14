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
#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"
#include "Graphics/Renderer2D.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/Shader.h"
#include "Graphics/ShaderLibrary.h"
#include "Graphics/Texture2D.h"
#include "Graphics/VertexArray.h"

#include "Graphics/OrthographicCamera.h"
#include "Graphics/OrthographicCameraController.h"

// Profiler
#include "Profiler/Timer/Timer.h"

#endif // !QED_H
