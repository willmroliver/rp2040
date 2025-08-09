cmake_minimum_required(VERSION 3.18)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_bootstrap C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIB_NAME ${PROJECT_NAME}_lib)

if(NOT DEFINED PICOTOOL_FETCH_FROM_GIT_PATH)
  set(PICOTOOL_FETCH_FROM_GIT_PATH ~/pico/picotool/)
endif()

pico_sdk_init()

add_subdirectory(src)

function(add_pico_executable EXEC USB UART)
  add_executable(${EXEC} ${EXEC}.c)
  target_link_libraries(${EXEC} pico_stdlib ${LIB_NAME})

  if (USB)
    pico_enable_stdio_usb(${EXEC} 1)
  endif()
  if (UART)
    pico_enable_stdio_uart(${EXEC} 1)
  endif()

  pico_add_extra_outputs(${EXEC})
endfunction()

add_pico_executable(blink 0 0)

