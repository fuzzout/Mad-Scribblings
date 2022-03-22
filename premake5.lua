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
	
	include "Mad/port/GLFW"
	include "Mad/port/Glad"
	include "Mad/port/imgui"

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
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.Glad}"
		}
		links {
			"GLFW",
			"Glad",
			"ImGui",
			"opengl32.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "off"
			runtime "Debug"
			systemversion "latest"

			defines {

			"MAD_PLATFORM_WINDOWS",
			"MAD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
			}

			postbuildcommands 
			{
				("{copy} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			}

		filter "configurations:Debug"
			defines "HZ_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "HZ_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "HZ_DIST"
			buildoptions "/MD"
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
		defines "HZ_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		buildoptions "/MD"
		optimize "On" 