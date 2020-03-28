
--TODO: make tables for common include dirs (imgui, glm, etc)












-- root
workspace "QED"

	files
	{
		"premake5.lua",
	}

---------------------------------------------------------------------
	
	-- PLATFORM
	-- TODO: maybe x86
	architecture "x64"

---------------------------------------------------------------------

	-- CONFIGURATION
	-- confiurations: 
	--		debug : debugging
	--		release : no debugging, verbose logging
	--		distribution : quiet logging
	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

---------------------------------------------------------------------


	-- VARIABLES

-- build directories
buildDir = "Build/"
intermediateDir = ("Intermediate/")
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"

-- base structure directories
common = "Common"
external = "External"
dependancies = external .. "/" .. "Vendor"

-- dependancy directory names
GLFWDir = dependancies .. "/" .. "GLFW"
GLFWInclude = GLFWDir .. "/" .. "include"
GLADDir = dependancies .. "/" .. "GLAD"
GLADInclude = GLADDir .. "/" .. "include"
ImGuiDir = dependancies .. "/" .. "ImGui"
GLMDir = dependancies .. "/" .. "GLM"
STBDir = dependancies .. "/" .. "stb"

-- project names
engineProjectName = "Engine"
sandboxProjectName = "Sandbox"

-- automation project names
ReloadSubmodules = "RELOAD_SUBMODULES"
RebuildSolution = "BUILD_SOLUTION"
GLFWBuildAutomation = "BUILD_GLFW"
GLADBuildAutomation = "BUILD_GLAD"
ImGuiBuildAutomation = "BUILD_IMGUI"

-- automation directory
automationDir = "Automation"
automationTools = "Tools"
dependecyProjects = "DependencyProjects"

-- automation tools
ReloadSubmodulesLocation = automationDir .. "/" ..ReloadSubmodules
RebuildSolutionLocation = automationDir .. "/" .. RebuildSolution

-- automation dependancy projects
GLFWBuildAutomationLocation = automationDir .. "/" .. GLFWBuildAutomation
GLADBuildAutomationLocation = automationDir .. "/" .. GLADBuildAutomation
ImGuiBuildAutomationLocation = automationDir .. "/" .. ImGuiBuildAutomation

-- dependecy projects
GLFWBuildDir = buildDir .. "GLFW"
GLFWLib = GLFWBuildDir .. "/src/Debug/" .. "glfw3.lib"
GLADBuildDir = buildDir .. "GLAD"
GLADObjDir = GLADBuildDir .. "/" .. intermediateDir
GLADLib = GLADBuildDir .. "/" .. "glad.lib"
ImGuiBuildDir = buildDir .. "ImGui"
ImGuiObjDir = ImGuiBuildDir .. "/" .. intermediateDir
ImGuiLib = ImGuiBuildDir .. "/" .. "imgui.lib"

-- pch
pchDirectory = "PCH"
pchName = "PCH"
pchHeaderFile = pchName .. ".h"
pchSourceFile = pchName .. ".cpp"

-- os data
osVersion = os.getversion().majorversion .. ' ' .. os.getversion().minorversion .. ' ' .. os.getversion().revision .. ' ' .. os.getversion().description

-- Set startup project
	startproject(sandboxProjectName)

---------------------------------------------------------------------

	-- AUTOMATION UTILITY TOOLS

group(automationDir .. "/" .. automationTools)

	project(RebuildSolution)
	
		location(RebuildSolutionLocation)
		kind "Utility"

		filter "system:windows"
			prebuildcommands
			{
				"../Scripts/rebuildSolution.bat"
			}

			postbuildcommands
			{
				"../Scripts/clean.bat"
			}

	project(ReloadSubmodules)

		location(ReloadSubmodulesLocation)
		kind "Utility"

		filter "system:windows"
			prebuildcommands
			{
				"../Scripts/clean.bat"
			}

			postbuildcommands
			{
				"../Scripts/reloadSubmodules.bat"
			}
group ""

