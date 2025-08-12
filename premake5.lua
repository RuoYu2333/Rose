workspace "Rose"
    architecture "x64"
    configurations { "Debug", "Release" ,"Dist"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Rose/vendor/GLFW/include"

include "Rose/vendor/GLFW"

project "Rose"  
    location "Rose"
    kind "SharedLib"
    language "C++"

    staticruntime "off"
    runtime "Debug"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "rspch.h"
    pchsource "Rose/src/rspch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",  
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/GLFW/include"
    }

    links {
        "GLFW",
        "opengl32.lib",
        "dwmapi.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines {
            "RS_PLATFORM_WINDOWS",
            "RS_BUILD_DLL",
            "_WINDLL"
        }


        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "RS_DEBUG" 
        symbols "On"

    filter "configurations:Release"
        defines "RS_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "RS_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",  
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
    }

    includedirs {
        "Rose/vendor/spdlog/include",
        "Rose/src"
    }

    links {
        "Rose"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines {
            "RS_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "RS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "RS_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "RS_DIST"
        optimize "On"