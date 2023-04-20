/*
 * File:   lab08.c
 * Dispositivo:	PIC16f887
 * Author: Santiago Sánchez
*/
// PIC16F887 Configuration Bit Setting

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = ON      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 8000000 

void texto(char data);
void cadena(char *str);
void setup();

char valor;
uint8_t pot;

void setup(){
    ANSEL = 0b00000001;
    ANSELH = 0;
    TRISA = 0b00000001; // PORTA todo salida
    TRISB = 0; // PORTB todo salida
    PORTA = 0;
    PORTB = 0;
    OSCCONbits.IRCF = 0b111 ;  // config. de oscilador interno
    OSCCONbits.SCS = 1;         //reloj interno
    TXSTAbits.SYNC = 0;     //asincrono
    TXSTAbits.BRGH = 1;     //high speed
    BAUDCTLbits.BRG16 = 1;  //uso los 16 bits
    SPBRG = 207;   //Baud rate necesario                       
    SPBRGH = 0;    //Para valores mayores a 255         
    RCSTAbits.SPEN = 1;     //enciendo el modulo
    RCSTAbits.RX9 = 0;      //8 bits
    RCSTAbits.CREN = 1;     //Habilitamos recepción
    TXSTAbits.TXEN = 1;     //Habilitamos transmision 
    ADCON1bits.VCFG0 = 0; //REF a voltaje 
    ADCON1bits.VCFG1 = 0; //REF a tierra 
    ADCON1bits.ADFM = 0; 
    PIE1bits.ADIE = 1;
    PIR1bits.ADIF = 0;
    ADCON0bits.ADCS = 0b00;
    ADCON0bits.CHS = 0b0000;
    ADCON0bits.ADON = 1;
}

void main(void){
    setup();
    while (1) {
        cadena("\r Que accion desea realizar: \r");
        cadena(" 1) Desplegar caracter \r");
        cadena(" 2) Enviar Ascii \r");
        cadena(" 3) Mostrar cadena \r");
        cadena(" 4) Mostrar potenciometro \r");
        
        while(PIR1bits.RCIF == 0);  
        
        valor = RCREG;
          
        switch(valor){
            case ('1'):
                cadena(" Ingrese valor desea mostrar: \r");
                while(PIR1bits.RCIF == 0);
                valor = RCREG;
                switch (valor){
                    case ('a'):
                    cadena("\ra");
                    break;
                    case ('2'):
                    cadena("\r2");
                    break;
                    case ('3'):
                    cadena("\r3");
                    break;
                    case ('4'):
                    cadena("\r4");
                    break;
                    case ('5'):
                    cadena("\r5");
                    break;
                    case ('6'):
                    cadena("\r6");
                    break;
                    case ('7'):
                    cadena("\r7");
                    break;
                    case ('8'):
                    cadena("\r8");
                    break;
                    case ('9'):
                    cadena("\r9");
                    break;
                }
                break;                         
                
            case ('2'):
                cadena(" Enviar Ascii: ");
                while(PIR1bits.RCIF == 0);//Espera que se ingrese un dato 
                PORTB = RCREG;  //lo paso al puerto B
                cadena("\r El valor se ha mostrado \r");
                break;   
                
            case ('3'):
                cadena("\r Hola \r");
                break;  
                
            case ('4'):
                    if (ADCON0bits.CHS == 0b0000) 
                    {
                        pot = ADRESH;
                    }
                PORTB = pot;
                break;
               
            default:
            cadena("error \r");     
        }
    }
    return;
}
    void texto(char data){
        while(TXSTAbits.TRMT == 0);
        TXREG = data;
    }

    void cadena(char *str){
        while(*str != '\0'){
            texto(*str);
            str++;
        }
    }