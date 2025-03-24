cmake_minimum_required(VERSION 3.19.2)

project(SIMPLE C CXX ASM)

# the name of the target operating system
set(CMAKE_SYSTEM_NAME Generic)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH  /usr/i586-mingw32msvc
    /home/alex/mingw-install)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/stm32.ld)

add_executable(main.elf startup.s main.cpp)

set(COMMON_OPTIONS
    -mcpu=cortex-m3
    -mthumb -mthumb-interwork
    # -ffunction-sections -fdata-sections
    -g
    -fno-common
    -fmessage-length=0
    # -specs=nosys.specs
    # -specs=nano.specs
    -mfloat-abi=soft
    -fverbose-asm
    -specs=rdimon.specs
    -lc -lrdimon
    -O0
)
target_compile_options(main.elf PRIVATE ${COMMON_OPTIONS})
target_link_options(main.elf PRIVATE ${COMMON_OPTIONS} -Wl,--gc-sections -T${LINKER_SCRIPT})