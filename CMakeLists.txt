cmake_minimum_required(VERSION 3.18)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_bootstrap C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(LIB_NAME ${PROJECT_NAME}_lib)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(LINKER_SCRIPT linker.ld)

set(COMMON_FLAGS "-march=armv6-m -mcpu=cortex-m0plus -mthumb -g")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++20")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu99")

add_link_options(
  "-T${CMAKE_SOURCE_DIR}/linker.ld"
)

add_subdirectory(src)

function(add_linked_executable EXEC)
  add_executable(${EXEC} 
    ${EXEC}.c
    sys/newlib.c
    sys/vector.c
    sys/asm/newlib.s
    sys/asm/boot2.s
  )
  target_link_libraries(${EXEC} ${LIB_NAME})
endfunction()

add_linked_executable(blink)

