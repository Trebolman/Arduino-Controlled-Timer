#include <LiquidCrystal.h>
#include <TimerOne.h>
const uint8_t led = 13;                // the pin with a LED
int ledState = LOW;                    // El LED empieza apagado
volatile unsigned long blinkCount = 0; // La definimos como volatile
uint8_t seg, minutos, hora;
//  ENTRADAS
uint8_t PushConfig = 14;
uint8_t PushMax = 15;
uint8_t PushMin = 16;
uint8_t PushDesconfig = 17;
int delayPush = 800;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup(void)
{
    // MODOS DE PINES
    pinMode(led, OUTPUT);
    pinMode(PushConfig, INPUT);
    pinMode(PushDesconfig, INPUT);
    pinMode(PushMax, INPUT);
    pinMode(PushMin, INPUT);

    // INICIALIZAMOS VALORES
    Timer1.initialize(1000000);        // Dispara cada segundo
    Timer1.attachInterrupt(ISR_Blink); // Activa la interrupcion y la asocia a ISR_Blink
    Serial.begin(9600);
    lcd.begin(16, 2);

    // OTRAS CONFIGURACIONES
}

void ISR_Blink()
{
    ledState = !ledState;
    seg++; // Contador veces se enciende el LED
    if (seg == 60)
    {
        minutos++;
        seg = 0;
    }
    if (minutos == 60)
    {
        hora++;
        minutos = 0;
    }
    if (hora == 24)
    {
        hora = 0;
    }
}

void editarTiempo()
{
    noInterrupts();
    uint8_t item = 1;
    bool flag = false;
    while(true)
    {
        switch (item)
        { 
            case 1:
            {
                while (true)
                {
                    lcd.setCursor(2, 0);
                    lcd.print("Editando HORA");
                    lcd.setCursor(4, 1);
                    lcd.print(hora);
                    lcd.setCursor(6, 1);
                    lcd.print(":");
                    lcd.setCursor(7, 1);
                    lcd.print(minutos);
                    lcd.setCursor(9, 1);
                    lcd.print(":");
                    lcd.setCursor(10, 1);
                    lcd.print(seg);

                    if (digitalRead(PushMax) == HIGH)
                    {
                        delay(delayPush + 1000);
                        lcd.clear();
                        hora++;
                        if (hora == 24)
                        {
                            hora = 0;
                        }
                    }
                    if (digitalRead(PushMin) == HIGH)
                    {
                        delay(delayPush + 1000);
                        lcd.clear();
                        hora--;
                        if (hora < 0)
                        {
                            hora == 0;
                        }
                    }
                    if (digitalRead(PushConfig) == HIGH)
                    {
                        delay(delayPush + 1000);
                        item = 2;
                        flag = true;
                        break;
                    }
                    if (digitalRead(PushDesconfig) == HIGH)
                    {
                        delay(delayPush);
                        flag = false;
                        break;
                    }
                    delay(delayPush+300);
                }
                break;
            }
            
            case 2:
            {
                while (true)
                {
                    // lcd.clear();
                    lcd.setCursor(1, 0);
                    lcd.print("Editando MINUTOS");
                    lcd.setCursor(4, 1);
                    lcd.print(hora);
                    lcd.setCursor(6, 1);
                    lcd.print(":");
                    lcd.setCursor(7, 1);
                    lcd.print(minutos);
                    lcd.setCursor(9, 1);
                    lcd.print(":");
                    lcd.setCursor(10, 1);
                    lcd.print(seg);

                    if (digitalRead(PushMax) == HIGH)
                    {
                        delay(delayPush + 1000);
                        lcd.clear();
                        minutos++;
                        if (minutos == 60)
                        {
                            minutos = 0;
                        }
                    }
                    if (digitalRead(PushMin) == HIGH)
                    {
                        delay(delayPush + 1000);
                        lcd.clear();
                        minutos--;
                        if (minutos < 0)
                        {
                            minutos == 0;
                        }
                    }
                    if (digitalRead(PushConfig) == HIGH)
                    {
                        delay(delayPush + 1000);
                        lcd.clear();
                        item = 3;
                        flag = true;
                        break;
                    }
                    if (digitalRead(PushDesconfig) == HIGH)
                    {
                        delay(delayPush);
                        flag = false;
                        break;
                    }
                    delay(delayPush+300);
                }
                break;
            }

            case 3:
            {
                while (true)
                {
                    // lcd.clear();
                    lcd.setCursor(1, 0);
                    lcd.print("Editando SEGUNDOS");
                    lcd.setCursor(4, 1);
                    lcd.print(hora);
                    lcd.setCursor(6, 1);
                    lcd.print(":");
                    lcd.setCursor(7, 1);
                    lcd.print(minutos);
                    lcd.setCursor(9, 1);
                    lcd.print(":");
                    lcd.setCursor(10, 1);
                    lcd.print(seg);

                    if (digitalRead(PushMax) == HIGH)
                    {
                        delay(delayPush + 1000);
                        lcd.clear();
                        seg++;
                        if (seg == 60)
                        {
                            seg = 0;
                        }
                    }
                    if (digitalRead(PushMin) == HIGH)
                    {
                        delay(delayPush + 1000);
                        lcd.clear();
                        seg--;
                        if (seg < 0)
                        {
                            seg == 0;
                        }
                    }
                    if (digitalRead(PushConfig) == HIGH)
                    {
                        delay(delayPush + 1000);
                        item = 1;
                        flag = true;
                        lcd.clear();
                        break;
                    }
                    if (digitalRead(PushDesconfig) == HIGH)
                    {
                        delay(delayPush);
                        flag = false;
                        break;
                    }
                    delay(delayPush+300);
                }
                break;
            }
        }
        if(!flag){break;}
    }
    interrupts();
}

void loop(void)
{
    lcd.clear();
    lcd.setCursor(4, 1);
    lcd.print(hora);
    lcd.setCursor(6, 1);
    lcd.print(":");
    lcd.setCursor(7, 1);
    lcd.print(minutos);
    lcd.setCursor(9, 1);
    lcd.print(":");
    lcd.setCursor(10, 1);
    lcd.print(seg);
    if (digitalRead(PushConfig) == HIGH)
    {
        delay(delayPush);
        editarTiempo();
        lcd.clear();
    }
    digitalWrite(led, ledState); // Asignamos el valor del
    delay(200);
}