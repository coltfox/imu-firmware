#include "sensors/bmp581.h"

/* Checks the binding only; does not indicate hardware is initialized. */
static int valid_device(const bmp581_t *device)
{
    return device != NULL && device->bus.spi != NULL &&
           device->bus.cs_port != NULL && device->bus.cs_pin != 0U &&
           (device->bus.cs_pin & (device->bus.cs_pin - 1U)) == 0U;
}

sensor_status_t bmp581_init(bmp581_t *device)
{
    /* TODO: datasheet-backed reset, identification, and startup sequence. */
    return valid_device(device) ? SENSOR_NOT_IMPLEMENTED : SENSOR_INVALID_ARGUMENT;
}

sensor_status_t bmp581_configure(bmp581_t *device,
                                  const bmp581_config_t *config)
{
    /* TODO: define supported settings and their register transactions. */
    if (!valid_device(device) || config == NULL) {
        return SENSOR_INVALID_ARGUMENT;
    }
    return SENSOR_NOT_IMPLEMENTED;
}

sensor_status_t bmp581_trigger(bmp581_t *device)
{
    /* TODO: determine whether/how the selected mode starts a conversion. */
    return valid_device(device) ? SENSOR_NOT_IMPLEMENTED : SENSOR_INVALID_ARGUMENT;
}

sensor_status_t bmp581_read(bmp581_t *device,
                             bmp581_measurement_t *measurement)
{
    /* TODO: readiness handling, register reads, decoding, and scaling. */
    if (!valid_device(device) || measurement == NULL) {
        return SENSOR_INVALID_ARGUMENT;
    }
    return SENSOR_NOT_IMPLEMENTED;
}
