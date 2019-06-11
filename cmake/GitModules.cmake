function (execute_command command_to_execute working_directory)
    message (STATUS "Executing: `${command_to_execute}` inside ${working_directory}")
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
        message ("Failure: ${output}")
        message (FATAL_ERROR "Failure: ${error}")
    endif ()
endfunction()

function (fetch_module_with_path module_name module_path working_directory branch)
    message (STATUS "Update module: ${module_name}, with path: ${module_path}, inside: ${working_directory}")
    find_package(Git QUIET)
    if (NOT GIT_FOUND)
        message (FATAL_ERROR "Can't find git")
    endif ()

    string(FIND ${module_name} "/" module_name_last_slash REVERSE)
    string(LENGTH ${module_name} module_length)
    math(EXPR target_name_begin "${module_name_last_slash} + 1")
    math(EXPR target_name_length "${module_length} - ${target_name_begin}")
    string(SUBSTRING ${module_name} ${target_name_begin} ${target_name_length} target_name)

    if (NOT TARGET ${target_name})
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
            message ("Failure: ${output}")
            message (FATAL_ERROR "Failure: ${error}")
        endif ()

        if (NOT ${module_path} STREQUAL "")
            execute_command("git checkout ${branch}" "${PROJECT_SOURCE_DIR}/${module_name}")
            execute_command("git submodule foreach git pull" ${PROJECT_SOURCE_DIR})

            add_subdirectory(${module_path})
        endif ()
    endif ()
endfunction()
