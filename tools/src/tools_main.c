/**
 * @file (tools_main.c)
 * @author JosheeDev
 * @copyright KrashGL Game Library (c) JosheeDev
 */

#include <core/defines.h>
#include <core/logger/logger.h>
#include <core/kstring/kstring.h>

// For executing shell commands.
#include <stdlib.h>

void print_help();
i32 process_shaders(i32 argc, char** argv);

i32 main(i32 argc, char** argv) {
    // The first arg is always the program itself.
    if (argc < 2) {
        KERROR("krash tools requires at least one argument.");
        print_help();
        return -1;
    }

    // The second argument tells us what mode to go into.
    if (strings_equali(argv[1], "buildshaders") || strings_equali(argv[1], "bshaders")) {
        return process_shaders(argc, argv);
    } else {
        KERROR("Unrecognized argument '%s'.", argv[1]);
        print_help();
        return -2;
    }

    return 0;
}

i32 process_shaders(i32 argc, char** argv) {
    if (argc < 3) {
        KERROR("Build shaders mode requires at least one additional argument.");
        return -3;
    }

    // Starting at third argument. One argument = 1 shader.
    for (u32 i = 2; i < argc; ++i) {
        char* sdk_path = NULL;
        size_t len = 0;

        #ifdef KPLATFORM_WINDOWS
        // Secure MSVC-friendly way
        if (_dupenv_s(&sdk_path, &len, "VULKAN_SDK") != 0 || sdk_path == NULL) {
            KERROR("Environment variable VULKAN_SDK not found. Check your Vulkan installation.");
            return -4;
        }
        #else
        // Portable fallback for Linux/macOS
        sdk_path = getenv("VULKAN_SDK");
        if (!sdk_path) {
            KERROR("Environment variable VULKAN_SDK not found. Check your Vulkan installation.");
            return -4;
        }
        #endif

        char end_path[10];
        i32 length = string_length(argv[i]);
        string_ncopy(end_path, argv[i] + length - 9, 9);

        // Parse the stage from the file name.
        char stage[5];
        if (strings_equali(end_path, "frag.glsl")) {
            string_ncopy(stage, "frag", 4);
        } else if (strings_equali(end_path, "vert.glsl")) {
            string_ncopy(stage, "vert", 4);
        } else if (strings_equali(end_path, "geom.glsl")) {
            string_ncopy(stage, "geom", 4);
        } else if (strings_equali(end_path, "comp.glsl")) {
            string_ncopy(stage, "comp", 4);
        }
        stage[4] = 0;

        // Output filename, just has different extension of spv.
        char out_filename[255];
        string_ncopy(out_filename, argv[i], length - 4);
        string_ncopy(out_filename + length - 4, "spv", 3);
        out_filename[length - 1] = 0;

        // Some output.
        KINFO("Processing %s -> %s...", argv[i], out_filename);
        
        // Construct the command and execute it.
        char command[4096];
        string_format(command, "%s/bin/glslc -fshader-stage=%s %s -o %s", sdk_path, stage, argv[i], out_filename);
        i32 retcode = system(command);

        #ifdef KPLATFORM_WINDOWS
        free(sdk_path); // free only if allocated by _dupenv_s
        #endif

        if (retcode != 0) {
            KERROR("Error compiling shader. See logs. Aborting process.");
            return -5;
        }
    }

    KINFO("Successfully processed all shaders.");
    return 0;
}

void print_help() {
#ifdef KPLATFORM_WINDOWS
    const char* extension = ".exe";
#else
    const char* extension = "";
#endif
    KINFO(
        "Krash Game Library Tools, Copyright 20225 JosheeDev.\n\
  usage:  tools%s <mode> [arguments...]\n\
  \n\
  modes:\n\
    buildshaders -  Builds shaders provided in arguments. For example,\n\
                    to compile Vulkan shaders to .spv from GLSL, a list of filenames\n\
                    should be provided that all end in <stage>.glsl, where <stage> is\n\
                    replaced by one of the following supported stages:\n\
                        vert, frag, geom, comp\n\
                    The compiled .spv file is output to the same path as the input file.\n",
        extension);
}
