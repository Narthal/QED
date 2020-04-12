# TODO

## Priority list
- [x] replace premake with build tool
- [ ] log.h redo
- [ ] generate build log file from vs
- [ ] store build log in sqlite

## Projects
- [x] [c++] Engine as exe & static lib
- [x] [c++] Client (sandbox) as dynamic lib
- [ ] [c++] Client (game core) as dynamic lib
- [ ] [c++] Common as static lib
- [ ] [c#] AssetPipelineTool as dynamic lib
- [ ] [c#] BuildTool as dynamic lib
- [ ] [c#] ConductorTool as exe
- [ ] [c#] ReflectionTool as dll
- [ ] [c#] ConfigTool as dll

## General
- [x] finish imgui docking
- [x] fixup github imgui submodule not pointing to correct branch (maybe re add the submodule)
- [ ] remove visual studio region pch include
- [ ] merge coreWindow and glfwWindow, remove support for multiple window creation
- [x] remove external tools unneccessary docs & files
- [x] vertex buffer abstraction
- [x] index buffer abstraction
- [x] shader abstraction
- [x] vertex buffer layout abstraction
- [x] vertex array abstraction
- [ ] maintenance : unify accessors
- [ ] utility : abort function
- [x] utility : assert function
- [ ] utility : stack trace (through return macro)
- [ ] rename : coreinput to input
- [ ] create QED Commons lib that statically links to the engine and the client application (log, QED globals, memory allocator for both exe and each dll, etc)
- [x] separate shader functionality to separate preprocessor file
- [ ] maintenance : make include paths absolute from project root
- [ ] maintenance : rework layer and moduleInterface relation (new module interface for it, new push layer / overlay function exposition)

## Have no idea
- [ ] glfw vsync disable is absolute dogshit

## Engine sanity
- [ ] Visual Studio memory check integration
- [ ] Valgrind integration

## Build Tool
- [x] precompiled heaers
- [x] preprocessor defs
- [x] sort conditionals to filters
- [ ] Generate .filters file for visual studio solution


