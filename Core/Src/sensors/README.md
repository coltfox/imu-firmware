# Sensor driver foundation

Public headers live in `Core/Inc/sensors/`; implementations live here.
The top-level CMake file lists the four sources explicitly. No generated
peripheral files need editing when these drivers evolve.

Each sensor has a caller-owned device containing a HAL SPI handle and its
active-low chip-select GPIO. Bind all four to `&hspi1`, using these existing
`main.h` definitions:

| Driver | CS port | CS pin |
| --- | --- | --- |
| ADXL380 | `CS_ADXL_GPIO_Port` | `CS_ADXL_Pin` |
| ICM-40609-D (`icm40609`) | `CS_ICM_GPIO_Port` | `CS_ICM_Pin` |
| MMC5983MA | `CS_MAG_GPIO_Port` | `CS_MAG_Pin` |
| BMP581 | `CS_BARO_GPIO_Port` | `CS_BARO_Pin` |

Example binding for future application code, after `MX_GPIO_Init()` and
`MX_SPI1_Init()`:

```c
#include "spi.h"
#include "sensors/adxl380.h"

adxl380_t accel = {
    .bus = { .spi = &hspi1, .cs_port = CS_ADXL_GPIO_Port, .cs_pin = CS_ADXL_Pin }
};
sensor_status_t status = adxl380_init(&accel);
/* Currently SENSOR_NOT_IMPLEMENTED; do not proceed as if initialization passed. */
```

`init` will perform sensor startup/identification, and `configure` will apply
sensor-specific settings. Config structs currently contain only a reserved byte;
zero-initialize them. No operating modes, ranges, rates, or defaults are defined.

`trigger` and `read` are separate so the application can eventually start a
conversion and retrieve it later. Whether a sensor/mode supports triggering,
how readiness is determined, and whether reads block remain datasheet decisions.
`SENSOR_NOT_READY` is available for future incomplete-conversion reporting.
No polling, delays, interrupts, or DMA behavior is implemented yet.

Measurements describe intended engineering units: acceleration in m/s^2,
angular rate in rad/s, magnetic field in microtesla, and pressure in pascals.
Only use an output when a future implementation returns `SENSOR_OK`.
Current stubs validate non-null pointers and a single nonzero CS pin mask,
then return `SENSOR_NOT_IMPLEMENTED`. They never modify outputs or hardware.
Pointer checks do not verify the actual peripheral or GPIO is initialized.

The caller owns the binding lifetime and serializes access across the shared
SPI bus (including chip-select assertion through deassertion). There is no
locking, dynamic allocation, generic driver dispatch, or transport framework.
The existing SPI mode and clock must be checked against each datasheet before
transactions are implemented; the stubs do not establish sensor compatibility.
