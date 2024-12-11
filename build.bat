@echo off

REM Check if build directory exists
if exist build (
    REM Remove the build folder
    rmdir /s /q build
)

REM Create a new build folder
mkdir build

REM Change to the build folder
pushd build

REM Run cmake to generate the build files
cmake .. -DCMAKE_BUILD_TYPE=Release

REM Build the project
cmake --build . --config Release

REM Return to the original directory
popd

REM Pause the script
@REM pause

exit