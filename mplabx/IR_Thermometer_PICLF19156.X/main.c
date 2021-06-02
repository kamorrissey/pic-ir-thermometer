/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16LF19156
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "display.h"

typedef enum sm_state {
    ST1, ST2, ST3, ST4, ST5,
    ST6, ST7, ST8, ST9, ST10,
    ST11,
} SM_STATE;

typedef enum temp_mode {
    FAHRENHEIT,
    CELSIUS,
} TEMP_MODE;


typedef struct dataee_block {
    uint8_t temp_mode;
} DATAEE_BLOCK;

typedef struct app_state {
    DATAEE_BLOCK dataee_block;
    uint8_t temp_exists;
    float temp_C;
    volatile int16_t ticks_remaining;
    SM_STATE next_sm_state;
} APP_STATE;

const uint16_t DATAEE_BLOCK_BASE = 0xF000;

APP_STATE g_app_state;

// forward references
void App_Initialize(void);
void App_GotoState( SM_STATE new_state );
void App_OnTimerClick(void);
void App_DisplayTemp(void);
void App_RunST1(void);
void App_RunST2(void);
void App_RunST3(void);
void App_RunST4(void);
void App_RunST5(void);
void App_RunST6(void);
void App_RunST7(void);
void App_RunST8(void);
void App_RunST9(void);
void App_RunST10(void);
void App_RunST11(void);

float Get_SupplyVoltage(void);
float Get_Temperature(void);
void DataEE_Load( DATAEE_BLOCK* buffer );
void DataEE_Store( DATAEE_BLOCK* buffer );

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
        
    App_Initialize();
    TMR0_SetInterruptHandler( App_OnTimerClick );
    
    while (1)
    {
        switch (g_app_state.next_sm_state)
        {
        default:
        case ST1:
            App_RunST1();
            break;
        case ST2:
            App_RunST2();
            break;
        case ST3:
            App_RunST3();
            break;
        case ST4:
            App_RunST4();
            break;
        case ST5:
            App_RunST5();
            break;
        case ST6:
            App_RunST6();
            break;
        case ST7:
            App_RunST7();
            break;
        case ST8:
            App_RunST8();
            break;
        case ST9:
            App_RunST9();
            break;
        case ST10:
            App_RunST10();
            break;
        case ST11:
            App_RunST11();
            break;
       }
    }
}

float Get_SupplyVoltage(void)
{
    ADCC_StartConversion(channel_FVR_Buffer1);
    while(!ADCC_IsConversionDone());
    uint16_t adc = ADCC_GetConversionResult();
    float supply_voltage = (float)( 1.024 * 4096.0 / adc );
    return supply_voltage;
}

float Get_Temperature(void)
{
    static uint8_t count = 0;
    static float temp[] = { 37.0f, 36.5f, 37.5f, };
    if ( count >= 3 )
    {
        count = 0;
    }
    return temp[count++];
}

void App_Initialize(void)
{
    App_GotoState( ST1 );
    DataEE_Load(&g_app_state.dataee_block);
    g_app_state.temp_exists = 0;
    g_app_state.temp_C = 0.0f;
}

void App_GotoState( SM_STATE sm_state )
{
    TMR0_StopTimer();
    g_app_state.next_sm_state = sm_state;
    g_app_state.ticks_remaining = 0;
}

void App_OnTimerClick(void)
{
    if ( g_app_state.ticks_remaining > 0 )
    {
        --g_app_state.ticks_remaining;
    }
}

void App_DisplayTemp(void)
{
    if ( !g_app_state.temp_exists )
    {
        DISPLAY_Ready();
    }
    else
    {
        int16_t temp;
        if ( g_app_state.dataee_block.temp_mode == FAHRENHEIT )
        {
            temp = (int16_t)(10 * ( g_app_state.temp_C * 9 / 5 + 32 ) + 0.5);
        }
        else
        {
            temp = (int16_t)(10 * g_app_state.temp_C + 0.5);
        }
        DISPLAY_ShowNumber( temp, 1 );
    }
}

void App_RunST1(void)
{
    // Display temperature or ready-indicator
    LCD_Enable();
    App_DisplayTemp();
    App_GotoState( ST2 );
}

void App_RunST2(void)
{
    // Wait for all buttons released
    while ( CLC1_OutputStatusGet() || CLC2_OutputStatusGet() )
    {
        SLEEP();
    }
    App_GotoState( ST3 );
}

