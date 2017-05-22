/**********************************************************************************/
/* Header file ADC.h                                                              */
/**********************************************************************************/
#ifndef _ADC_H_
#define _ADC_H_


/* declare global variable ADC_Data */
extern unsigned int ADC_Data;


/* declare initialisation function ADC_Init */
extern void ADC_Init(void);


/* declare interrupt service routine ADC_ISR */
extern __interrupt void ADC_ISR(void);



#endif _ADC_H_
