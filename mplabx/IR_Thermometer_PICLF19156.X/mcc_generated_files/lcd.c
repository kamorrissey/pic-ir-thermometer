/**
  LCD Generated Driver File
  
  @Company
    Microchip Technology Inc.

  @File Name
    lcd.c

  @Summary
    This is the generated driver implementation file for the LCD driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides implementations for driver APIs for LCD.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16LF19156
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "lcd.h"

/**
  Section: LCD APIs
*/

void LCD_Initialize(void)
{
    // Disable module before configuring
    LCDCONbits.LCDEN = 0;

    // set the LCD to the options selected in the User Interface
    // LP 1:8; WFT Type-A waveform; 
    LCDPS = 0x07;
    
    // LCDCST Max contrast (Min Resistance); 
    LCDREF = 0x00;
    
    // LRLAP disabled; LRLBP Low; LCDIRI disabled; LRLAT Always B Power mode; 
    LCDRL = 0x10;
    
    // BIAS 3.00V; EN5V disabled; LPEN disabled; 
    LCDVCON1 = 0x02;
    
    // CPWDT disabled; LCDVSRC Internal Resistor Ladder + Vdd for VLCD3; 
    LCDVCON2 = 0x82;
    
    //SegCom Data Registers
	LCDDATA0 = 0x00;
	LCDDATA1 = 0x00;
	LCDDATA2 = 0x00;
	LCDDATA6 = 0x00;
	LCDDATA7 = 0x00;
	LCDDATA8 = 0x00;
	LCDDATA12 = 0x00;
	LCDDATA13 = 0x00;
	LCDDATA14 = 0x00;
	LCDDATA18 = 0x00;
	LCDDATA19 = 0x00;
	LCDDATA20 = 0x00;
	LCDDATA24 = 0x00;
	LCDDATA25 = 0x00;
	LCDDATA26 = 0x00;
	LCDDATA30 = 0x00;
	LCDDATA31 = 0x00;
	LCDDATA32 = 0x00;
	LCDDATA36 = 0x00;
	LCDDATA37 = 0x00;
	LCDDATA38 = 0x00;
	LCDDATA42 = 0x00;
	LCDDATA43 = 0x00;
	LCDDATA44 = 0x00;
    
	//Enable used segments
	LCDSE0 = 0xCF;
	LCDSE1 = 0x03;
	LCDSE2 = 0x00;
	LCDSE3 = 0x00;
	LCDSE4 = 0x00;
	LCDSE5 = 0x00;
	
    // CS LFINTOSC; SLPEN enabled; WERR No LCD Write Error; LMUX 1/4 COM(3:0); LCDEN enabled; 
    LCDCON = 0x84;
	
}

void LCD_Enable (void)
{
    LCDCONbits.LCDEN = 1;
}

void LCD_Disable (void)
{
    LCDCONbits.LCDEN = 0;    
}

void LCD_EnableSleepMode (void)
{
    LCDCONbits.SLPEN = 1;
}

void LCD_DisableSleepMode (void) 
{
    LCDCONbits.SLPEN = 0;    
}

void LCD_SetContrast (unsigned int value)
{
    LCDREFbits.LCDCST = value;
}

void LCD_SetIntervalAPowerMode (unsigned int value)
{
    LCDRLbits.LRLAP = value;      
}

void LCD_SetIntervalBPowerMode (unsigned int value)
{
    LCDRLbits.LRLBP = value;      
}

void LCD_SetPowerDistribution (unsigned int value)
{
    LCDRLbits.LRLAT = value;       
}

bool LCD_IsActive (void)
{
    return LCDPSbits.LCDA;
}

void LCD_DisplayOn_DIG1_SYM00Num()
{
	DIG1_SYM00AON;DIG1_SYM00BON;DIG1_SYM00CON;DIG1_SYM00DON;DIG1_SYM00EON;DIG1_SYM00FON;DIG1_SYM00GON;
}

void LCD_DisplayOff_DIG1_SYM00Num()
{
	DIG1_SYM00AOFF;DIG1_SYM00BOFF;DIG1_SYM00COFF;DIG1_SYM00DOFF;DIG1_SYM00EOFF;DIG1_SYM00FOFF;DIG1_SYM00GOFF;
}

