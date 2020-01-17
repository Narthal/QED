
-- root
workspace "QED"

	-- TODO: maybe x86
	architecture "x64"

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




-- build directories
buildDir = "Build/"
intermediateDir = ("Intermediate/")
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"

-- common directory
common = "Common"

-- project names
engineProjectName = "Engine"
sandboxProjectName = "Sandbox"

-- automation project names
GLFWBuildAutomation = "BuildGLFW"
GLFWBuildAutomationLocation = "Automation/" .. GLFWBuildAutomation

-- automation directory
automationDir = "Automation"

-- pch
pchDirectory = "PCH"
pchName = "PCH"
pchHeaderFile = pchName .. ".h"
pchSourceFile = pchName .. ".cpp"

-- os data
osVersion = os.getversion().majorversion .. ' ' .. os.getversion().minorversion .. ' ' .. os.getversion().revision .. ' ' .. os.getversion().description



group(automationDir)

project(GLFWBuildAutomation)

	location(GLFWBuildAutomationLocation)
	kind "Utility"

	filter "system:windows"
		prebuildcommands
		{
			"../Scripts/rebuildGLFW.bat;"
		}

group ""	



-- engine
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
		engineProjectName .. "/" .. pchDirectory	-- local PCH directory
	}

	links
	{
		GLFWBuildAutomation -- GLFW automation
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
			"/sdl-",
		}





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
			"/sdl-",
		}