# Project Context: Prototype IMU

## Overview

This repository contains firmware for a Virginia Tech senior design project sponsored by **Psionic**. The team is developing a prototype inertial measurement unit (IMU) that measures acceleration, angular rate, magnetic field, and barometric pressure, then sends measurement data to an external controller. A separate host-PC application is planned for visualization and optional logging.

The intended system associates measurements with an external trigger and aims for predictable acquisition and transmission timing. Specific implementation details may evolve during development.

## Hardware

- **Target MCU:** STM32F411CEU6 on a Black Pill module, mounted on a custom sensor PCB.
- **Additional development board:** NUCLEO-F446RE (STM32F446RE). Its onboard ST-LINK can also be used to program/debug an external STM32 over SWD.
- **Accelerometer:** Analog Devices ADXL380.
- **Gyroscope:** TDK InvenSense ICM-40609-D.
- **Magnetometer:** MEMSIC MMC5983MA.
- **Barometer:** Bosch BMP581.
- **Sensor interface:** All four sensors share SPI1, with separate active-low chip-select GPIOs. Sensor interrupt and synchronization connections are also present.

### STM32F411 Pin Assignments

| Function | MCU pin |
| --- | --- |
| SPI1 SCK / MISO / MOSI | PA5 / PA6 / PA7 |
| ADXL380 chip select | PC14 |
| ICM-40609-D chip select | PA2 |
| MMC5983MA chip select | PB0 |
| BMP581 chip select | PA4 |
| USART1 TX / RX (debug serial) | PA9 / PA10 |
| SWDIO / SWCLK | PA13 / PA14 |

These are the currently established assignments for the target hardware. Other peripheral settings and sensor operating configurations may change.

## System Goals and Interfaces

- External trigger: 3.3 V active-high pulse, approximately 50 µs wide.
- Nominal measurement period: approximately 10 ms.
- Controller communications: UART at 921600 baud, 8-N-1.
- Trigger-to-packet latency target: 5 ms or less under nominal conditions.
- Measurement data includes acceleration XYZ, angular rate XYZ, magnetic field XYZ, and pressure, with timing/status information as appropriate.
- The packet format, sensor settings, and acquisition strategy are not finalized.

These are overall system goals; experiments and diagnostics may use different settings, such as a slower debug UART baud rate.

## Development Tools

- **STM32CubeMX 6.x:** MCU peripheral configuration and initialization code generation; the `.ioc` file stores the configuration.
- **Visual Studio Code + STM32CubeIDE extension:** Editing, building, flashing, and debugging.
- **CMake and Arm GCC:** Build system and compiler toolchain.
- **STM32CubeF4 HAL:** ST's hardware abstraction layer used by the firmware.
- **ST-LINK / SWD:** Programming and source-level debugging; STM32CubeProgrammer may also be used.

## Repository Layout

The repository is based on a **CubeMX-generated CMake project**. The principal firmware application source is under `Core/`:

```text
Core/
├── Inc/        # Application and peripheral headers
└── Src/        # Application source, including main.c and peripheral initialization
```

Depending on CubeMX code-generation settings, peripheral initialization may be in `main.c` or split into files such as `spi.c`, `gpio.c`, and `usart.c` under `Core/Src/`, with headers under `Core/Inc/`. Additional application or sensor-driver source may also live under `Core/`.

Other generated project content typically includes:

- `Drivers/`: STM32 HAL and CMSIS support code.
- `cmake/` and `CMakeLists.txt`: CMake build definitions and generated configuration.
- `*.ioc`: CubeMX peripheral/pin configuration.
- Startup assembly and a linker script: MCU-specific startup and memory mapping.

When working on firmware behavior, **look in `Core/` first**. The surrounding generated files provide MCU and build infrastructure. Exact paths may vary with CubeMX settings.

## Scope of This File

This document is background context, not a fixed implementation plan. It does not prescribe a driver API, module architecture, interrupt/DMA strategy, or development sequence. Hardware configuration and software design can be refined as the project progresses.
