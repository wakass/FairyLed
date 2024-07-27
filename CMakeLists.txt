# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# Pull in Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(FairyLed C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

set(PICO_CXX_ENABLE_RTTI 1)

# Initialise the Pico SDK
pico_sdk_init()

include("PicoLed/PicoLed.cmake")

# Add executable. Default name is the project name, version 0.1

add_executable(FairyLed FairyLed.cpp )

pico_set_program_name(FairyLed "FairyLed")
pico_set_program_version(FairyLed "0.1")

pico_enable_stdio_uart(FairyLed 1)
pico_enable_stdio_usb(FairyLed 1)

# Add the standard library to the build
target_link_libraries(FairyLed pico_stdlib PicoLed)

pico_add_extra_outputs(FairyLed)
## Make upload possible
## add_custom_target(upload avrdude  -c ${PROG_TYPE} -p ${MCU} -U flash:w:${PRODUCT_NAME}.hex DEPENDS hex)
## Send the magic 1200 baud reset, and upload uf2

add_custom_target(upload ALL 
        COMMAND stty -f /dev/tty.usbmodem11401 1200 
        COMMAND sleep 1 
        COMMAND picotool load -f -x FairyLed.uf2
        COMMENT "Uploading to device"
        DEPENDS FairyLed)
