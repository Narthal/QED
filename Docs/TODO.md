# TODO

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
- [ ] remove external tools unneccessary docs & files
- [x] vertex buffer abstraction
- [x] index buffer abstraction
- [x] shader abstraction
- [x] vertex buffer layout abstraction
- [x] vertex array abstraction
- [ ] maintenance : unify accessors
- [ ] maintenace : delete / create constructors
- [ ] utility : abort function
- [ ] utility : assert function
- [ ] utility : stack trace (through return macro)
- [ ] move : input dir to event
- [ ] rename : coreinput to input
- [ ] create QED Commons lib that statically links to the engine and the client application (log, QED globals, memory allocator for both exe and each dll, etc)
- [ ] separate shader functionality to separate preprocessor file
- [ ] maintenance : make include paths absolute from project root

## Have no idea
- [ ] glfw vsync disable is absolute dogshit

## Engine sanity
- [ ] Visual Studio memory check integration
- [ ] Valgrind integration

## Build Tool
- [ ] Add c++ standard
- [ ] Static std library switch
- [ ] std library debug switch
- [ ] Conditionals
- [ ] Defines
- [ ] Links (to other projects too)
- [ ] Default values config file (JSON / XML)
- [ ] Hook up pre/post build events
- [ ] Write first Build Tool extension : build increment header generator
- [ ] Complete migration from premake to BT
- [ ] Make file generator for linux builds
- [ ] ?Premake fallback/generator?
- [ ] cmake wrapper project (command line settings generator)


