#ifndef IMU_ADXL380_H
#define IMU_ADXL380_H

#include "sensors/sensor_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    sensor_spi_t bus;
} adxl380_t;

/* Placeholder only. Zero-initialize; add datasheet-backed fields later.
 * This is not a sensor register value or a working default configuration.
 */
typedef struct {
    uint8_t reserved;
} adxl380_config_t;

/* Intended engineering units; decoding/scaling are not implemented. */
typedef struct {
    float x_m_s2;
    float y_m_s2;
    float z_m_s2;
} adxl380_measurement_t;

/* All functions are stubs: valid arguments return SENSOR_NOT_IMPLEMENTED.
 * No SPI/GPIO access, delays, state changes, or output writes occur.
 * init will eventually initialize/check the sensor, not the MCU peripherals.
 * configure will eventually apply explicit sensor settings.
 * trigger is separate from read for modes requiring a conversion command.
 * read will eventually retrieve a completed sample without starting one.
 * Conversion support, readiness checks, and timing remain to be determined.
 */
sensor_status_t adxl380_init(adxl380_t *device);
sensor_status_t adxl380_configure(adxl380_t *device,
                                  const adxl380_config_t *config);
sensor_status_t adxl380_trigger(adxl380_t *device);
sensor_status_t adxl380_read(adxl380_t *device,
                             adxl380_measurement_t *measurement);

#ifdef __cplusplus
}
#endif

#endif /* IMU_ADXL380_H */
