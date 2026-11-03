#ifndef IMU_ICM40609_H
#define IMU_ICM40609_H

#include "sensors/sensor_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    sensor_spi_t bus;
} icm40609_t;

/* Placeholder only. Zero-initialize; add datasheet-backed fields later.
 * This is not a sensor register value or a working default configuration.
 */
typedef struct {
    uint8_t reserved;
} icm40609_config_t;

/* Intended engineering units; decoding/scaling are not implemented. */
typedef struct {
    float x_rad_s;
    float y_rad_s;
    float z_rad_s;
} icm40609_measurement_t;

/* All functions are stubs: valid arguments return SENSOR_NOT_IMPLEMENTED.
 * No SPI/GPIO access, delays, state changes, or output writes occur.
 * init will eventually initialize/check the sensor, not the MCU peripherals.
 * configure will eventually apply explicit sensor settings.
 * trigger is separate from read for modes requiring a conversion command.
 * read will eventually retrieve a completed sample without starting one.
 * Conversion support, readiness checks, and timing remain to be determined.
 */
sensor_status_t icm40609_init(icm40609_t *device);
sensor_status_t icm40609_configure(icm40609_t *device,
                                  const icm40609_config_t *config);
sensor_status_t icm40609_trigger(icm40609_t *device);
sensor_status_t icm40609_read(icm40609_t *device,
                             icm40609_measurement_t *measurement);

#ifdef __cplusplus
}
#endif

#endif /* IMU_ICM40609_H */
