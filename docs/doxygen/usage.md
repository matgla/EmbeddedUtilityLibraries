Usage guide {#usage_page}
=========================


EmbeddedUtilityLibrary uses CMake as a project configurator. To use it in your project, you must add sources, i.e., with git submodules.
When sources are available call `add_subdirectory(eul_path)` from your CMakeLists. 

If you are using [Yaspem](https://github.com/matgla/Yaspem), here is the package entry snippet: 
```json 
{
    "link": "https://github.com/matgla/EmbeddedUtilityLibraries.git",
    "type": "git",
    "version": "master",
    "target": "eul",
    "options": {
        "cmake_variables": {
            "DISABLE_TESTS": "ON",
            "DISABLE_SANITIZERS": "ON"
        }
    }
}
```

After that, call `find_package(eul REQUIRED)` from your CMakeLists.txt.

To configure dedicated compiler flags, you can pass the `eul_cxx_compilation_flags` variable via CMake. 
You can pass the `eul_cxx_linking_flags` variable to configure dedicated linker flags via CMake.
