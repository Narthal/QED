# TODO
- [x] common directory
- [x] rework precompiled headers and underlying structure
- [x] unify upper case directories
- [ ] reimplement shitty entry point hijack mechanism
- [x] somehow tell cmake to use /MT & /MTd for GLFW generation
- [ ] implement basic sqlite database wrapper class
- [ ] implement sandboxed filesystem (PhysicalFileSystem)


## Projects
- engine (+server)
- common
- modules
  - openGLModule
  - pythonScriptingModule
- client
- utility
- launcher

- ?steam workshop integration?
- ?news webpage host?
- ?authentication server?


# GOALS
## engine
- [x] log
- [x] registry
- [x] client - engine setup
- [ ] sqlite
- [ ] virtual file system	-many many loaders (?loaderAPI?)
- [ ] moduleFramework		-DescriptorAPI	-ScriptingAPI	-RendererAPI
- [ ] event system
- [ ] window abstraction
- [ ] input events
- [ ] ?layers?
- [ ] imgui
- [ ] camera
- [ ] allocator
- [ ] thread pool
- [ ] ecs
- [ ] imgui debug tools
- [ ] profilers
- [ ] box2D
- [ ] chanels (arbitrary)
- [ ] sound
- [ ] headless server mode
- [ ] networking - p2p server, server only, cooperative servers

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
- [ ] bat. scripts to be replaced with this
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



