unsigned int ADC_data;
unsigned char RX_data, TX_data[7];

void main() {

  OSCCON=0x70;
  NOT_WPUEN_bit=0;   /*Enabling Internal Pull-Up Functions*/
  WPUC|=0x07;
  ANSELA=0x01;  /*Deactivating analog inputs, all pins are digital*/
  ANSELC=0x00;

  TRISC.B3=0; /*Declaring RC3(PIN 7) as output*/
  PORTC.B3=0;

  TRISC.B2=0; /*Declaring RC2(PIN 8) as output*/
  PORTC.B2=1;

  TRISC.B1=0; /*Declaring RC1(PIN 9) as output*/
  PORTC.B1=0;

  TRISC.B0=0; /*Declaring RC0(PIN 10) as output*/
  PORTC.B0=1;

  ADCON1=0xD0;   
  ADCON0=0x01; 

  for (;;) {
    GO_NOT_DONE_bit=1;
    while(GO_NOT_DONE_bit==1); /*Waiting for conversion to be over*/
    ADC_data=ADRESL;    /*Reading LOW Byte of ADC Result*/
    ADC_data=ADC_data+(ADRESH<<8);  /*Reading HIGH Byte of ADC Result*/
    IntToStr(ADC_data, TX_data);  /*Converting ADC data to string of chars*/

    if(ADC_data>51)    /*If Vin > 2.5V*/
        {
            PORTC.B3=1;  /*Turning LED ON*/
            PORTC.B2=0;
            PORTC.B1=0;
            PORTC.B0=0;
            Delay_ms(2000);
            PORTC.B0=1;
            Delay_ms(2000);
        }
        else
        {
        if(ADC_data<51 && ADC_data>31)    /*If Vin > 2.5V*/
        {
            PORTC.B3=0;  /*Turning LED ON*/
            PORTC.B2=1;
            PORTC.B1=0;
            PORTC.B0=0;
            Delay_ms(1000);
            PORTC.B0=1;
            Delay_ms(2000);
        }
        else
        {
            PORTC.B3=0;  /*Turning LED OFF*/
            PORTC.B2=0;
            PORTC.B1=1;
            PORTC.B0=0;
        }
        }
}
}
