cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(alarm_clock C CXX ASM)

pico_sdk_init()

add_subdirectory(lib/pico-ssd1306)

add_executable(alarm_clock
        main.cpp
        display.cpp
        button.cpp)

target_link_libraries(alarm_clock
        hardware_i2c
        hardware_gpio
        hardware_timer
        hardware_rtc
        hardware_irq
        pico_ssd1306)

pico_add_extra_outputs(alarm_clock)

