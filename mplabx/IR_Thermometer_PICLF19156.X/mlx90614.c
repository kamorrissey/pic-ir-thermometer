/* 
 * File:   mlx90614.c
 * Author: kamor
 *
 * Created on January 28, 2022, 10:31 PM
 */

#include "mlx90614.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"

// Uncomment this define to stub out IR sensor
// #define NO_SENSOR

#define MLX_BUS_ADDR 0      // Default I2C bus address for MLX90614
#define RAMADDR_TAMB 6      // Address from which to read ambient (sensor's own) temperature.
#define RAMADDR_TOBJ 7      // Address from which to read object (person's) temperature.


int32_t MLX90614ReadObjectTemp(void)
{
#ifdef NO_SENSOR
    static uint8_t count = 0;
    static int32_t temp[] = { 3700, 3650, 3750, };
    if ( count >= 3 )
    {
        count = 0;
    }
    return temp[count++];
#else
    uint16_t raw = I2C1_Read2ByteRegister(MLX_BUS_ADDR, RAMADDR_TOBJ);
    // Have to swap bytes in answer
    uint16_t normalized = (raw << 8 | raw >> 8);
    // normalized is centiK, convert to centiC
    return normalized * 2L - 27315;
#endif
}
