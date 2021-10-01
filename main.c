/*
 * main.c
 * Author : Abeer Sobhy.
 */ 
#include "headers.h"
#include "LCD/LCD.h"
#include "Keypad/Keypad.h"
#include "Calculator/Calculator.h"
volatile int8_t  char_;
int main(void)
{
	LCD_Inti();
	Keypad_Inti();
	Calc_start(); /*View Start Window.*/
	while(1)
	{
		char_ = Keypad_Read(); /*Get the pressed key.*/
		if(char_ != -1) /*There is a pressed key.*/
		{
			if((char_ == '=') || (char_ == 'C')) /*The pressed key is a number*/
			{
				Calc_store_operand(char_); /*Store the character.*/
			} 
			else /*the pressed key is an operand or character.*/
			{
				Calc_store_numbers(char_); /*Store the number.*/
			}
		}
	}
}