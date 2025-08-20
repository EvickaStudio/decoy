cmake_minimum_required(VERSION 3.30)
project(decoy 
    VERSION 0.1.0
    DESCRIPTION "A lightweight Windows utility that creates dummy processes mimicking analysis tools"
    LANGUAGES C
)

# Set C standard and require it
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Modern CMake: use target-based approach instead of global include_directories
# include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Create a common library for shared code
add_library(decoy-common STATIC
    src/utils.c
    src/banner.c
    src/args.c
    src/process_control.c
)

# Set include directories for the common library
target_include_directories(decoy-common 
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Add executables
add_executable(dummy
    src/dummy.c
    resources/dummy.rc
)

add_executable(decoy-manager
    src/manager.c
    resources/manager.rc
)

# Link the common library to decoy-manager
target_link_libraries(decoy-manager PRIVATE decoy-common)

# Windows-specific configuration
if(WIN32)
    if(MSVC)
        # Optimize for size and enable link-time code generation
        target_compile_options(decoy-manager PRIVATE 
            $<$<CONFIG:Release>:/O1 /GL /Gy>
        )
        target_link_options(decoy-manager PRIVATE 
            $<$<CONFIG:Release>:/LTCG /OPT:REF /OPT:ICF>
        )
    endif()
    
    # Link against required Windows libraries
    target_link_libraries(decoy-manager PRIVATE Version Psapi)
    
    # Set output directory for all configurations
    set_target_properties(dummy decoy-manager PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release"
    )
endif()
