/* 
 * File:   mlx90614.h
 * Author: kamor
 *
 * Created on January 28, 2022, 10:31 PM
 */

#ifndef MLX90614_H
#define	MLX90614_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Read object temperature from MLX90614.
 * @returns Temperature in centiCelsius.
 */
int32_t MLX90614ReadObjectTemp(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MLX90614_H */

