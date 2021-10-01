/*
 * Calculator.h
 *  Author: Abeer Sobhy.
 */ 

#ifndef CALCULATOR_H_
#define CALCULATOR_H_
#include "../headers.h"
/*****************************************************************************
* Function Name: Calc_start.
* Purpose      : Display some words on the LCD.
* Parameters   : void
* Return value : void
*****************************************************************************/
void Calc_start(void);
/*****************************************************************************
* Function Name: Calc_Restart.
* Purpose      : Restart the calculator.
* Parameters   : void
* Return value : void
*****************************************************************************/
void Calc_Restart(void);
/*****************************************************************************
* Function Name: Calc_op.
* Purpose      : Calculate multiple operation .
* Parameters   : void
* Return value : result of the operations (double).
*****************************************************************************/
double Calc_op(void);
/*****************************************************************************
* Function Name: Calc_store_numbers.
* Purpose      : Store numbers .
* Parameters   : number from 0 to 9 (int8_t char).
* Return value : void
*****************************************************************************/
void Calc_store_numbers(int8_t char_);
/*****************************************************************************
* Function Name: Calc_store_operand.
* Purpose      : Store operand or character and calculate operations if it was '='.
* Parameters   : character or operand (int8_t char)
* Return value : void
*****************************************************************************/
void Calc_store_operand(int8_t char_);
#endif /* CALCULATOR_H_ */