#!/bin/bash
if [ -z "$1" ]; then
    echo "Usage: build.sh [clean|release|debug]"
fi

STM32_CHIP="STM32F429ZI"
STM_BOARD="STM32F429I-Discovery"
TARGET_FILE="${TARGET_FILE:-"hmonitor"}"

CURR_DIR_PATH=$PWD
GDB_HOST="${GDB_HOST:-"127.0.0.1"}"
GDB_PORT="${GDB_PORT:-"2331"}"
PATH_TO_TC="${HOME}/opt/gcc-arm-none-eabi-5_4-2016q3"
PATH_TO_STM32CUBE="${PATH_TO_STM32CUBE:-"${HOME}/opt/STM32Cube_FW_F4_V1.16.0"}"
PATH_TO_STM32_CMAKE="${PATH_TO_STM32_CMAKE:-"${CURR_DIR_PATH}/stm32-cmake"}"
PATH_TO_FREERTOS="${CURR_DIR_PATH}/freertos/FreeRTOS"
PATH_TO_BUILD="./build"


for arg in $@; do
  if [ "clean" = "$arg" ]; then
      set -x
      rm -rf ${PATH_TO_BUILD}
  elif [ "release" = "$arg" ] || [ "build" = "$arg" ]; then
      mkdir -p ${PATH_TO_BUILD}
      cd ${PATH_TO_BUILD}
      
      cmake \
        -DTOOLCHAIN_PREFIX=$PATH_TO_TC \
        -DSTM32_CHIP=$STM32_CHIP \
        -DSTM_BOARD=$STM_BOARD \
        -DSTM32Cube_DIR=$PATH_TO_STM32CUBE \
        -DFREERTOS_ROOT=$PATH_TO_FREERTOS \
        -DCMAKE_TOOLCHAIN_FILE=$PATH_TO_STM32_CMAKE/cmake/gcc_stm32.cmake \
        -DCMAKE_MODULE_PATH=$PATH_TO_STM32_CMAKE/cmake/ \
        -DCMAKE_BUILD_TYPE=Debug ..
      make $TARGET_FILE.hex
      cd ..
  elif [ "flash" = "$arg" ]; then
      openocd -f board/stm32f4discovery.cfg -c "program build/hmonitor.hex reset exit"
  elif [ "debug" = "$arg" ]; then
      arm-none-eabi-gdb \
        -ex "target remote $GDB_HOST:$GDB_PORT" \
        -ex "monitor flash device = $STM32_DEVICE" \
        -ex "monitor halt" \
        -ex "load" \
        -ex "monitor reset" \
        $TARGET_FILE
  fi
done

