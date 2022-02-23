
workspace "variety"
    architecture "x64"
    configurations {
        "Debug",
        "Release"
    }

    files {
        "premake5.lua",
        ".gitignore",
        ".gitmodules"
    }

    startproject "variety"

    include "extern/glfw"

    project "variety"
        location "variety"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "On"

        targetdir ("bin/%{cfg.buildcfg}/")
        objdir ("obj/%{prj.name}/%{cfg.buildcfg}/%{prj.name}")

        files {
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.h",

            "extern/glad/src/glad.c",
            "extern/imgui/*.cpp"
        }

        includedirs {
            "%{prj.name}/include",

            "extern/glad/include",
            "extern/imgui",
            
            "extern/glfw/include"
        }
        excludes {
            "%{prj.name}/include/melisma.h"
        }

        libdirs {
            "lib/glfw"
        }

        links {
            "opengl32.lib",
            "glfw.lib"
        }           

        filter "configurations:Debug"
		    defines {
                "V_DEBUG"
		    }
		    buildoptions "/MDd"
		    symbols "On"

        filter "configurations:Release"
            defines "V_RELEASE"
            buildoptions "/MD"
            optimize "On"