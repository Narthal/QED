# TODO

## TODO Today
- [ ] convert to cmake


## Priority list
### Build system
- [ ] make conductor - cmake integration
- [ ] create CodeGeneration & Database directories, redirect glad codegen to new dir

### Static reflection and codeGen
- [ ] conductor - libclang binding
- [ ] custom attribute in libclang
- [ ] store AST in serialized file
- [ ] conductor codegen based on serialized AST
- [ ] expose conductor codegen to cmake

### Refactor / Remove dependancy
- [ ] rewrite logger, remove spdlog as dependancy
- [ ] rewrite profiler
- [ ] connect logger & profiler to sqlite

### Addition
- [ ] custom allocator

## Goal dependancies
- render to frame buffer object (FBO)
  - Render FBO in imgui viewport
    - Set up imgui dockspace
  - Introduce tests
- SQLite integration
  - Rewrite asset loading and caching
  - Rewrite profiler and logger
- Allocator
  - Basic ECS
    - Basic scripting
    - Threading
  - Custom imgui allocator (give allocation functions to imgui (imgui has wrapper function))
  - Custom cPython allocator

## General
- [ ] utility : abort function
- [ ] utility : stack trace (through return macro)
- [ ] rename : coreinput to input
- [ ] rework : rework layer and moduleInterface relation (new module interface for it, new push layer / overlay function exposition)
- [ ] maintenace : find out wtf is wrong with includeing globals and registry in QED.h
- [ ] maintenace : set imgui math tipes to use new math types
- [ ] maintenace : corewindow create function similar to rendererAPI
- [ ] maintenance : fixup #include <instrumentor> to "instrumentor"
- [ ] profiler : rewrite with log (collectors and sinks, writers)
- [ ] QOL : make quadProperties struct and move most of the drawQuad args to there
- [ ] maintenace : rewrite drawQuad function to be a templated function reducing overloads
- [ ] maintenace : create core graphics folder and move all classes that are base classes to there
- [ ] feature : shader hot reload
- [ ] feature : shader fallback system
- [ ] feature : high level shader language that cross compiles to glsl
- [ ] QOL : create ref equals function (needed in drawQuad for instance)
- [ ] rewrite : replace uint32 to int32 in setInt and setIntArray
- [ ] feature : render queue to sort all draw calls by z order, draw back to front so alpha blending works
- [ ] rewrite renderer to give it some purpose
- [ ] buildTool : environmental variable option, work dir option for buildTool
  
## Have no idea
- [ ] glfw vsync disable is absolute dogshit


