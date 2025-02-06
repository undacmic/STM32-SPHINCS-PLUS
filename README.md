# SPHINCS+ Arm Cortex-M0+ implementation

## Project Installation

### Dependencies

 - [CMake](https://cmake.org/getting-started/)
 - [Arm GNU Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) - C compiler for ARM cross-compilation
 - [OpenOCD](https://openocd.org/pages/getting-openocd.html) - Flashing the development board

### Firmware generation

```sh
mkdir build && \
cd build && \
cmake .. && \
cmake --build . --verbose

make flash
```

### Running tests and generating coverage reports

```sh
mkdir -p src/test/build && \
cd src/test/build && \
cmake .. && \
cmake --build . --verbose

ctest -T Test -E coverage -T Coverage
```