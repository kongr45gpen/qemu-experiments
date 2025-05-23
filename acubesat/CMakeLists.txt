cmake_minimum_required(VERSION 3.23)

project(ACUBESAT C CXX ASM)

set(CMAKE_SYSTEM_NAME Generic)

# set(CMAKE_C_COMPILER    arm-none-eabi-gcc)
# set(CMAKE_CXX_COMPILER  arm-none-eabi-g++)
# set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/mps4.ld)

add_definitions(-DARM_MATH_CM7 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -D__FPU_PRESENT=1)

find_package(etl CONFIG REQUIRED)
find_package(logger CONFIG REQUIRED COMPONENTS log_common)
find_package(ecss-services CONFIG REQUIRED COMPONENTS common)

include_directories(
    original
    original/inc
    original/inc/Platform
    original/inc/FreeRTOSTasks
    original/inc/Platform/Parameters
    original/src
    original/src/config
    original/src/config/default
    original/src/config/default/osal
    original/src/config/default/peripheral/clk
    original/src/config/default/peripheral/efc
    original/src/config/default/peripheral/nvic
    original/src/config/default/peripheral/pio
    original/src/config/default/peripheral/rtc
    original/src/config/default/peripheral/systick
    original/src/config/default/peripheral/twihs/master
    original/src/config/default/system
    original/src/config/default/system/cache
    original/src/config/default/system/debug
    original/src/config/default/system/int
    original/src/config/default/system/time
    original/src/config/default/system/time/src
    original/lib/FreeRTOS
    original/lib/FreeRTOS/Source
    original/lib/FreeRTOS/Source/include
    original/lib/FreeRTOS/Source/portable
    original/lib/FreeRTOS/Source/portable/GCC
    original/lib/FreeRTOS/Source/portable/GCC/SAM
    original/lib/FreeRTOS/Source/portable/GCC/SAM/CM7
    original/lib/FreeRTOS/Source/portable/MemMang
    original/src/packs
    original/src/packs/ATSAMV71Q21B_DFP
    original/src/packs/ATSAMV71Q21B_DFP/component
    original/src/packs/ATSAMV71Q21B_DFP/instance
    original/src/packs/ATSAMV71Q21B_DFP/pio
    original/src/packs/CMSIS
    original/src/packs/CMSIS/CMSIS
    original/src/packs/CMSIS/CMSIS/Core
    original/src/packs/CMSIS/CMSIS/Core/Include
    original/AutoGenerated.X
    original/AutoGenerated.X/dist
    original/AutoGenerated.X/dist/default
    original/AutoGenerated.X/dist/default/production
    original/AutoGenerated.X/nbproject
    original/AutoGenerated.X/nbproject/private
    original/lib/SEGGER/RTT
    original/lib/SEGGER/Config
    original/lib/cross-platform-software
    original/lib/cross-platform-software
    src/drivers
)

add_subdirectory(original/lib/cross-platform-software)

file(GLOB_RECURSE DRIVER_SOURCES 
)
file(GLOB_RECURSE SOURCES
    "original/src/*.c"
    "original/src/*.cpp" 
    "original/lib/SEGGER/RTT/*.c"
    "original/AutoGenerated.X/*.c"
    "src/*.cpp"
    "src/*.c"
    "src/*.s"
)
file(GLOB_RECURSE FREERTOS_SOURCES "original/lib/FreeRTOS/*.c")

list(REMOVE_ITEM SOURCES
    ${PROJECT_SOURCE_DIR}/original/src/config/default/interrupts.c
    ${PROJECT_SOURCE_DIR}/original/src/config/default/startup_gcc.c
    ${PROJECT_SOURCE_DIR}/original/src/config/default/libc_syscalls.c
    ${PROJECT_SOURCE_DIR}/original/src/config/default/peripheral/clk/plib_clk.c
    ${PROJECT_SOURCE_DIR}/original/src/config/default/peripheral/afec/plib_afec0.c
    ${PROJECT_SOURCE_DIR}/original/src/config/default/peripheral/mcan/plib_mcan0.c
    ${PROJECT_SOURCE_DIR}/original/src/config/default/peripheral/mcan/plib_mcan1.c
    ${PROJECT_SOURCE_DIR}/original/lib/cross-platform-software/src/Platform/Logger.cpp
)

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT} ${FREERTOS_SOURCES} ${DRIVER_SOURCES})

target_link_libraries(${PROJECT_NAME}.elf PRIVATE common common_cross etl log_common)

set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS_INIT} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")

add_compile_definitions(LOGLEVEL_TRACE)

set(COMMON_OPTIONS
    # -mcpu=cortex-m7
    # -mthumb -mthumb-interwork
    -ffunction-sections -fdata-sections
    -g
    -fno-common
    -fmessage-length=0
    -specs=nosys.specs
    -specs=nano.specs
    # -mfloat-abi=soft
    -fverbose-asm
    # -specs=rdimon.specs
    -lc -lrdimon
    -O0
    -Wno-psabi
)

target_compile_options(${PROJECT_NAME}.elf PRIVATE ${COMMON_OPTIONS})
target_link_options(${PROJECT_NAME}.elf PRIVATE ${COMMON_OPTIONS} -Wl,--gc-sections -T${LINKER_SCRIPT})
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,-gc-sections,--print-memory-usage ${COMMON_OPTIONS}")