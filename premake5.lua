
-- root
workspace "QED"


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
dependancies = external .. "/" .. "Dependencies"

-- dependancy directory names
GLFWDir = dependancies .. "/" .. "GLFW"
GLFWInclude = GLFWDir .. "/" .. "include"

-- project names
engineProjectName = "Engine"
sandboxProjectName = "Sandbox"

-- automation project names
GLFWBuildAutomation = "BUILD_GLFW"
ReloadSubmodules = "RELOAD_Submodules"
RebuildSolution = "BUILD_Solution"

-- automation directory
automationDir = "Automation"
GLFWBuildAutomationLocation = automationDir .. "/" .. GLFWBuildAutomation
ReloadSubmodulesLocation = automationDir .. "/" .. ReloadSubmodules
RebuildSolutionLocation = automationDir .. "/" ..RebuildSolution

-- automated builds
GLFWBuildDir = buildDir .. "GLFW"
GLFWLib = GLFWBuildDir .. "/src/Debug/" .. "glfw3.lib"

-- pch
pchDirectory = "PCH"
pchName = "PCH"
pchHeaderFile = pchName .. ".h"
pchSourceFile = pchName .. ".cpp"

-- os data
osVersion = os.getversion().majorversion .. ' ' .. os.getversion().minorversion .. ' ' .. os.getversion().revision .. ' ' .. os.getversion().description

---------------------------------------------------------------------

	-- AUTOMATION UTILITY TOOLS

group(automationDir)

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

	project(GLFWBuildAutomation)

		location(GLFWBuildAutomationLocation)
		kind "Utility"

		filter "system:windows"
			prebuildcommands
			{
				"../Scripts/rebuildGLFW.bat;"
			}

group ""	

---------------------------------------------------------------------

	-- ENGINE

project(engineProjectName)
	
	location(engineProjectName)
	kind "SharedLib"
	language "C++"

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
		common,	-- common directory
		engineProjectName .. "/" .. pchDirectory,	-- local PCH directory
		GLFWInclude,	-- GLFW include directory
	}

	links
	{
		"opengl32.lib",	-- OpenGL
		GLFWBuildAutomation, -- GLFW automation
		GLFWLib,	-- glfw3.lib

	}

	filter "system:Windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MAKE_DLL",
			"QED_ENGINE_WINDOWS",
			"BUILD_OS=" .. '"' .. osVersion .. '"'
		}

		postbuildcommands
		{
			"{MKDIR} " .. "../" .. buildDir .. sandboxProjectName .. "/" .. outputDir,
			"{COPY} %{cfg.buildtarget.relpath} " ..  "../" .. buildDir .. sandboxProjectName .. "/" .. outputDir,
		}

	filter "configurations:Debug"
		defines { "QED_ENGINE_DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "QED_ENGINE_RELEASE" }
		optimize "On"

	filter "configurations:Distribution"
		defines { "QED_ENGINE_DISTRIBUTION" }
		optimize "On"

	
	filter { "system:windows" }
		buildoptions
		{
			"/MT",
			--"/MDd",
			"/sdl-",
		}


---------------------------------------------------------------------

	-- sandbox

project(sandboxProjectName)
	
	location(sandboxProjectName)
	kind "ConsoleApp"
	language "C++"

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
		common,	-- common directory
		sandboxProjectName .. "/" .. pchDirectory,	-- local PCH directory

		engineProjectName .. "/**"
	}

	links
	{
		engineProjectName
	}


	filter "system:Windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			QED_SANDBOX_WINDOWS
		}

	filter "configurations:Debug"
		defines { "QED_SANDBOX_DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "QED_SANDBOX_RELEASE" }
		optimize "On"

	filter "configurations:Distribution"
		defines { "QED_SANDBOX_DISTRIBUTION" }
		optimize "On"

	
	filter { "system:windows" }
		buildoptions
		{
			"/MT",
			--"/MD",
			"/sdl-",
		}