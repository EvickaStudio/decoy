cmake_minimum_required(VERSION 3.30)
project(decoy C)

set(CMAKE_C_STANDARD 11)

if(MSVC)
    # Optimize for size and enable link-time code generation:
    set(CMAKE_C_FLAGS_RELEASE "/O1 /GL /Gy /DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/LTCG /OPT:REF /OPT:ICF")
endif()

# Build dummy with resource
add_executable(dummy dummy.c dummy.rc)

# Build scarecrow (manager)
add_executable(decoy-manager manager.c manager.rc)

# Ensure the executables end up in the same directory
set_target_properties(dummy decoy-manager PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release")
