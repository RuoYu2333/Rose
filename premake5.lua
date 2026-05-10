workspace "Rose"
    architecture "x64"
    startproject "Sandbox"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Rose/vendor/GLFW/include"
IncludeDir["GLAD"] = "Rose/vendor/Glad/include"
IncludeDir["ImGui"] = "Rose/vendor/imgui"
IncludeDir["glm"] = "Rose/vendor/glm"
IncludeDir["stb_image"] = "Rose/vendor/STB"

include "Rose/vendor/GLFW"
include "Rose/vendor/Glad"
include "Rose/vendor/imgui"


project "Rose"  
    location "Rose"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "rspch.h"
    pchsource "Rose/src/rspch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",  
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/STB/**.h",
        "%{prj.name}/vendor/STB/**.cpp"
    }
    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/GLFW/include",
        "%{prj.name}/vendor/Glad/include",
        "%{prj.name}/vendor/imgui",
        "%{prj.name}/vendor/glm",
        "%{prj.name}/vendor/STB"
    }

    links {
        "GLFW",
        "opengl32.lib",
        "Glad",
        "dwmapi.lib",
        "ImGui"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "RS_PLATFORM_WINDOWS",
            "RS_BUILD_DLL",
            "_WINDLL",
            "GLFW_INCLUDE_NONE"
        }


    filter "configurations:Debug"
        defines "RS_DEBUG"
        runtime "Debug"
        buildoptions "/MDd"
        symbols "on"
        disablewarnings { 
        "6294", 
        "26495",
        "26498" ,
        "26800",
        "4005"
    }
    	linkoptions { "/IGNORE:4006","/IGNORE:4098"}

    filter "configurations:Release"
        defines "RS_RELEASE"
        runtime "Release"
        buildoptions "/MD"
        optimize "on"
        disablewarnings { 
        "6294", 
        "26495",
        "26498" ,
        "26800",
        "4005"
    }
        linkoptions { "/IGNORE:4006","/IGNORE:4098" }
    filter "configurations:Dist"
        defines "RS_DIST"
        runtime "Release"
        buildoptions "/MD"
        optimize "on"
        disablewarnings { 
        "6294", 
        "26495",
        "26498" ,
        "26800",
        "4005"
    }
    	linkoptions { "/IGNORE:4006","/IGNORE:4098" }

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

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
        "Rose/src",
        "Rose/vendor/glm",
        "Rose/vendor"
    }

    links {
        "Rose"
    }

    filter "system:windows"
        systemversion "latest"

        defines { 
            "RS_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "RS_DEBUG"
        runtime "Debug"
        buildoptions "/MDd"
        symbols "on"
        disablewarnings { 
        "6294", 
        "26495",
        "26498" ,
        "26800",
        "4005"
    }
    	linkoptions { "/IGNORE:4006","/IGNORE:4098" }

    filter "configurations:Release"
        defines "RS_RELEASE"
        runtime "Release"
        buildoptions "/MD"
        optimize "on"
        disablewarnings { 
        "6294", 
        "26495",
        "26498" ,
        "26800",
        "4005"
    }
        linkoptions { "/IGNORE:4006","/IGNORE:4098" }

    filter "configurations:Dist"
        defines "RS_DIST"
        runtime "Release"
        buildoptions "/MD"
        optimize "on"
        disablewarnings { 
        "6294", 
        "26495",
        "26498" ,
        "26800",
        "4005"
    }
     	linkoptions { "/IGNORE:4006","/IGNORE:4098"}       
 