/***************************************************************************
 * External Device Address Mapping.                                        *
 ***************************************************************************/
#define EX_LCD_DATA	(*(volatile unsigned char *)0x8000)		// text LCD / graphic LCD 데이터
#define EX_LCD_CONTROL	(*(volatile unsigned char *)0x8001)	// text LCD / graphic LCD 제어명령
#define EX_SS_DATA	(*(volatile unsigned char *)0x8002)		// 7 segment LED 데이터
#define EX_SS_SEL	(*(volatile unsigned char *)0x8003)		// 7 segment LED 자리 선택
#define EX_DM_SEL	(*(volatile unsigned int  *)0x8004)		// dot matrix select
#define EX_DM_DATA	(*(volatile unsigned int  *)0x8006)		// dot matrix 데이터
#define EX_LED		(*(volatile unsigned char *)0x8008)		// 8 LEDs output
#define EX_STEPPING	(*(volatile unsigned char *)0x8009)		// step motor
#define EX_DCMOTOR	(*(volatile unsigned char *)0x800A)		// DC motor
#define EX_SERVO	(*(volatile unsigned char *)0x800B)		// servo motor


/***************************************************************************
 * Trainning Kit Initialize                                                *
 ***************************************************************************/
void init_kt_m128(void)
{
	MCUCR = MCUCR | 0x80;		// external address/data mode

    // port initialize
 	DDRA=0x0; DDRB=0x0; DDRC=0x0; DDRD=0x0; DDRE=0x0; DDRF=0x0; DDRG=0x00;
	PORTA=0x0; PORTB=0x0; PORTC=0x0; PORTD=0x0; PORTE=0x0; PORTF=0x0; PORTG=0x0; 

	EX_SS_DATA=0x00;			// external device initialize
	EX_SS_SEL=0x00;
	EX_DM_SEL=0x00;
	EX_DM_DATA=0x00;
	EX_LED=0x00;
	EX_STEPPING=0x00;

	init_printf();		// printf() 사용 선언
}

/***************************************************************************
 * printf declear                                                          *
 ***************************************************************************/
//UART1 initialize
// desired baud rate: 19200
// char size: 8 bit
// parity: Disabled
void uart1_init(void)
{
	UCSR1B = 0x00; // interrupt disable while setting baud rate
	UCSR1A = 0x00; // Asynchronous Normal Mode
	UCSR1C = 0x06; // 비동기 방식, No parity bit, 1 stop bit 
	UBRR1L = 0x33;  // set baud rate 0x67 for 9600bps, 0x33 for 19200, 0x19 for 38400,  0x6 for 115200bps
	UBRR1H = 0x00; // 
	UCSR1B = 0x08; // transmitter enable only
}

//int putchar(char c)
int uart1_putchar(char c)
{
	UCSR1A = UCSR1A | 0x40;
	UDR1 = c;
	while(!(UCSR1A & 0x40));
}

//int getchar(void)
int uart1_getchar(void)
{
	char c;
	while(!(UCSR1A & 0x80));
	c = UDR1;
	uart1_putchar(c);
	return c;
}

void init_printf(void)
{
	uart1_init();
	fdevopen(uart1_putchar, uart1_getchar);
}

