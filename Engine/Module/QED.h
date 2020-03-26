#ifndef QED_H
#define QED_H


// Application
#include "../Core/Application/Application.h"

// Log
#include "../Core/Log/Log.h"

// Type
#include "../Core/Type/Type.h"

// Time
#include "../Core/Time/TimeStep.h"

// Globals
#include "../Core/Registry/Registry.h"
#include "../Core/Globals.h"

// Input
#include "../Input/CoreInput.h"
#include "../Input/Keycodes.h"

//TODO: remove
#include "../Event/ApplicationEvent.h"
#include "../UI/ImGuiLayer.h"

// Module interfaces
#include "ModuleInterface.h"

// UI
#include "imgui.h"
#include "ImGuiLayer.h"

// Graphics
#include "../Graphics/Renderer.h"
#include "../Graphics/RenderCommand.h"

#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/ShaderLibrary.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/VertexArray.h"

#include "../Graphics/OrthographicCamera.h"



#endif // !QED_H
