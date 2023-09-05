cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(strand_burner
        LANGUAGES C ASM CXX)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of the project

add_executable(strand_burner main.c)

target_link_libraries(strand_burner pico_stdlib)

pico_enable_stdio_uart(strand_burner 1)
pico_enable_stdio_usb(strand_burner 0)

pico_add_extra_outputs(strand_burner)

