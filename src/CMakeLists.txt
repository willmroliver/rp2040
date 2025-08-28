add_library(${LIB_NAME}
  clocks.c
  gpio.c
  led.c
  pll.c
  resets.c
  timer.c
  usb.c
  util.c
  watchdog.c
  xosc.c
)

target_include_directories(
  ${LIB_NAME} 
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/inc
)

add_subdirectory(asm)

