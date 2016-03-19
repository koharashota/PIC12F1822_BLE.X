/*
* File:   main.c
* Author: shota
*
* Created on February 22, 2016, 11:29 PM
*/

// PIC12F1822 Configuration Bit Settings

// 'C' source line config statements
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// コンフィギュレーション１の設定
#pragma config FOSC = INTOSC    // 内部ｸﾛｯｸを使用する(INTOSC)
#pragma config WDTE = OFF       // ｳｵｯﾁﾄﾞｯｸﾞﾀｲﾏｰ無し(OFF)
#pragma config PWRTE = ON       // 電源ONから64ms後にﾌﾟﾛｸﾞﾗﾑを開始する(ON)
#pragma config MCLRE = OFF      // 外部ﾘｾｯﾄ信号は使用せずにﾃﾞｼﾞﾀﾙ入力(RA5)ﾋﾟﾝとする(OFF)
#pragma config CP = OFF         // ﾌﾟﾛｸﾞﾗﾑﾒﾓﾘｰを保護しない(OFF)
#pragma config CPD = OFF        // ﾃﾞｰﾀﾒﾓﾘｰを保護しない(OFF)
#pragma config BOREN = ON       // 電源電圧降下常時監視機能ON(ON)
#pragma config CLKOUTEN = OFF   // CLKOUTﾋﾟﾝをRA6ﾋﾟﾝで使用する(OFF)
#pragma config IESO = OFF       // 外部・内部ｸﾛｯｸの切替えでの起動はなし(OFF)
#pragma config FCMEN = OFF      // 外部ｸﾛｯｸ監視しない(FCMEN_OFF)

// コンフィギュレーション２の設定
#pragma config WRT = OFF        // Flashﾒﾓﾘｰを保護しない(OFF)
#pragma config PLLEN = OFF      // 動作クロックを32MHzでは動作させない(OFF)
#pragma config STVREN = ON      // スタックがオーバフローやアンダーフローしたらリセットをする(ON)
#pragma config BORV = HI        // 電源電圧降下常時監視電圧(2.5V)設定(HI)
#pragma config LVP = OFF        // 低電圧プログラミング機能使用しない(OFF)

#define _XTAL_FREQ  8000000
#define test RA2
#define reed_switch RA3
#define tx RA4 // シリアル通信送信用
#define rx RA5 // シリアル通信送信用
static void pic_init();

void main(void)
{
  //初期設定
  pic_init();
  while(1)
  {
    while(TXIF == 0){}
    if(reed_switch == 1){
      test = 1;
      TXREG = 1;
    } else {
      test = 0;
      TXREG = 0;
    }
    __delay_ms(1000);
  }
}


static void pic_init(){
  //clock
  OSCCON = 0b01110000;      // 8MHz
  //IO
  ANSELA= 0x00;	// set all RA to digital pin
  //TRISA = 0x00; // RAを全てアウトプット
  TRISA = 0b00101011;			// IOポートRA0(AN0),RA1(SCL),RA5(RX)を入力モード（RA3は入力専用）、RA2(SDA), RA4(TX)を出力モード
  PORTA = 0x00;
  WPUA = 0b00001000; // RA3は内部プルアップ抵抗を指定する
  // USART機能の設定を行う
  RXDTSEL = 1;   // 2番ピン(RA5)をRX受信ピンとする
  TXCKSEL = 1;   // 3番ピン(RA4)をTX送信ピンとする
  SPBRG = 51; //9600bps (FOSC=8MHz (without PLLx4))
  TXEN = 1; // 送信を許可するかの指定ビット
  SYNC = 0; // ＵＳＡＲＴモードの指定ビット
  SPEN = 1;  // シリアルピン使用の指定ビット
  CREN = 1; // 連続受信許可の指定ビット
  RCIE=1; //RC intrrupt enable

  TXSTA  = 0b00100100 ;     // 送信情報設定：非同期モード ８ビット・ノンパリティ
  RCSTA  = 0b10010000 ;     // 受信情報設定
}
