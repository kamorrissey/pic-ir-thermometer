#include <xc.h>

#include "mcc_generated_files/mcc.h"
#include "pmd.h"

void PMD_UnusedDisable(void)
{
    PMD0bits.ACTMD = 1;
    // PMD0bits.FVRMD = 1;
    PMD0bits.IOCMD = 1;
    // PMD0bits.NVMMD = 1;
    // PMD0bits.SYSCMD = 1;
    
    // PMD1bits.TMR0MD = 1;
    // PMD1bits.TMR1MD = 1;
    // PMD1bits.TMR2MD = 1;
    // PMD1bits.TMR4MD = 1;

    // PMD2bits.ADCMD = 1;
    PMD2bits.CMP1MD = 1;
    PMD2bits.CMP2MD = 1;
    PMD2bits.DACMD = 1;
    PMD2bits.RTCCMD = 1;
    PMD2bits.ZCDMD = 1;
    
    PMD3bits.CCP1MD = 1;
    PMD3bits.CCP2MD = 1;
    PMD3bits.CCP3MD = 1; // PWM3
    PMD3bits.CCP4MD = 1; // PWM4
    
    PMD4bits.CWG1MD = 1;
    // PMD4bits.MSSP1MD = 1;
    PMD4bits.UART1MD = 1;
    PMD4bits.UART2MD = 1;
    
    // PMD5bits.CLC1MD = 1;
    // PMD5bits.CLC2MD = 1;
    // PMD5bits.CLC3MD = 1;
    // PMD5bits.CLC4MD = 1;
    // PMD5bits.LCDMD = 1;
    // PMD5bits.SMT1MD = 1;
}

void PMD_Sleep(void)
{
    FVREN = 0;
}

void PMD_Wake(void)
{
    FVREN = 1;
}
