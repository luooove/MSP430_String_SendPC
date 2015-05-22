//用来测试按键发送字符串给PC机，不同的按键发送不同的指令。
//下一步用按键控制液晶

#include <msp430.h> 
#define uchar unsigned char
#define uint unsigned int
//#include "Key.c"
unsigned char str[10]="abc\n";


/* MCLK=16MHZ 下测定 */

void delay_ms(uint i)
{
  uint j=1328;
  while(i--)
  {
       for(j=1328;j>0;j--);
  }
}

void Serial_init()
{
	P10SEL = 0x30;                             // P10.4,5 = USCI_A0 TXD/RXD
	UCA3CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCA3CTL1 |= UCSSEL_2;                     // SMCLK
	UCA3BR0 = 6;                              // 1MHz 9600 (see User's Guide)
	UCA3BR1 = 0;                              // 1MHz 9600
	UCA3MCTL = UCBRS_0 + UCBRF_13 + UCOS16;   // Modln UCBRSx=0, UCBRFx=0,
											// over sampling
	UCA3CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	//UCA3IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

}


void UartTX_Send(unsigned char *Data,int len)
{
	int j;
	for(j=0;j<len;j++)
		{
			while (!(UCA3IFG&UCTXIFG));
			UCA3TXBUF =*Data++;
		}
}

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    Serial_init();
    UartTX_Send(str,4);
    UartTX_Send(str,4);
    UartTX_Send(str,4);
	return 0;
}
