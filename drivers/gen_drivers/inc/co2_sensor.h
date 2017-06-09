#ifndef __CO2_SENSOR_H__
#define __CO2_SENSOR_H__

#include "gen_types.h"

hm_ret_t co2_sensor_init(void);
hm_ret_t co2_sensor_uninit(void);
hm_ret_t co2_sensor_val_get(uint16_t *val);

#endif /* __CO2_SENSOR_DRV_H__ */
