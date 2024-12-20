#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <compat/twi.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/signal.h>
#include <stdlib.h>
#include <math.h>

// ultrasonic sensor
#define TRIGA 4		// 전면 Trigger 신호 (출력 = PE4)
#define ECHOA 5	// 전면 Echo 신호 (입력 = PE5)
#define TRIGB 6		// 내부 Trigger 신호 (출력 = PE6)
#define ECHOB 7	// 내부 Echo 신호 (입력 = PE7)
#define SOUND_VELOCITY 340UL    // 소리 속도 (m/sec)

// LCD
#define BYTE    unsigned char
#define WORD    unsigned int
volatile char data[100], LCD, lcd_addr;

/*
PORTB
PB6 > 서보 모터

PORTD
AT128 PD0 > LCD SCL
AT128 PD1 > LCD SDA

PORTE
PE4, PE5 > 전면 초음파 센서 Trigger(PE4), Echo(PE5)
PE6, PE7 > 내부 초음파 센서 Trigger(PE6), Echo(PE7)

PORTG
PG0 > R
PG1 > G
PG2 > B
*/

// ATmega128 initialize
void init_at128(void) {
	// port initialize
	DDRA = 0x0; DDRB = 0x0; DDRC = 0x0; DDRD = 0x0; DDRE = 0x0; DDRF = 0x0; DDRG = 0x00;
	PORTA = 0x0; PORTB = 0x0; PORTC = 0x0; PORTD = 0x0; PORTE = 0x0; PORTF = 0x0; PORTG = 0x0;
	init_printf();
}

// UART1 initialize
void uart1_init(void) {
	UCSR1B = 0x00;	// interrupt disable while setting baud rate
	UCSR1A = 0x00;	// Asynchronous Normal Mode
	UCSR1C = 0x06;	// 비동기 방식, No parity bit, 1 stop bit
	UBRR1L = 0x67;	// 16MHz에서 9,600 bps
	UBRR1H = 0x00;
	UCSR1B = 0x08;	// transmitter enable only
}

int uart1_putchar(char c) {
	UCSR1A = UCSR1A | 0x40;
	UDR1 = c;
	while(!(UCSR1A & 0x40));
}

int uart1_getchar(void) {
	char c;
	while(!(UCSR1A & 0x80));
	c = UDR1;
	uart1_putchar(c);
	return c;
}

void init_printf(void) {
	uart1_init();
	fdevopen(uart1_putchar, uart1_getchar);
}

void init_parts() {
	// ultrasoinc sensor
	DDRE |=_BV(4);		// 전면 PE4 set 1, trigger A
	DDRE &=~(_BV(5));	// 전면 PE5 set 0, echo A
	DDRE |=_BV(6);		// PE6 set 1, trigger B
	DDRE &=~(_BV(7));	// PE7 set 0, echo B

	// servo motor
	DDRB |= _BV(6);		// PB6 set 1, servo motor

	// LED 출력
	DDRG |= _BV(0);		// PB0 set 1, Red LED output
	DDRG |= _BV(1);		// PB1 set 1, Green LED output
	DDRG |= _BV(2);		// PB2 set 1, Blue LED output

	// Green LED on / Red, Blue LED off
	PORTG &= ~(_BV(0));	// Red
	PORTG |= _BV(1);	// Green
	PORTG &= ~(_BV(2));	// Blue

	// LCD(Initial TWI Peripheral)
	DDRD |= _BV(0);     // PD0 set 1, SCL output
	DDRD |= _BV(1);     // PD1 set 1, SDA output
	PORTD &= ~(_BV(0));	// Set PD0 SCL, PD1 SDA Low
	PORTD &= ~(_BV(1));
}

//////////////////////
//ultrasonic sencor1//
/////////////////////
unsigned int measure_distancemotor(void) {
	unsigned int distance;

	TCCR3B = 0x03;                  		// Timer/Counter1 클록 4us(64분주)
	PORTE &= ~(1<<TRIGA);		// Trig=LOW상태
	_delay_us(10);				// 10us동안 유지
	PORTE |= (1<<TRIGA);			// Trig=HIGH -> 거리 측정 명령 시작
	_delay_us(10);				// 10us동안 유지
	PORTE &= ~(1<<TRIGA);		// Trig=LOW -> 거리 측정 명령 끝
	while(!(PINE & (1<<ECHOA)));	// Echo=HIGH가 될 때까지 대기
	TCNT3 = 0x0000;				// Timer/Counter1 값 초기화
	while(PINE & (1<<ECHOA));		// Echo=LOW가 될 때까지 대기
	TCCR3B=0x00;				// Timer/Counter1 클록 정지(클록 입력 차단,CS11~CS10=000)
	distance = (unsigned int)(SOUND_VELOCITY * (TCNT3*4/2)/1000);	// 거리=속도x시간, 거리 단위는 1mm
	return distance;
}

