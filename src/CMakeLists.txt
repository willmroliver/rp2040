add_library(${LIB_NAME}
  clocks.c
  gpio.c
  resets.c
)

target_include_directories(
  ${LIB_NAME} 
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/inc
)