void App_RunST3(void)
{
    // Wait for button press or timeout
    g_app_state.ticks_remaining = 300; // 30 secs * 10 ticks/sec
    TMR0_Reload();
    TMR0_StartTimer();
    while (1)
    {
        if ( CLC1_OutputStatusGet() )
        {
            App_GotoState( ST4 );
            return;
        }
        else if ( CLC2_OutputStatusGet() )
        {
            App_GotoState( ST8 );
            return;
        }
        else if ( g_app_state.ticks_remaining == 0 )
        {
            App_GotoState( ST7 );
            return;
        }
        else
        {
            SLEEP();
        }
    }
}

void App_RunST4(void)
{
    // Measure Vdd, compare to threshold
    float vdd = Get_SupplyVoltage();
    if ( vdd < 2.65 )
    {
        App_GotoState( ST6 );
    }
    else
    {
        App_GotoState( ST5 );
    }
}

void App_RunST5(void)
{
    // Capture temperature
    g_app_state.temp_C = Get_Temperature();
    g_app_state.temp_exists = 1;
    App_GotoState( ST1 );
}

void App_RunST6(void)
{
    // Display low battery
    LCD_Enable();
    DISPLAY_BatteryLow();
    App_GotoState( ST2 );
}

void App_RunST7(void)
{
    // Clear display
    DISPLAY_AllPixels_Off();
    LCD_Disable();
    App_GotoState( ST3 );
}

void App_RunST8(void)
{
    // Display units
    LCD_Enable();
    DISPLAY_DIG1_Segments( DISPLAY_CharToSegments(' '));
    DISPLAY_DIG2_Segments( DISPLAY_CharToSegments(' '));
    DISPLAY_DIG3_Segments( DISPLAY_CharToSegments(' '));
    if ( g_app_state.dataee_block.temp_mode == FAHRENHEIT )
    {
        DISPLAY_DIG4_Segments( DISPLAY_CharToSegments('F'));
    }
    else
    {
        DISPLAY_DIG4_Segments( DISPLAY_CharToSegments('C'));
    }
    DISPLAY_DP1_Off();
    DISPLAY_DP2_Off();
    DISPLAY_DP3_Off();
    DISPLAY_COLON_Off();
    App_GotoState( ST11 );
}

void App_RunST9(void)
{
    // Wait for button press or timeout
    g_app_state.ticks_remaining = 50; // 5 secs
    TMR0_Reload();
    TMR0_StartTimer();
    while (1)
    {
        if ( CLC1_OutputStatusGet() )
        {
            App_GotoState( ST1 );
            return;
        }
        else if ( CLC2_OutputStatusGet() )
        {
            App_GotoState( ST10 );
            return;
        }
        else if ( g_app_state.ticks_remaining == 0 )
        {
            App_GotoState( ST1 );
            return;
        }
        else
        {
            SLEEP();
        }
    }
}

void App_RunST10(void)
{
    // Toggle units
    if ( g_app_state.dataee_block.temp_mode == FAHRENHEIT )
    {
        g_app_state.dataee_block.temp_mode = CELSIUS;
    }
    else
    {
        g_app_state.dataee_block.temp_mode = FAHRENHEIT;
    }
    // TODO: save units to EEPROM
    DataEE_Store(&g_app_state.dataee_block);
    App_GotoState( ST8 );
}

void App_RunST11(void)
{
    // Wait for all buttons released
    while ( CLC1_OutputStatusGet() || CLC2_OutputStatusGet() )
    {
        SLEEP();
    }
    App_GotoState( ST9 );
}

void DataEE_Load( DATAEE_BLOCK* buffer )
{
    uint8_t* dest = (uint8_t*)buffer;
    for ( uint16_t i = 0; i < sizeof(DATAEE_BLOCK); ++i )
    {
        *dest++ = DATAEE_ReadByte( DATAEE_BLOCK_BASE + i );
    }
}

void DataEE_Store( DATAEE_BLOCK* buffer )
{
    uint8_t* src = (uint8_t*)buffer;
    for ( uint16_t i = 0; i < sizeof(DATAEE_BLOCK); ++i )
    {
        DATAEE_WriteByte( DATAEE_BLOCK_BASE + i, *src++ );
    }
}

/**
 End of File
*/