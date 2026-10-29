cmake_minimum_required(VERSION 3.14)
project(ClientBase LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SYSTEM_VERSION "10.0.26100.0")

add_compile_definitions(
        $<$<CONFIG:Debug>:_ITERATOR_DEBUG_LEVEL=0>
        $<$<CONFIG:Debug>:_HAS_ITERATOR_DEBUGGING=0>
)
add_compile_options(/utf-8)
add_compile_options(/EHsc)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

include(cmake/dependencies.cmake)

add_library(${PROJECT_NAME} SHARED
        src/Core/BootStrapper.cpp
        src/Core/BootStrapper.h
        src/Memory/Signatures.cpp
        src/Memory/Signatures.h
        src/Memory/Address.h
        src/Memory/SigScanner.h
        src/Utility/cryptStr.h
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
            $<$<CONFIG:Debug>:-O0>
            $<$<CONFIG:Debug>:-g>
            $<$<CONFIG:Debug>:-gcodeview>

            $<$<CONFIG:Release>:-O0>
            $<$<CONFIG:Release>:-g>
            $<$<CONFIG:Release>:-gcodeview>
            $<$<CONFIG:Release>:-fno-omit-frame-pointer>
    )
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:/Zi>
            $<$<CONFIG:Release>:/Zi>
            $<$<CONFIG:RelWithDebInfo>:/Zi>
            $<$<CONFIG:MinSizeRel>:/Zi>
    )

    target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:/DEBUG>
            $<$<CONFIG:Release>:/DEBUG>
            $<$<CONFIG:Release>:/DEBUG:FULL>
            $<$<CONFIG:RelWithDebInfo>:/DEBUG>
            $<$<CONFIG:RelWithDebInfo>:/DEBUG:FULL>
            $<$<CONFIG:MinSizeRel>:/DEBUG>
            $<$<CONFIG:MinSizeRel>:/DEBUG:FULL>
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES
            PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
        safetyhook::safetyhook
        libhat::libhat
        glm::glm
        EnTT::EnTT
        DiscordRPC
        yaml-cpp::yaml-cpp
        Microsoft::DirectX-Headers
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        _WINDLL
        WIN32_LEAN_AND_MEAN
        NOMINMAX
        GLM_ENABLE_EXPERIMENTAL
)