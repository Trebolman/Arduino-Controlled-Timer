#define LCD_ENABLE_PIN  PIN_D3                                    ////
#define LCD_RS_PIN      PIN_D2                                    ////
#define LCD_RW_PIN      PIN_A0                                    ////
#define LCD_DATA4       PIN_D4                                    ////
#define LCD_DATA5       PIN_D5                                    ////
#define LCD_DATA6       PIN_D6                                    ////
#define LCD_DATA7       PIN_D7
//Termino de las conexiones LCD

#include <16F877A.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock = 20000000)
//~ #include <math.h>
#include <lcd.c>
//~ #include <stdlib.h>

int8    carga;
int32    f=34;
int32    ifrecuencia;

char     frecuencia[]="03000 Hz";

void     showFrecuencia()
{
   ifrecuencia=f*100;
   frecuencia[0]=ifrecuencia/10000+48;
      if((frecuencia[0]<48)||(frecuencia[0]>57)){frecuencia[0]=48;}
   frecuencia[1]=ifrecuencia/1000+48;
      if((frecuencia[1]<48)||(frecuencia[1]>57)){frecuencia[1]=48;}
   frecuencia[2]=(ifrecuencia%1000)/10+48;
      if((frecuencia[2]<48)||(frecuencia[2]>57)){frecuencia[2]=48;}
   frecuencia[3]=(ifrecuencia%1000)%10+48;
      if((frecuencia[3]<48)||(frecuencia[3]>57)){frecuencia[3]=48;}
   frecuencia[4]=ifrecuencia%10+48;
      if((frecuencia[4]<48)||(frecuencia[4]>57)){frecuencia[4]=48;}
}

#INT_TIMER0
void     timer0_int()
{
   output_toggle(PIN_E1);
   set_timer0(carga);
}

void     main()
{
   set_tris_b(0x0F);
   set_tris_e(0x00);
   port_b_pullups(FALSE);

   lcd_init();
   
   lcd_putc("Error");

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_4);
   carga=256-200000/(8*4*f)+15;
   set_timer0(carga);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(global);
   
   showFrecuencia();
   
   while(1)
   {
      lcd_putc("\f");
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Carga: %u", carga);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"Frec(Hz): %Lu", f*100);
      delay_ms(100);
   }
}

