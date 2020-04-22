#ifndef QED_H
#define QED_H


// Core
#include "Core/Application/ApplicationInterface.h"
#include "Core/Log/Log.h"
#include "Core/Type/Type.h"
#include "Core/Time/TimeStep.h"

// Module interfaces
#include "Module/Interfaces/ModuleInterface.h"
#include "Module/Module.h"

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




// Graphics
//#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Renderer/RenderCommandInterface.h"
#include "Graphics/Renderer/Renderer2D.h"

#include "Graphics/Interface/Textures/Texture2D.h"

#include "Graphics/Camera/OrthographicCameraControllerInterface.h"

// Profiler
#include "Profiler/Instrumentor.h"

#endif // !QED_H
