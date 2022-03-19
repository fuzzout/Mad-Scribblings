workspace "Mad"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLFW"] = "Mad/port/GLFW/include"

	include "Mad/port/GLFW"

	project "Mad"
		location "Mad"
		kind "SharedLib"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "madpch.h"
		pchsource "Mad/src/madpch.cpp"

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs 
		{
			"%{prj.name}/src",
			"%{prj.name}/port/spdlog/include",
			"%{IncludeDir.GLFW}"
		}
		links {
			"GLFW",
			"opengl32.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "off"
			runtime "Debug"
			systemversion "latest"

			defines {

			"MAD_PLATFORM_WINDOWS",
			"MAD_BUILD_DLL"
			}

			postbuildcommands 
			{
				("{copy} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			}

			filter "configurations:Debug"
				defines "MAD_DEBUG"
				symbols "On"
				
			filter "configurations:Release"
				defines "MAD_RELEASE"
				optimize "On"

			filter "configurations:Dist"
				defines "MAD_DIST"
				optimize "On"



	project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
			language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Mad/port/spdlog/include",
			"Mad/src"
		}

			links
			{
				"Mad"
			}

					filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines {
			"MAD_PLATFORM_WINDOWS"
			}

			filter "configurations:Debug"
				defines "MAD_DEBUG"
				symbols "On"
				
			filter "configurations:Release"
				defines "MAD_RELEASE"
				optimize "On"

			filter "configurations:Dist"
				defines "MAD_DIST"
				optimize "On"