void LCD_DIG1_SYM00Num (unsigned char num) 
{
    switch (num)
    {
        case 0: DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GOFF;  break;
        case 1: DIG1_SYM00AOFF;  DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DOFF;  DIG1_SYM00EOFF;  DIG1_SYM00FOFF;  DIG1_SYM00GOFF;  break;
        case 2: DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00COFF;  DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FOFF;  DIG1_SYM00GON;   break;
        case 3: DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EOFF;  DIG1_SYM00FOFF;  DIG1_SYM00GON;   break;
        case 4: DIG1_SYM00AOFF;  DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DOFF;  DIG1_SYM00EOFF;  DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 5: DIG1_SYM00AON;   DIG1_SYM00BOFF;  DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EOFF;  DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 6: DIG1_SYM00AON;   DIG1_SYM00BOFF;  DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 7: DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DOFF;  DIG1_SYM00EOFF;  DIG1_SYM00FOFF;  DIG1_SYM00GOFF;  break;
        case 8: DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EON;   DIG1_SYM00FON;   DIG1_SYM00GON;   break;
        case 9: DIG1_SYM00AON;   DIG1_SYM00BON;   DIG1_SYM00CON;   DIG1_SYM00DON;   DIG1_SYM00EOFF;  DIG1_SYM00FON;   DIG1_SYM00GON;   break;

        default: DIG1_SYM00AOFF; DIG1_SYM00BOFF; DIG1_SYM00COFF; DIG1_SYM00DOFF; DIG1_SYM00EOFF; DIG1_SYM00FOFF; DIG1_SYM00GOFF;
    }    
}

void LCD_DisplayOn_DIG2_SYM01Num()
{
	DIG2_SYM01AON;DIG2_SYM01BON;DIG2_SYM01CON;DIG2_SYM01DON;DIG2_SYM01EON;DIG2_SYM01FON;DIG2_SYM01GON;
}

void LCD_DisplayOff_DIG2_SYM01Num()
{
	DIG2_SYM01AOFF;DIG2_SYM01BOFF;DIG2_SYM01COFF;DIG2_SYM01DOFF;DIG2_SYM01EOFF;DIG2_SYM01FOFF;DIG2_SYM01GOFF;
}

void LCD_DIG2_SYM01Num (unsigned char num) 
{
    switch (num)
    {
        case 0: DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GOFF;  break;
        case 1: DIG2_SYM01AOFF;  DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DOFF;  DIG2_SYM01EOFF;  DIG2_SYM01FOFF;  DIG2_SYM01GOFF;  break;
        case 2: DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01COFF;  DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FOFF;  DIG2_SYM01GON;   break;
        case 3: DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EOFF;  DIG2_SYM01FOFF;  DIG2_SYM01GON;   break;
        case 4: DIG2_SYM01AOFF;  DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DOFF;  DIG2_SYM01EOFF;  DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 5: DIG2_SYM01AON;   DIG2_SYM01BOFF;  DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EOFF;  DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 6: DIG2_SYM01AON;   DIG2_SYM01BOFF;  DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 7: DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DOFF;  DIG2_SYM01EOFF;  DIG2_SYM01FOFF;  DIG2_SYM01GOFF;  break;
        case 8: DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EON;   DIG2_SYM01FON;   DIG2_SYM01GON;   break;
        case 9: DIG2_SYM01AON;   DIG2_SYM01BON;   DIG2_SYM01CON;   DIG2_SYM01DON;   DIG2_SYM01EOFF;  DIG2_SYM01FON;   DIG2_SYM01GON;   break;

        default: DIG2_SYM01AOFF; DIG2_SYM01BOFF; DIG2_SYM01COFF; DIG2_SYM01DOFF; DIG2_SYM01EOFF; DIG2_SYM01FOFF; DIG2_SYM01GOFF;
    }    
}

void LCD_DisplayOn_DIG3_SYM02Num()
{
	DIG3_SYM02AON;DIG3_SYM02BON;DIG3_SYM02CON;DIG3_SYM02DON;DIG3_SYM02EON;DIG3_SYM02FON;DIG3_SYM02GON;
}

