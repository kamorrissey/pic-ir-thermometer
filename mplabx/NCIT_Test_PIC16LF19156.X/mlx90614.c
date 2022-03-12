/* 
 * File:   mlx90614.c
 * Author: kamor
 *
 * Created on January 28, 2022, 10:31 PM
 */

#include <xc.h>

#include "mlx90614.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"

#define _XTAL_FREQ 1000000

// Uncomment this define to stub out IR sensor
//#define NO_SENSOR

#define MLX_BUS_ADDR 0x5A   // Default I2C bus address for MLX90614
#define RAMADDR_TAMB 6      // Address from which to read ambient (sensor's own) temperature.
#define RAMADDR_TOBJ 7      // Address from which to read object (person's) temperature.
#define ADDR_SLEEP 0xFF     // Address for sleep command
#define PEC_SLEEP 0xE8      // Error check code for sleep command


// crc8 is adapted from https://github.com/sparkfun/SparkFun_MLX90614_Arduino_Library/blob/master/src/SparkFunMLX90614.cpp
static uint8_t crc8 (uint8_t inCrc, uint8_t inData)
{
	uint8_t data = inCrc ^ inData;
	for (uint8_t i = 0; i < 8; i++)	{
		if (( data & 0x80 ) != 0 ) {
			data <<= 1;
			data ^= 0x07;
		} else {
			data <<= 1;
		}
	}
	return data;
}

int32_t MlxReadObjectTemp(void)
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
    uint8_t bus_addr = MLX_BUS_ADDR;
    // TODO: implement error handling on sensor read
    uint16_t raw = I2C1_Read2ByteRegister(bus_addr, RAMADDR_TOBJ);
    // Have to swap bytes in answer
    uint16_t normalized = (raw << 8 | raw >> 8);
    // normalized is centiK, convert to centiC
    return normalized * 2L - 27315;
#endif
}

void MlxSleep(void)
{
#ifndef NO_SENSOR
    // send MLX90614 sleep request
    uint8_t bus_addr = MLX_BUS_ADDR;
    uint8_t crc = crc8(0, bus_addr<<1);
    crc = crc8(crc, ADDR_SLEEP);
    I2C1_Write1ByteRegister(bus_addr, ADDR_SLEEP, PEC_SLEEP);
#endif    
    // set SCL/SDA to GPIO output
    RC3PPS = 0;
    RC4PPS = 0;
    TRISC3 = 0; // SCL
    TRISC4 = 0; // SDA
    // drive SCL low, SDA high
    RC3 = 0;
    RC4 = 1;
    // leave SCL/SDA as GPIO output
}

void MlxWake(void)
{
    // assuming SCL/SDA are GPIO output...
    // drive SCL hi, wait 5ms
    RC3 = 1;
    __delay_ms(1);
    // drive SDA low, wait 35ms
    RC4 = 0;
    __delay_ms(40);
    // set SCL/SDA to GPIO input
    TRISC3 = 1; // SCL
    TRISC4 = 1; // SDA
    RC3PPS = 0x13;
    RC4PPS = 0x14;
#ifndef NO_SENSOR
    // sleep 300ms, waiting for sensor to initialize (0.25s nominal)
    __delay_ms(300);
    // Get a temp reading because 1st one after sensor init will be raw
    (void)MlxReadObjectTemp();
#endif
}
