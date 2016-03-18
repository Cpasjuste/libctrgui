libctrbui
=========

- install cLion IDE
- open project in cLion
- File -> Settings -> Build, Execution... -> CMake -> CMake options  -> "-D CMAKE_TOOLCHAIN_FILE=DevkitArm3DS.cmake"
- File -> Settings -> Build, Execution... -> CMake -> Pass system... -> "DEVKITARM /opt/devkitpro/devkitARM"
- File -> Settings -> Build, Execution... -> CMake -> Pass system... -> "DEVKITPRO /opt/devkitpro"
- Tools -> CMake -> Show Generated... -> Delete all files/folders
- File -> Reload CMake Project
