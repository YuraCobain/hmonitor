#!/bin/bash
if [ -z "$1" ]; then
    echo "Usage: build.sh [clean|release|debug]"
fi

STM32_CHIP="STM32F429ZI"
STM_BOARD="STM32F429I-Discovery"
TARGET_FILE="${TARGET_FILE:-"hmonitor"}"

GDB_HOST="${GDB_HOST:-"127.0.0.1"}"
GDB_PORT="${GDB_PORT:-"2331"}"
PATH_TO_TC="/opt/gcc-arm-none-eabi-5_4-2016q3"
PATH_TO_STM32CUBE="${PATH_TO_STM32CUBE:-"/opt/STM32Cube_FW_F4_V1.15.0"}"
PATH_TO_STM32_CMAKE="${PATH_TO_STM32_CMAKE:-"/home/ikobein/dev/evo/hmonitor/stm32-cmake"}"
PATH_TO_FREERTOS="/home/ikobein/dev/evo/hmonitor/freertos/FreeRTOS"
PATH_TO_BUILD="./build"

mkdir -p ${PATH_TO_BUILD}
cd ${PATH_TO_BUILD}

for arg in $@; do
  if [ "clean" = "$arg" ]; then
      set -x
      rm -rf ../${PATH_TO_BUILD}
  elif [ "release" = "$arg" ]; then
      cmake \
        -DTOOLCHAIN_PREFIX=$PATH_TO_TC \
        -DSTM32_CHIP=$STM32_CHIP \
        -DSTM_BOARD=$STM_BOARD \
        -DSTM32Cube_DIR=$PATH_TO_STM32CUBE \
        -DFREERTOS_ROOT=$PATH_TO_FREERTOS \
        -DCMAKE_TOOLCHAIN_FILE=$PATH_TO_STM32_CMAKE/cmake/gcc_stm32.cmake \
        -DCMAKE_MODULE_PATH=$PATH_TO_STM32_CMAKE/cmake/ \
        -DCMAKE_BUILD_TYPE=Release \
        ../ \
      make -j4 $TARGET_FILE.hex
  elif [ "build" = "$arg" ]; then
      cmake \
        -DTOOLCHAIN_PREFIX=$PATH_TO_TC \
        -DSTM32_CHIP=$STM32_CHIP \
        -DSTM_BOARD=$STM_BOARD \
        -DSTM32Cube_DIR=$PATH_TO_STM32CUBE \
        -DFREERTOS_ROOT=$PATH_TO_FREERTOS \
        -DCMAKE_TOOLCHAIN_FILE=$PATH_TO_STM32_CMAKE/cmake/gcc_stm32.cmake \
        -DCMAKE_MODULE_PATH=$PATH_TO_STM32_CMAKE/cmake/ \
        -DCMAKE_BUILD_TYPE=Debug ..
      make  $TARGET_FILE.hex
  elif [ "flash" = "$arg" ]; then
      exec 5>&1
      JLINK_OUTPUT=$(JLinkExe -commandfile ./tools/flash.jlink|tee >(cat - >&5))

      if (echo $JLINK_OUTPUT | egrep -i "failed|warning" > /dev/null)
      then
        echo "**********************"
        echo "Flash failed or warned"
        echo "**********************"
        exit 1
      else
        echo "Flash ok!"
      fi
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