//////////////////////
//ultrasonic sencor2//
/////////////////////
unsigned int measure_distanceled(void) {
	unsigned int distance;

	TCCR1B=0x03;				// Timer/Counter1 클록 4us(64분주)
	PORTE &= ~(1<<TRIGB);		// Trig=LOW상태
	_delay_us(10);				// 10us동안 유지
	PORTE |= (1<<TRIGB);			// Trig=HIGH -> 거리 측정 명령 시작
	_delay_us(10);				// 10us동안 유지
	PORTE &= ~(1<<TRIGB);		// Trig=LOW -> 거리 측정 명령 끝
	while(!(PINE & (1<<ECHOB)));	// Echo=HIGH가 될 때까지 대기
	TCNT1=0x0000;				// Timer/Counter1 값 초기화
	while(PINE & (1<<ECHOB));		// Echo=LOW가 될 때까지 대기
	TCCR1B=0x00;				// Timer/Counter1 클록 정지(클록 입력 차단,CS11~CS10=000)
	distance = (unsigned int)(SOUND_VELOCITY * (TCNT1*4/2)/1000);	// 거리=속도x시간, 거리 단위는 1mm
	return distance;
}


//////////////////////
/////servo motor/////
/////////////////////
void controlSERVO(distancemotor) {
	int i;

	if (distancemotor < 100 ) {
		LCD_string(0x84," OPEN");	// lcd 문자출력
        	for(i=0; i<50; i++) {
			PORTB |=_BV(6);
			_delay_us(2500);
			PORTB &=~(_BV(6));
			_delay_us(17500);
		}
		printf("DistanceMotor: %d mm\n\r", distancemotor);
		_delay_ms(3000);
	}

	else {
		LCD_string(0x84,"CLOSE");	// lcd 문자출력
		for(i = 0; i < 50; i++){
			PORTB |=_BV(6);
			_delay_us(500);
			PORTB &=~(_BV(6));
			_delay_us(19500);
		}
		printf("DistanceMotor: %d mm\n\r", distancemotor);
	}
}

//////////////////////
/////////LED/////////
/////////////////////
void controlLEDs(distanceled) {
	if (distanceled < 60) {
		LCD_string(0xC3,"    RED");
        	// Red LED on Green, Blue LED off
        	PORTG |= _BV(0);	// Red
        	PORTG &= ~(_BV(1));	// Green
        	PORTG &= ~(_BV(2));	// Blue
        	printf("Red led on, LED Distance: %d\n\r",distanceled);
        	_delay_ms(100);
	}

	else if (distanceled >= 60 && distanceled <= 100) {
		LCD_string(0xC4,"  BLUE");
		// Blue LED on Red, Green LED off
		PORTG &= ~(_BV(0));	// Red
		PORTG &= ~(_BV(1));	// Green
		PORTG |= _BV(2);	// Blue
		printf("Blue led on, LED Distance: %d\n\r",distanceled);
		_delay_ms(100);
	}

	else if (distanceled > 100) {
		LCD_string(0xC5,"GREEN");
		// Green LED on Red, Blue LED off
        	PORTG &= ~(_BV(0));	// Red
		PORTG |= _BV(1);	// Green
		PORTG &= ~(_BV(2));	// Blue
		printf("Green led on, LED Distance: %d\n\r",distanceled);
		_delay_ms(100);
	}
}

//////////////////////
/////LCD 1602//////
/////////////////////
char getch(void) {
	BYTE data;

	loop_until_bit_is_set(UCSR0A,7);
	data = UDR0;
	UCSR0A |= 0x80;   //Clear RXC0
	return(data);
}

void putch(BYTE data) {
	loop_until_bit_is_set(UCSR0A,5);
	UDR0 = data;
	UCSR0A |= 0x20;   //Clear UDRE0
}

void twi_write(unsigned char address,unsigned char data) {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //START

	while(!(TWCR & (1<<TWINT)));          //TWINT flag 기다림
	while((TWSR&0xF8) != 0x08);             //START 상태(08) 기다림

	TWDR = (address << 1) & 0xfe;         // 7 bit address + 0(write)
	TWCR = (1<<TWINT)|(1<<TWEN);     //전송

	while(!(TWCR & (1<<TWINT)));
	while((TWSR&0xF8) != 0x18);             //SLA+W ACK 상태(18) 기다림

	TWDR = data;            //data
	TWCR = (1<<TWINT)|(1<<TWEN);     //전송

	while(!(TWCR & (1<<TWINT)));
	while((TWSR&0xF8) != 0x28);            //Data ACK 상태(28) 기다림

	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN); 	//STOP
}



