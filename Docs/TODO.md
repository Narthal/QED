# TODO

## Priority list
- [ ] finish batch renderer
- [ ] create basic sqlite handlers 
- [ ] load textures from sqlite
- [ ] create conductor
- [ ] change buildtool to a dll and connect it with conductor
- [ ] create simple assetPipelineTool
- [ ] custom allocator

## Goal dependancies
- SQLite integration
  - Rewrite asset loading and caching
  - Rewrite profiler and logger
- Allocator
  - Basic ECS
    - Basic scripting
    - Threading
  - Custom imgui allocator (give allocation functions to imgui (imgui has wrapper function))
  - Custom pybind11 allocation (overload new operator with a macro for pybind files)


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
- [ ] remove visual studio region pch include
- [ ] maintenance : unify accessors
- [ ] utility : abort function
- [ ] utility : stack trace (through return macro)
- [ ] rename : coreinput to input
- [ ] rework : rework layer and moduleInterface relation (new module interface for it, new push layer / overlay function exposition)
- [ ] maintenace : find out wtf is wrong with includeing globals and registry in QED.h
- [ ] maintenace : custom math types decl in Types.h, set imgui math tipes to use new types
- [ ] maintenace : corewindow create function similar to rendererAPI
- [ ] maintenance : fixupe #include <instrumentor> to "instrumentor"
- [ ] profiler : rewrite with log (collectors and sinks, writers)
- [ ] QOL : make quadProperties struct and move most of the drawQuad args to there
- [ ] maintenace : rewrite drawQuad function to be a templated function reducing overloads
- [ ] maintenace : create core graphics folder and move all classes that are base classes to there
- [ ] feature : shader hot reload
- [ ] feature : shader fallback system
- [ ] feature : high level shader language that cross compiles to glsl
- [ ] QOL : create ref equals function (needed in drawQuad for instance)
- [ ] rewrite : replace uint32 to int32 in setInt and setIntArray
  
## Have no idea
- [ ] glfw vsync disable is absolute dogshit

## Engine sanity
- [ ] some form of mem check

## Build Tool
- [ ] Generate .filters file for visual studio solution
- [ ] Allow virtual folders in solutions


