#libctrgui

##cLion IDE (linux)
 1. Install cLion IDE
 2. Open project in cLion
 3. File -> Settings -> Build, Execution... -> CMake -> CMake options  -> "-D CMAKE_TOOLCHAIN_FILE=DevkitArm3DS.cmake"
 4. File -> Settings -> Build, Execution... -> CMake -> Pass system... -> "DEVKITARM /opt/devkitpro/devkitARM"
 5. File -> Settings -> Build, Execution... -> CMake -> Pass system... -> "DEVKITPRO /opt/devkitpro"
 6. Tools -> CMake -> Show Generated... -> Delete all files/folders
 7. File -> Reload CMake Project

##linux (shell)
 1. `mkdir build/`
 2. `cd build/`
 3. `cmake -DCMAKE_TOOLCHAIN_FILE=../DevkitArm3DS.cmake ../`
 4. `cmake --build . --target Example_3dsx`
