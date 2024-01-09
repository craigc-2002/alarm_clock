# alarm_clock
Alarm clock using Raspberry Pi Pico and an SSD13-6 display

## Building
- Clone the repo, and initialise submodules
- Copy pico_sdk_import.cmake into the root directory and set the PICO_SDK_PATH environment variable
- Create build directory
- Move into build directory and run ```cmake ..; make```