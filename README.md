# alarm_clock
Alarm clock using Raspberry Pi Pico and an SSD1306 display

## Building
- Clone the repo, and initialise submodules
- Copy pico_sdk_import.cmake into the root directory and set the PICO_SDK_PATH environment variable
- Create build directory
- Move into build directory and run ```cmake ..; make```
- Plug Pico in in Bootsel mode and copy the ```alarm_clock.elf``` file onto it

## Usage
### Setting time
- Hold down Button 1 to enter time setting mode
- Use Button 2 to increase the time and Button 3 to decrease the time
- Use Button 1 and Button 4 to change which part of the time and date is changed (indicated by bar above/below)
- Leave time setting mode by pressing Button 1 when the Hour is currently selected or Button 4 when the Year is selected

### Setting Alarm
- Hold down Button 2 to enter alarm setting mode
- Set the alarm time as with clock time setting above
- Insted of setting the date, the alarm can be selected as on or off (the alarm will ring every day it is on)
- Leave time setting mode by pressing Button 1 when the Hour is currently selected or Button 4 when the alarm state is selected

### Setting Display Contrast
- Hold down Button 4 to enter display contrast setting mode
- Use Button 2 to increase contrast and Button 3 to decrease
- Press Button 1 or Button 4 to leave display contrast setting mode
