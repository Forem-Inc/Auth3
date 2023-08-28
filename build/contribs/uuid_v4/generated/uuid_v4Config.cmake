if(NOT TARGET uuid_v4::uuid_v4)
    # Provide path for scripts
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

    include("${CMAKE_CURRENT_LIST_DIR}/uuid_v4Targets.cmake")
endif()
