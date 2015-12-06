cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME puppetbot)
project(${PROJECT_NAME})

set(${CMAKE_PROJECT_NAME}_SKETCH puppetbot.ino)

#set(${CMAKE_PROJECT_NAME}_BOARD uno)
#set(${CMAKE_PROJECT_NAME}_PORT /dev/tty.usbmodem1421)

set(${CMAKE_PROJECT_NAME}_BOARD nano)
set(${CMAKE_PROJECT_NAME}_PORT /dev/cu.wchusbserial1420)
set(nano.build.mcu atmega328p)
set(nano.upload.protocol arduino)
set(nano.upload.speed 57600)

link_directories(/Applications/Arduino.app/Contents/Java/libraries)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libraries)
link_directories(/Users/albinotonnina/Documents/Arduino/libraries)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})