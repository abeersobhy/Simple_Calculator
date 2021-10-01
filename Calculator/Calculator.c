/*
 * calculator.c
 *  Author: Abeer Sobhy.
 */ 
#include "../headers.h"
#include "../LCD/LCD.h"
#include "Calculator.h"
volatile int8_t num_index = 1;
volatile int8_t  i = 0 , j = 0 , op1 , digit = 0 , flag = 0;
volatile double num[10] , result ;
#define CALC_RESTART()   digit = 0 ; j = 0 ; flag = 0; num_index = 1;\
						 LCD_Write_Command(LCD_Clear); 
void Calc_start(void)
{
	LCD_Write_Command(0x85); /*Set cursor at coloum 5 in row number zero.*/
	LCD_Write_String("Welcome"); /*Display welcome on the LCD for 500 ms.*/
	delay_ms(500);
	LCD_Write_Command(LCD_Clear); /*Clear the LCD.*/
	LCD_Write_Command(0x83); /*Set cursor at coloum 3 in row number zero.*/
	LCD_Write_String("Enter your");  /*Display the string on the LCD for 1000 ms.*/
	LCD_Write_Command(0xc3); /*Set cursor at coloum 3 in row number one.*/
	LCD_Write_String("Operation"); /*Display the string on the LCD for 1000 ms.*/
	delay_ms(500);
	LCD_Write_Command(LCD_Clear); /*Clear the LCD.*/
}
void Calc_Restart(void)
{
	CALC_RESTART(); 
}
void Calc_store_numbers(int8_t char_)
{
	switch(char_)
	{
		case 0 ... 9 :
		LCD_Write_Number(char_); /*Print the pressed number then wait for 300 ms.*/
		delay_ms(300);
		digit++; /*Increment the number of digits by one.*/
    	switch(digit) /*Check the position of the this digit.*/
    	{
			case 1 : /*Decimal number.*/
			if(op1 != '.')
			{
				num[j] = char_;
			}
			else /*Float number.*/
			{
				num[j] += (char_/10);
			}
			break;
			case 2 ... 4 :
			if(op1 != '.') /*Decimal number.*/
			{
				num[j] = num[j]*10 + char_;
			}
			else /*Float numbers.*/
			{
				switch(digit)
				{
					case 2: num[j] += (char_/100); break;
					case 3: num[j] += (char_/1000); break;
					case 4: num[j] += (char_/10000); break;
				}
			}
			break;
    	}
		break;
		case '+' : digit = 0; j++; num[j++] = '+'; LCD_Write_String(" + "); delay_ms(300); break; /*Store the operand , be ready to receive a new char_ "digit = 0 , j++" */
        case '-' : digit = 0; j++; num[j++] = '-'; LCD_Write_String(" - "); delay_ms(300); break; /*Store the operand , be ready to receive a new char_ "digit = 0 , j++" */
	    case '*' : digit = 0; j++; num[j++] = '*'; LCD_Write_String(" * "); delay_ms(300); break; /*Store the operand , be ready to receive a new char_ "digit = 0 , j++" */
        case '/' : digit = 0; j++; num[j++] = '/'; LCD_Write_String(" / "); delay_ms(300); break; /*Store the operand , be ready to receive a new char_ "digit = 0 , j++" */
        case '%' : digit = 0; j++; num[j++] = '%'; LCD_Write_String(" % "); delay_ms(300); break; /*Store the operand , be ready to receive a new char_ "digit = 0 , j++" */
        case '.' : digit = 0; op1 = char_; LCD_Write_Char('.'); delay_ms(300); break; 	 /*Be ready to receive a float number*/
	}
}
void Calc_store_operand(int8_t char_)
{
	switch(char_)
	{
		case '=':
		LCD_Write_String(" =");
		delay_ms(300);
		result = Calc_op();
		if(flag != 1) /*No syntax calculation error.*/
		{
			LCD_Write_Command(LINE_TWO);
			LCD_Display_Number(result);
			delay_ms(300);
		}
		else /*There is an error.*/
		{
			goto syntax_error;
		}
		break;
		case 'C': Calc_Restart(); break; /*Restart the calculator.*/
		syntax_error: LCD_Write_Command(LCD_Clear); LCD_Write_String("Wrong entry"); delay_ms(300); Calc_Restart(); /*print the error message restart the calculator.*/
	}
}
double Calc_op(void)
{
	/*Calculate all operations of '*' & '/' .*/ 
	num_index = 1;
	while(num_index <= j)   
	{
		if(num[num_index] == '*')
		{
			num[num_index-1] *= num[num_index+1]; /*Calculate the operation.*/
			for(int8_t k = num_index ; k <= j ; k++) /*Delete the operand after multiplication.*/
			{
				num[k] = num[k+1];
			}
			j--; /*Decrease the number of elements of the array of num */
			for(int8_t k = num_index ; k <= j ; k++) /*Delete the number after the operand .*/
			{
				num[k] = num[k+1];
			}
			j--; /*Decrease the number of elements of the array of num */
		}
		else if(num[num_index] == '/')
		{
			if(num[num_index+1] == 0) /*There is a syntax error (number / 0).*/
			{
				flag = 1;
				return 0;
			}
			else 
			{
				num[num_index-1] /= (float)num[num_index+1]; /*Calculate the operation.*/
				for(int8_t k = num_index ; k <= j ; k++) /*Delete the operand after division.*/
				{
					num[k] = num[k+1];
				}
				j--; /*Decrease the number of elements of the array of num */
				for(int8_t k = num_index ; k <= j ; k++) /*Delete the number after the operand .*/
				{
					num[k] = num[k+1];
				}
				j--; /*Decrease the number of elements of the array of num */
			}
		}
		else /*No equivalent operand*/
		{
			num_index += 2; /*Move to  the second operand*/ 
		}
	}         
	num_index = 1;
	/*Calculate all operations of '+' & '-'.*/
	while(num_index <= j)
    {
		if(num[num_index] == '+')
		{
			num[num_index-1] += num[num_index+1]; /*Calculate the operation.*/
			for(int8_t k = num_index ; k <= j ; k++) /*Delete the operand after addition.*/
			{
				num[k] = num[k+1];
			}
			j--; /*Decrease the number of elements of the array of num */
			for(int8_t k = num_index ; k <= j ; k++) /*Delete the second number after the operand .*/
			{
				num[k] = num[k+1];
			}
			j--; /*Decrease the number of elements of the array of num */
		}
		else if(num[num_index] == '-')
		{
			num[num_index-1] -= num[num_index+1]; /*Calculate the operation.*/
			for(int8_t k = num_index ; k <= j ; k++) /*Delete the operand after subtraction.*/
			{
				num[k] = num[k+1];
			}
			j--; /*Decrease the number of elements of the array of num */
			for(int8_t k = num_index ; k <= j ; k++) /*Delete the second number after the operand .*/
			{
				num[k] = num[k+1];
			}
			j--; /*Decrease the number of elements of the array of num */	
		}
		else
		{
			num_index += 2;
		}
	}
    return num[0];/*Result of all operations should be here (the first element in the array called num[]).*/
}