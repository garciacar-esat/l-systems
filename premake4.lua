solution ("L_System_solution_" .. _ACTION)
  configurations { "Debug", "Release" }
  platforms { "x32", "x64" }
  location ("build")
  language "C"
  kind "ConsoleApp"

	language "C++"
	kind "ConsoleApp"

	projects = { "PR0_Base"}

	for i, prj in ipairs(projects) do
		project (prj)
		targetname (prj)

		prj_path = "./build/" .. prj

		location (prj_path .. "/" .. _ACTION)

		includedirs {
			"./include/",
			"./deps/include",
		}

		files {
			"./deps/include/*.h",
		}

	    defines { "_CRT_SECURE_NO_WARNINGS" }
	    flags { "ExtraWarnings" }

		configuration "vs2015"
		  windowstargetplatformversion "8.1"

		configuration "vs2017"
		--windowstargetplatformversion "10.0.15063.0"
		  windowstargetplatformversion "10.0.16299.0"
		--windowstargetplatformversion "10.0.17134.0"
		--windowstargetplatformversion "10.0.17134.471"


    configuration "Debug"
        defines { "DEBUG" }
		links {"opengl32",
		"user32","shell32","gdi32"}
        targetdir ("bin/Debug")
        targetsuffix "_d"
        objdir ("build/" .. "Debug")
        flags { "Symbols" }

    configuration "Release"
		links { "opengl32",
		"user32","shell32","gdi32"}
        targetdir ("bin/Release")
        objdir ("build/" .. "Release")
        flags { "Optimize" }

	end

	project "PR0_Base"
		files {
      "./tests/base.cpp",
      "./include/LSystem.h"
    }