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
	IncludeDir["Glad"] = "Mad/port/Glad/include"
	IncludeDir["ImGui"] = "Mad/port/imgui"
	IncludeDir["glm"] = "Mad/port/glm"
	IncludeDir["stb_image"] = "Mad/port/stb_image"
	
	include "Mad/port/GLFW"
	include "Mad/port/Glad"
	include "Mad/port/imgui"

	project "Mad"
		location "Mad"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "madpch.h"
		pchsource "Mad/src/madpch.cpp"

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/port/stb_image/**.h",
			"%{prj.name}/port/stb_image/**.cpp"
		}
		
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
		includedirs 
		{
			"%{prj.name}/src",
			"%{prj.name}/port/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}"
		}
		links {
			"GLFW",
			"Glad",
			"ImGui",
			"opengl32.lib"
		}

		filter "system:windows"
			systemversion "latest"

			defines {

			"MAD_PLATFORM_WINDOWS",
			"MAD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
			}

		filter "configurations:Debug"
			defines "HZ_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "HZ_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "HZ_DIST"
			runtime "Release"
			optimize "On"



	project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Mad/port/spdlog/include",
			"Mad/port/glm",
			"Mad/src"
		}

			links
			{
				"Mad"
			}

			filter "system:windows"
			systemversion "latest"

			defines {
			"MAD_PLATFORM_WINDOWS"
			}


	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on" 