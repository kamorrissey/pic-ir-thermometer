/* 
 * File:   pmd.h
 * Author: kamor
 *
 * Created on March 10, 2022, 6:39 PM
 */

#ifndef PMD_H
#define	PMD_H

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Disable all unused peripheral modules.
 */
void PMD_UnusedDisable(void);

/**
 * Disable all used peripheral modules not needed in sleep mode.
 */
void PMD_Sleep(void);

/**
 * Enable and reinitialize all sleeping peripherals.
 */
void PMD_Wake(void);


#ifdef	__cplusplus
}
#endif

#endif	/* PMD_H */

