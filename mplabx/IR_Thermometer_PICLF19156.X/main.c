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
} SM_STATE;

typedef enum temp_mode {
    FAHRENHEIT,
    CELSIUS,
} TEMP_MODE;

typedef struct app_state {
    TEMP_MODE temp_mode;
    uint8_t temp_exists;
    float temp_C;
    int16_t ticks_remaining;
    SM_STATE next_sm_state;
} APP_STATE;

APP_STATE g_app_state;

// forward references
void App_Initialize( APP_STATE* app_state );
void App_GotoState( APP_STATE* app_state, SM_STATE );
void App_TimerClick(void);
void App_DisplayTemp( APP_STATE* app_state );
void App_RunST1( APP_STATE* app_state );
void App_RunST2( APP_STATE* app_state );
void App_RunST3( APP_STATE* app_state );
void App_RunST4( APP_STATE* app_state );
void App_RunST5( APP_STATE* app_state );
void App_RunST6( APP_STATE* app_state );
void App_RunST7( APP_STATE* app_state );
void App_RunST8( APP_STATE* app_state );
void App_RunST9( APP_STATE* app_state );
void App_RunST10( APP_STATE* app_state );

float Get_SupplyVoltage(void);
float Get_Temperature(void);

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
        
    App_Initialize( &g_app_state );
    TMR0_SetInterruptHandler( &App_TimerClick );
    
    while (1)
    {
        switch (g_app_state.next_sm_state)
        {
        default:
        case ST1:
            App_RunST1( &g_app_state );
            break;
        case ST2:
            App_RunST2( &g_app_state );
            break;
        case ST3:
            App_RunST3( &g_app_state );
            break;
        case ST4:
            App_RunST4( &g_app_state );
            break;
        case ST5:
            App_RunST5( &g_app_state );
            break;
        case ST6:
            App_RunST6( &g_app_state );
            break;
        case ST7:
            App_RunST7( &g_app_state );
            break;
        case ST8:
            App_RunST8( &g_app_state );
            break;
        case ST9:
            App_RunST9( &g_app_state );
            break;
        case ST10:
            App_RunST10( &g_app_state );
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

void App_Initialize( APP_STATE* app_state )
{
    App_GotoState( app_state, ST1 );
    // TODO: get temp mode from EEPROM
    app_state->temp_mode = FAHRENHEIT;
    app_state->temp_exists = 0;
    app_state->temp_C = 0.0f;
}

void App_GotoState( APP_STATE* app_state, SM_STATE sm_state )
{
    LED_SetLow();
    TMR0_StopTimer();
    app_state->next_sm_state = sm_state;
    app_state->ticks_remaining = 0;
}

void App_TimerClick(void)
{
    if ( g_app_state.ticks_remaining > 0 )
    {
        --g_app_state.ticks_remaining;
    }
}

void App_DisplayTemp( APP_STATE* app_state )
{
    if ( !app_state->temp_exists )
    {
        DISPLAY_Ready();
    }
    else
    {
        int16_t temp;
        if ( app_state->temp_mode == FAHRENHEIT )
        {
            temp = (int16_t)(10 * app_state->temp_C + 0.5);
        }
        else
        {
            temp = (int16_t)(10 * app_state->temp_C * 9 / 5 + 32.0 + 0.5);
        }
        DISPLAY_ShowNumber( temp, 1 );
    }
}

void App_RunST1( APP_STATE* app_state )
{
    // Display temperature or ready-indicator
    LCD_Enable();
    App_DisplayTemp( app_state );
    App_GotoState( app_state, ST2 );
}

void App_RunST2( APP_STATE* app_state )
{
    // Wait for all buttons released
    LED_SetHigh();
    while ( CLC1_OutputStatusGet() || CLC1_OutputStatusGet() )
    {
        SLEEP();
    }
    App_GotoState( app_state, ST3 );
}

void App_RunST3( APP_STATE* app_state )
{
    // Wait for button press or timeout
    LED_SetHigh();
    app_state->ticks_remaining = 300; // 30 secs
    TMR0_Reload();
    TMR0_StartTimer();
    while (1)
    {
        if ( CLC1_OutputStatusGet() )
        {
            App_GotoState( app_state, ST4 );
            return;
        }
        else if ( CLC2_OutputStatusGet() )
        {
            App_GotoState( app_state, ST8 );
            return;
        }
        else if ( app_state->ticks_remaining == 0 )
        {
            App_GotoState( app_state, ST7 );
            return;
        }
        else
        {
            SLEEP();
        }
    }
}

void App_RunST4( APP_STATE* app_state )
{
    // Measure Vdd, compare to threshold
    float vdd = Get_SupplyVoltage();
    if ( vdd < 2.65 )
    {
        App_GotoState( app_state, ST6 );
    }
    else
    {
        App_GotoState( app_state, ST5 );
    }
}

void App_RunST5( APP_STATE* app_state )
{
    // Capture temperature
    app_state->temp_C = Get_Temperature();
    app_state->temp_exists = 1;
    App_GotoState( app_state, ST1 );
}

void App_RunST6( APP_STATE* app_state )
{
    // Display low battery
    LCD_Enable();
    DISPLAY_BatteryLow();
    App_GotoState( app_state, ST2 );
}

void App_RunST7( APP_STATE* app_state )
{
    // Clear display
    DISPLAY_AllPixels_Off();
    LCD_Disable();
    App_GotoState( app_state, ST3 );
}

void App_RunST8( APP_STATE* app_state )
{
    // Display units
    LCD_Enable();
    DISPLAY_DIG1_Segments( DISPLAY_CharToSegments(' '));
    DISPLAY_DIG2_Segments( DISPLAY_CharToSegments(' '));
    DISPLAY_DIG3_Segments( DISPLAY_CharToSegments(' '));
    if ( app_state->temp_mode == FAHRENHEIT )
    {
        DISPLAY_DIG1_Segments( DISPLAY_CharToSegments('F'));
    }
    else
    {
        DISPLAY_DIG1_Segments( DISPLAY_CharToSegments('C'));
    }
    DISPLAY_DP1_Off();
    DISPLAY_DP2_Off();
    DISPLAY_DP3_Off();
    DISPLAY_COLON_Off();
    App_GotoState( app_state, ST9 );
}

void App_RunST9( APP_STATE* app_state )
{
    // Wait for button press or timeout
    LED_SetHigh();
    app_state->ticks_remaining = 50; // 5 secs
    TMR0_Reload();
    TMR0_StartTimer();
    while (1)
    {
        if ( CLC1_OutputStatusGet() )
        {
            App_GotoState( app_state, ST1 );
            return;
        }
        else if ( CLC2_OutputStatusGet() )
        {
            App_GotoState( app_state, ST10 );
            return;
        }
        else if ( app_state->ticks_remaining == 0 )
        {
            App_GotoState( app_state, ST1 );
            return;
        }
        else
        {
            SLEEP();
        }
    }
}

void App_RunST10( APP_STATE* app_state )
{
    // Toggle units
    if ( app_state->temp_mode == FAHRENHEIT )
    {
        app_state->temp_mode = CELSIUS;
    }
    else
    {
        app_state->temp_mode = FAHRENHEIT;
    }
    // TODO: save units to EEPROM
    App_GotoState( app_state, ST8 );
}

/**
 End of File
*/