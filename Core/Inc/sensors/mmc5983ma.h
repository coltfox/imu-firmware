#ifndef IMU_MMC5983MA_H
#define IMU_MMC5983MA_H

#include "sensors/sensor_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    sensor_spi_t bus;
} mmc5983ma_t;

/* Placeholder only. Zero-initialize; add datasheet-backed fields later.
 * This is not a sensor register value or a working default configuration.
 */
typedef struct {
    uint8_t reserved;
} mmc5983ma_config_t;

/* Intended engineering units; decoding/scaling are not implemented. */
typedef struct {
    float x_uT;
    float y_uT;
    float z_uT;
} mmc5983ma_measurement_t;

/* All functions are stubs: valid arguments return SENSOR_NOT_IMPLEMENTED.
 * No SPI/GPIO access, delays, state changes, or output writes occur.
 * init will eventually initialize/check the sensor, not the MCU peripherals.
 * configure will eventually apply explicit sensor settings.
 * trigger is separate from read for modes requiring a conversion command.
 * read will eventually retrieve a completed sample without starting one.
 * Conversion support, readiness checks, and timing remain to be determined.
 */
sensor_status_t mmc5983ma_init(mmc5983ma_t *device);
sensor_status_t mmc5983ma_configure(mmc5983ma_t *device,
                                  const mmc5983ma_config_t *config);
sensor_status_t mmc5983ma_trigger(mmc5983ma_t *device);
sensor_status_t mmc5983ma_read(mmc5983ma_t *device,
                             mmc5983ma_measurement_t *measurement);

#ifdef __cplusplus
}
#endif

#endif /* IMU_MMC5983MA_H */
