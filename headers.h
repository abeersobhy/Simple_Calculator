/*
 * headers.h
 *
 * Created: 04/09/2021 10:42:40 ص
 *  Author: user
 */ 


#ifndef HEADERS_H_
#define HEADERS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 8000000UL
#define delay_ms(x) _delay_ms(x);

#define SET_BIT(x,b) ((x) |= (1 << b))
#define CLR_BIT(x,b) ((x) &= ~(1 << b))
#define TOGGLE_BIT(x,b) ((x) ^= (1 << b))
#define GET_BIT(x,b) (((x) >> b) & 1)

/*
#define DDRA_ *(volatile uint8_t*(3A))
#define PORTA_ *(volatile uint8_t*(3B))
#define PINA_ *(volatile uint8_t*(39))

#define DDRB_ *(volatile uint8_t*(37))
#define PORTB_ *(volatile uint8_t*(38))
#define PINB_ *(volatile uint8_t*(36))

#define DDRC_ *(volatile uint8_t*(34))
#define PORTC_ *(volatile uint8_t*(35))
#define PINC_ *(volatile uint8_t*(33))

#define DDRD_ *(volatile uint8_t*(31))
#define PORTD_ *(volatile uint8_t*(32))
#define PIND_ *(volatile uint8_t*(30))
*/

#endif /* HEADERS_H_ */