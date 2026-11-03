/* Shared types only: no bus ownership, register protocol, or scheduling layer. */
#ifndef IMU_SENSOR_COMMON_H
#define IMU_SENSOR_COMMON_H

#include <stddef.h>
#include "stm32f4xx_hal.h"

typedef enum {
    SENSOR_OK = 0,
    SENSOR_INVALID_ARGUMENT,
    SENSOR_NOT_IMPLEMENTED,
    SENSOR_NOT_READY,
    SENSOR_IO_ERROR,
    SENSOR_TIMEOUT
} sensor_status_t;

/* Caller-owned binding. Initialize GPIO and SPI before calling a driver.
 * All sensors may reference the same SPI handle; CS is active low.
 * Caller must serialize complete transactions on the shared bus, including CS.
 */
typedef struct {
    SPI_HandleTypeDef *spi;
    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;
} sensor_spi_t;

#endif /* IMU_SENSOR_COMMON_H */