// write a command(instruction) to text LCD
void LCD_command(BYTE command) {
	LCD = (command & 0b11110000) | 0b00001100;	// MSB 4 bit, command mode, write mode, enable high
	twi_write(lcd_addr, LCD);
	_delay_us(50);
	LCD &= ~(_BV(2));		// enable toggle
	twi_write(lcd_addr, LCD);
	_delay_us(50);

	LCD = (command & 0b00001111) ;
	LCD = LCD << 4;
	LCD = LCD | 0b00001100;	// LSB 4 bit, command mode, write mode, enable high
	twi_write(lcd_addr, LCD);
	_delay_us(50);
	LCD &= ~(_BV(2));		// enable toggle
	twi_write(lcd_addr, LCD);
	_delay_us(50);

	_delay_ms(1);			// LCD 제어를 위해 시간 지연 필요함
}

// display a character on text LCD
void LCD_data(BYTE data) {
	LCD = (data & 0b11110000) | 0b00001101;	// MSB 4 bit, data mode, write mode, enable high
	twi_write(lcd_addr, LCD);
	_delay_us(50);
	LCD &= ~(_BV(2));               // enable toggle
	twi_write(lcd_addr, LCD);
	_delay_us(50);

	LCD = (data & 0b00001111) ;
	LCD = LCD << 4;
	LCD = LCD | 0b00001101;	// LSB 4 bit, data mode, write mode, enable high
	twi_write(lcd_addr, LCD);
	_delay_us(50);
	LCD &= ~(_BV(2));		// enable toggle
	twi_write(lcd_addr, LCD);
	_delay_us(50);

	_delay_ms(1);			// LCD 제어를 위해 시간 지연 필요함
}

// display a string on LCD
void LCD_string(BYTE command, BYTE *string) {
	LCD_command(command);	// start position of string

	while(*string != '\0')		// display string
	{
		LCD_data(*string);
		string++;
	}
}

// LCD 1602 initialize for nibble operation
void LCD_nibble(lcd_addr) {
	_delay_ms(20);
	twi_write(lcd_addr, 0b00111100);    //command mode, write mode, enable high
	_delay_us(50);
	twi_write(lcd_addr, 0b00111000);    // toggle e
	_delay_us(50);

	_delay_ms(4);
	twi_write(lcd_addr, 0b00111100);    //command mode, write mode, enable high
	_delay_us(50);
	twi_write(lcd_addr, 0b00111000);    // toggle e
	_delay_us(50);

	_delay_ms(1);
	twi_write(lcd_addr, 0b00111100);    //command mode, write mode, enable high
	_delay_us(50);
	twi_write(lcd_addr, 0b00111000);    // toggle e
	_delay_us(50);

	_delay_ms(4);
	twi_write(lcd_addr, 0b00101100);    // command mode, write mode, enable high
	_delay_us(50);
	twi_write(lcd_addr, 0b00101000);    // toggle e
	_delay_us(50);
	twi_write(lcd_addr, 0b00101100);
	_delay_us(50);
}

// initialize text LCD module
void LCD_initialize(void) {
	LCD_command(0x3c);	// LCD function set(8 bit, 16x2 line, 5x7 dot)
	_delay_ms(2);
	LCD_command(0x08);	// LCD display control(display ON, cursor OFF, blink OFF)
	_delay_ms(2);
	LCD_command(0x01);	// clear display
	_delay_ms(2);
	LCD_command(0x06);	// LCD entry mode set(increment, not shift)
	_delay_ms(2);
	LCD_command(0x02);	// Retrun Home
	_delay_ms(2);
}

///////////////////////////////////////////////////////////////////////////////////////
int main(void) {
	unsigned int distancemotor, distanceled;

	// MCU initialize
	MCUCR = 0x00;	// enable external memory and I/O disenable
	XMCRA = 0x00;	// 0x1100-0xFFFF=1 wait
	XMCRB = 0x00;	// disenable bus keeper
	_delay_ms(5);

	init_at128();		// ATmega128 initialize
	_delay_ms(5);

	init_parts();		// parts initialize
	_delay_ms(5);

	lcd_addr = 0x27;

	// Initial TWI Peripheral
	TWSR = 0x01;	// Select Prescaler of 4
	TWBR = 18;	// SCL frequency = 16000000 / (16 + 2 * 18 * 4) = 100 khz

	//LCD Initialize
	LCD_nibble(lcd_addr);
	LCD_initialize();

	printf("\n\r");
	printf("initialize finished\n\r");

	LCD_command(0x01);
	_delay_ms(1000);
	LCD_string(0x80,"A_11 START");
	_delay_ms(1000);
	LCD_command(0x01);

	while (1) {
		distancemotor = measure_distancemotor();	// measure ultrasonic sencor1
		distanceled = measure_distanceled();		// measure ultrasonic sencor2

 	  	controlSERVO(distancemotor);			// control servo
		controlLEDs(distanceled);				// control LED
    	}

	return 0;
}
