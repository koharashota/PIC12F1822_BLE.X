
#include <xc.h>

#define _XTAL_FREQ (8000000)

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memeory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = HI        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), high trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

void pin_init()
{
  OSCCON = 0b01110000;      // 8MHz
  ANSELA = 0b00000000;
  ANSELB = 0b00000000;
  TRISA = 0b00000001;       //A0ポートを利用
  TRISB = 0b00000000;
  PORTA = 0b00000000;
  PORTB = 0b00000000;

  //9600bbsに設定
  SPBRG = 12;

  //UART送信設定
  TXEN = 1;
  SYNC = 0;
  SPEN = 1;
}

void main(void)
{
  __delay_ms(100);             
  pin_init();                //I/Oの初期化

  while(1)
  {
      if(RA0 == 1) {         //RA0がHIGH(通電)なら1を送る
      while(TXIF == 0){}
      TXREG = 1;
      __delay_ms(1000);
      } else {               //RA0がLOWなら0を送る
      while(TXIF == 0){}
      TXREG = 0;
      __delay_ms(1000);
      }
  }
}
