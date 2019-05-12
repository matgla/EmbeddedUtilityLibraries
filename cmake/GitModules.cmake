function (execute_command command_to_execute working_directory)
    message (STATUS "Executing: ${command_to_execute} inside ${working_directory}")
    find_package(Git QUIET)
    if (NOT GIT_FOUND)
        message (FATAL_ERROR "Can't find git")
    endif ()

    string(REPLACE " " ";" command_to_execute "${command_to_execute}")

    execute_process(
        COMMAND
            ${command_to_execute}
        WORKING_DIRECTORY
            ${working_directory}
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error
        RESULT_VARIABLE result
        OUTPUT_QUIET
        ERROR_QUIET
    )

    if (NOT result EQUAL "0")
        message ("Failure: ${OUTPUT_VARIABLE}")
        message (FATAL_ERROR "Failure: ${ERROR_VARIABLE}")
    endif ()
endfunction()

function (fetch_module_with_path module_name module_path working_directory)
    message (STATUS "Update module: ${module_name}, with path: ${module_path}, inside: ${working_directory}")
    find_package(Git QUIET)
    if (NOT GIT_FOUND)
        message (FATAL_ERROR "Can't find git")
    endif ()

    if (NOT TARGET ${module_name})
        execute_process(
            COMMAND
                git submodule update --init -- ${module_name}
            WORKING_DIRECTORY
                ${working_directory}
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error
            RESULT_VARIABLE result
            OUTPUT_QUIET
            ERROR_QUIET

        )

        if (NOT result EQUAL "0")
            message ("Failure: ${OUTPUT_VARIABLE}")
            message (FATAL_ERROR "Failure: ${ERROR_VARIABLE}")
        endif ()

        if (NOT ${module_path} STREQUAL "")
            execute_command("git submodule foreach git checkout master" ${PROJECT_SOURCE_DIR})
            execute_command("git submodule foreach git pull" ${PROJECT_SOURCE_DIR})

            add_subdirectory(${module_path})
        endif ()
    endif ()
endfunction()
