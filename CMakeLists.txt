cmake_minimum_required(VERSION 3.30)
project(decoy C)

set(CMAKE_C_STANDARD 11)

if(MSVC)
    # Optimize for size and enable link-time code generation:
    set(CMAKE_C_FLAGS_RELEASE "/O1 /GL /Gy /DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/LTCG /OPT:REF /OPT:ICF")
endif()

# Specify where to find headers and resources
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Add executables
add_executable(dummy
    src/dummy.c
    resources/dummy.rc
)

add_executable(decoy-manager
    src/manager.c
    src/process_control.c
    src/utils.c
    src/banner.c
    src/args.c
    resources/manager.rc
)

# Ensure the executables end up in the same directory
set_target_properties(dummy decoy-manager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release")

# Link libraries (if needed, none needed here)
# target_link_libraries(decoy-manager ...)
