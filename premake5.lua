
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
buildDir = "build/"
binDir = (buildDir .. "bin/")
intermediateDir = (buildDir .. "intermediate/")
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"

-- project names
pch = "sharedPCH"
engineProjectName = "engine"
sandboxProjectName = "sandbox"

-- pch directory
enginePchDir = engineProjectName .. "/" .. "PCH/"

-- os data
osVersion = os.getversion().majorversion .. ' ' .. os.getversion().minorversion .. ' ' .. os.getversion().revision .. ' ' .. os.getversion().description


project(pch)
	location(pch)
	kind "SharedLib"
	language "C++"

	targetdir(binDir .. outputDir .. "%{prj.name}")
	objdir(intermediateDir .. outputDir .. "%{prj.name}")

	pchheader("QEDpch.h")
	pchsource(pch .. "/" .. "QEDpch.cpp")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	filter { "system:windows" }
		buildoptions
		{
			--"/MT",
			"/sdl-"
		}


-- engine
project(engineProjectName)
	
	location(engineProjectName)
	kind "SharedLib"
	language "C++"

	targetdir(binDir .. outputDir .. "%{prj.name}")
	objdir(intermediateDir .. outputDir .. "%{prj.name}")

	pchheader("QEDpch.h")
	pchsource("QEDpch.cpp")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		intermediateDir .. outputDir .. pch,		-- .pch file location
		pch
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
			"{COPY} %{cfg.buildtarget.relpath} " ..  "../" .. binDir .. outputDir .. sandboxProjectName,
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

	
	filter { "system:windows", "configurations:Release" }
		buildoptions
		{
			"/MT",
			"/sdl-"
		}





-- sandbox
project(sandboxProjectName)
	
	location(sandboxProjectName)
	kind "ConsoleApp"
	language "C++"

	targetdir(binDir .. outputDir .. "%{prj.name}")
	objdir(intermediateDir .. outputDir .. "%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

		
	includedirs
	{
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

	
	filter { "system:windows", "configurations:Release" }
		buildoptions
		{
			"/MT",
			"/sdl-"
		}