group(automationDir .. "/" .. dependecyProjects)

	project(GLFWBuildAutomation)

		location(GLFWBuildAutomationLocation)
		kind "Utility"

		filter "system:windows"
			prebuildcommands
			{
				"../Scripts/rebuildGLFW.bat;"
			}

	project (GLADBuildAutomation)

		location(GLADBuildAutomationLocation)
		kind "StaticLib"
		language "C++"
		staticruntime "off"

		targetdir(GLADBuildDir)
		objdir(GLADObjDir)
		
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"

		targetname("glad")

		files
		{
			GLADDir .. "/**.h",
			GLADDir .. "/**.c",
		}

		includedirs
		{
			GLADInclude
		}

		filter "configurations:Debug"
			symbols "On"
			runtime "Debug"

		filter "configurations:Release"
			optimize "On"
			runtime "Release"

		filter "configurations:Distribution"
			optimize "On"

	project (ImGuiBuildAutomation)

		location(ImGuiBuildAutomationLocation)
		kind "StaticLib"
		language "C++"
		staticruntime "off"

		targetdir(ImGuiBuildDir)
		objdir(ImGuiObjDir)

		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"

		targetname("imgui")

		-- NOTE: do not recursively include files, as the files deeper are test, examples, etc
		files
		{
			ImGuiDir .. "/*.h",
			ImGuiDir .. "/*.cpp",
		}

		includedirs
		{
			ImGuiDir
		}

		defines
		{
			"IMGUI_API=__declspec(dllexport)"
		}

		filter "configurations:Debug"
			symbols "On"
			runtime "Debug"

		filter "configurations:Release"
			optimize "On"
			runtime "Release"

		filter "configurations:Distribution"
			optimize "On"


group ""

---------------------------------------------------------------------

	-- ENGINE

project(engineProjectName)
	
	location(engineProjectName)
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	systemversion "latest"

	targetdir(buildDir .. engineProjectName.. "/" .. outputDir)
	objdir(buildDir .. engineProjectName.. "/" .. outputDir .. "/" .. intermediateDir)

	pchheader(engineProjectName .. pchHeaderFile)
	pchsource(engineProjectName .. "/" .. pchDirectory .. "/" .. engineProjectName .. pchSourceFile)

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		common,										-- common directory
		engineProjectName .. "/" .. pchDirectory,	-- local PCH directory
		GLFWInclude,								-- GLFW include directory
		GLADInclude,								-- GLAD include
		ImGuiDir,									-- ImGui include (no such dir, just ImGui root)
		GLMDir,										-- GLM headers
		STBDir,										-- stb
	}

	links
	{
		"opengl32.lib",			-- OpenGL
		GLFWBuildAutomation,	-- GLFW automation
		GLFWLib,				-- glfw3.lib
		GLADBuildAutomation,	-- GLAD automation
		GLADLib,				-- glad.lib
		ImGuiBuildAutomation,	-- ImGui automation
		ImGuiLib,				-- imgui.lib
	}

	filter "system:Windows"

		defines
		{
			"MAKE_ENGINE",									-- QED API
			"QED_WINDOWS",						-- windows build
			"BUILD_OS=" .. '"' .. osVersion .. '"',		-- os details
			"GLFW_INCLUDE_NONE",						-- GLAD already includes OpenGL
		}

		postbuildcommands
		{
			"{MKDIR} " .. "../" .. buildDir .. sandboxProjectName .. "/" .. outputDir,
			"{COPY} %{cfg.buildtarget.relpath} " ..  "../" .. buildDir .. sandboxProjectName .. "/" .. outputDir,
		}

	filter "configurations:Debug"
		defines { "QED_ENGINE_DEBUG", "DEBUG" }
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines { "QED_ENGINE_RELEASE" }
		optimize "On"
		runtime "Release"

	filter "configurations:Distribution"
		defines { "QED_ENGINE_DISTRIBUTION" }
		optimize "On"

	
	filter { "system:windows" }
		buildoptions
		{
			"/sdl-",
		}


---------------------------------------------------------------------

	-- sandbox

project(sandboxProjectName)
	
	location(sandboxProjectName)
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	systemversion "latest"

	targetdir(buildDir .. sandboxProjectName .. "/" .. outputDir)
	objdir(buildDir .. sandboxProjectName .. "/" .. outputDir .. "/" .. intermediateDir)

	pchheader(sandboxProjectName .. pchHeaderFile)
	pchsource(sandboxProjectName .. "/" .. pchDirectory .. "/" .. sandboxProjectName .. pchSourceFile)

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

		
	includedirs
	{
		common,										-- common directory
		sandboxProjectName .. "/" .. pchDirectory,	-- local PCH directory

		engineProjectName .. "/**",					-- the Engine

		ImGuiDir,									-- ImGui include (no such dir, just ImGui root)
		GLMDir,										-- GLM headers
	}

	links
	{
		engineProjectName,
		buildDir .. engineProjectName.. "/" .. outputDir .. "/Engine.lib"
	}


	filter "system:Windows"

		defines
		{
			"MAKE_MODULE",									-- QED API
			"QED_WINDOWS"
		}

	filter "configurations:Debug"
		defines { "QED_SANDBOX_DEBUG", "DEBUG" }
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines { "QED_SANDBOX_RELEASE" }
		optimize "On"
		runtime "Release"

	filter "configurations:Distribution"
		defines { "QED_SANDBOX_DISTRIBUTION" }
		optimize "On"

	
	filter { "system:windows" }
		buildoptions
		{
			"/sdl-",
		}