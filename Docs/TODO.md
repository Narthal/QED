# TODO

- [ ] finish imgui docking
- [ ] fixup github imgui submodule not pointing to correct branch (maybe re add the submodule)

## Projects
- engine (+server)
- common
- modules
  - openGLModule
  - pythonScriptingModule
- client
- utility
- launcher

## premake
- [ ] bat. scripts to be replaced with cross platform commands embedded in premake

# GOALS
## engine
##### Core
- [x] log
- [x] registry
- [x] client - engine setup
- [ ] update registry to have templated static casts & allow multiple types
- [ ] move GLFW to separate project (Window API, Input API)
##### virtual file system	(VFS, PFS)
- [ ] implement basic sqlite database wrapper class
##### Event system
- [x] input events
- [x] layers
- [ ] event queue (asynchronous dispatch queue)
- [ ] thread safe
##### Module framework
- [ ] implement module framework
##### System manager
- [ ] threading
- [ ] thread pool
- [ ] memory allocation
##### UI
- [x] imgui
- [ ] docking imgui
##### Renderer
- [ ] shader class
- [ ] camera
- [ ] module api integration & move to openGLModule
##### ECS
##### Tools
- [ ] imgui debug tools
- [ ] profilers
##### Stuff to integrate
- [ ] box2D
- [ ] sound lib
- [ ] networking lib
##### Stuff to implement
- [ ] headless server mode (layers)

## openGLModule
- [ ] abstraction layer
- [ ] shader abstraction
- [ ] sprite
- [ ] tilemap
- [ ] ambient lighting
- [ ] ?particle system?
- [ ] normals
- [ ] shadows (layered and raytraced)

## utility
- [ ] restart engine
- [ ] cli for management & debug
- [ ] error / crash handler

## client
*** gameplay implementation ***
- [ ] editable tiles
- [ ] game mode	-permission system
- [ ] pawns
- [ ] pathfinder algorithm(top down & sidescroller & ?rocket?)
- [ ] gravity simulation
- [ ] solar system simulation
- [ ] game state save in database
- [ ] tiles with data
- [ ] item storage
- [ ] item moving
- [ ] air simulation
- [ ] liquid simulation
- [ ] computer simulation
- [ ] imgui programming	-GUI	-interpreter
- [ ] dynamic sprites & tiles
- [ ] game events
- [ ] tech tree
- [ ] factions
- [ ] missions
- [ ] game master AI

## launcher
- [ ] cross platform lightweight app
- [ ] update / patch / mod loader
- [ ] html canvas
- [ ] Authenticate