void LCD_DisplayOff_DIG3_SYM02Num()
{
	DIG3_SYM02AOFF;DIG3_SYM02BOFF;DIG3_SYM02COFF;DIG3_SYM02DOFF;DIG3_SYM02EOFF;DIG3_SYM02FOFF;DIG3_SYM02GOFF;
}

void LCD_DIG3_SYM02Num (unsigned char num) 
{
    switch (num)
    {
        case 0: DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GOFF;  break;
        case 1: DIG3_SYM02AOFF;  DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DOFF;  DIG3_SYM02EOFF;  DIG3_SYM02FOFF;  DIG3_SYM02GOFF;  break;
        case 2: DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02COFF;  DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FOFF;  DIG3_SYM02GON;   break;
        case 3: DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EOFF;  DIG3_SYM02FOFF;  DIG3_SYM02GON;   break;
        case 4: DIG3_SYM02AOFF;  DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DOFF;  DIG3_SYM02EOFF;  DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 5: DIG3_SYM02AON;   DIG3_SYM02BOFF;  DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EOFF;  DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 6: DIG3_SYM02AON;   DIG3_SYM02BOFF;  DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 7: DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DOFF;  DIG3_SYM02EOFF;  DIG3_SYM02FOFF;  DIG3_SYM02GOFF;  break;
        case 8: DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EON;   DIG3_SYM02FON;   DIG3_SYM02GON;   break;
        case 9: DIG3_SYM02AON;   DIG3_SYM02BON;   DIG3_SYM02CON;   DIG3_SYM02DON;   DIG3_SYM02EOFF;  DIG3_SYM02FON;   DIG3_SYM02GON;   break;

        default: DIG3_SYM02AOFF; DIG3_SYM02BOFF; DIG3_SYM02COFF; DIG3_SYM02DOFF; DIG3_SYM02EOFF; DIG3_SYM02FOFF; DIG3_SYM02GOFF;
    }    
}

void LCD_DisplayOn_DIG4_SYM03Num()
{
	DIG4_SYM03AON;DIG4_SYM03BON;DIG4_SYM03CON;DIG4_SYM03DON;DIG4_SYM03EON;DIG4_SYM03FON;DIG4_SYM03GON;
}

void LCD_DisplayOff_DIG4_SYM03Num()
{
	DIG4_SYM03AOFF;DIG4_SYM03BOFF;DIG4_SYM03COFF;DIG4_SYM03DOFF;DIG4_SYM03EOFF;DIG4_SYM03FOFF;DIG4_SYM03GOFF;
}

void LCD_DIG4_SYM03Num (unsigned char num) 
{
    switch (num)
    {
        case 0: DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GOFF;  break;
        case 1: DIG4_SYM03AOFF;  DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DOFF;  DIG4_SYM03EOFF;  DIG4_SYM03FOFF;  DIG4_SYM03GOFF;  break;
        case 2: DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03COFF;  DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FOFF;  DIG4_SYM03GON;   break;
        case 3: DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EOFF;  DIG4_SYM03FOFF;  DIG4_SYM03GON;   break;
        case 4: DIG4_SYM03AOFF;  DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DOFF;  DIG4_SYM03EOFF;  DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 5: DIG4_SYM03AON;   DIG4_SYM03BOFF;  DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EOFF;  DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 6: DIG4_SYM03AON;   DIG4_SYM03BOFF;  DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 7: DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DOFF;  DIG4_SYM03EOFF;  DIG4_SYM03FOFF;  DIG4_SYM03GOFF;  break;
        case 8: DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EON;   DIG4_SYM03FON;   DIG4_SYM03GON;   break;
        case 9: DIG4_SYM03AON;   DIG4_SYM03BON;   DIG4_SYM03CON;   DIG4_SYM03DON;   DIG4_SYM03EOFF;  DIG4_SYM03FON;   DIG4_SYM03GON;   break;

        default: DIG4_SYM03AOFF; DIG4_SYM03BOFF; DIG4_SYM03COFF; DIG4_SYM03DOFF; DIG4_SYM03EOFF; DIG4_SYM03FOFF; DIG4_SYM03GOFF;
    }    
}

// end of file