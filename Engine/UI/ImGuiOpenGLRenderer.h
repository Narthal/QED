#pragma once

#include "imgui.h"

// Backend API
IMGUI_IMPL_API bool     ImGui_ImplOpenGL3_Init(const char* glsl_version = NULL);
IMGUI_IMPL_API void     ImGui_ImplOpenGL3_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplOpenGL3_NewFrame();
IMGUI_IMPL_API void     ImGui_ImplOpenGL3_RenderDrawData(ImDrawData* draw_data);

// (Optional) Called by Init/NewFrame/Shutdown
IMGUI_IMPL_API bool     ImGui_ImplOpenGL3_CreateFontsTexture();
IMGUI_IMPL_API void     ImGui_ImplOpenGL3_DestroyFontsTexture();
IMGUI_IMPL_API bool     ImGui_ImplOpenGL3_CreateDeviceObjects();
IMGUI_IMPL_API void     ImGui_ImplOpenGL3_DestroyDeviceObjects();

// Specific OpenGL versions
//#define IMGUI_IMPL_OPENGL_ES2     // Auto-detected on Emscripten
//#define IMGUI_IMPL_OPENGL_ES3     // Auto-detected on iOS/Android

// Desktop OpenGL: attempt to detect default GL loader based on available header files.
// If auto-detection fails or doesn't select the same GL loader file as used by your application,
// you are likely to get a crash in ImGui_ImplOpenGL3_Init().
// You can explicitly select a loader by using '#define IMGUI_IMPL_OPENGL_LOADER_XXX' in imconfig.h or compiler command-line.
//#if !defined(IMGUI_IMPL_OPENGL_LOADER_GL3W) \
// && !defined(IMGUI_IMPL_OPENGL_LOADER_GLEW) \
// && !defined(IMGUI_IMPL_OPENGL_LOADER_GLAD) \
// && !defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING) \
// && !defined(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)
//    #if defined(__has_include)
//        #if __has_include(<GL/glew.h>)
//            #define IMGUI_IMPL_OPENGL_LOADER_GLEW
//        #elif __has_include(<glad/glad.h>)
//            #define IMGUI_IMPL_OPENGL_LOADER_GLAD
//        #elif __has_include(<GL/gl3w.h>)
//            #define IMGUI_IMPL_OPENGL_LOADER_GL3W
//        #elif __has_include(<glbinding/gl/gl.h>)
//            #define IMGUI_IMPL_OPENGL_LOADER_GLBINDING
//        #else
//            #error "Cannot detect OpenGL loader!"
//        #endif
//    #else
//        #define IMGUI_IMPL_OPENGL_LOADER_GL3W       // Default to GL3W
//    #endif
//#endif

