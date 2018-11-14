#include <LiquidCrystal.h> 
#include <TimerOne.h> 

int seg = 0;
int minutos = 0;
int hora = 0;            

//  ENTRADAS 
uint8_t btnConfig = 15;
uint8_t btnMas = 16;
uint8_t btnMin = 17;
uint8_t btnSalir = 14;
uint8_t salida = 18;

int delayPush = 800;
int limite = 0, contador = 0;
bool level = HIGH;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);




void setup(void)
{ // MODOS DE PINES pinMode(led, OUTPUT);
    pinMode(btnConfig, INPUT);
    pinMode(btnMin, INPUT);
    pinMode(btnConfig, INPUT);
    pinMode(btnMas, INPUT);
    pinMode(btnSalir, INPUT);
    pinMode(salida, OUTPUT);
    
     // INICIALIZAMOS 
    Timer1.initialize(1000000); // Dispara cada segundo
    Timer1.attachInterrupt(ISR_Blink);  // Activa la interrupcion y la 
    Serial.begin(9600);
    lcd.begin(16, 2); 
    digitalWrite(salida, !level);
    // hora = 0;
    // minutos = 0;
    // seg = 30;

    // CONFIGURANDO EL LCD
    // ImprimirLCD();
    ImprimirLineas();
    ImprimirSeg();
    ImprimirMin();
    ImprimirHora();
    
    // OTRAS CONFIGURACIONES
}

void ISR_Blink(){
    contador++;
    Serial.println(limite);Serial.println(contador);
     // Contador veces se enciende el LED 
    ImprimirSeg();
    ImprimirMin();
    ImprimirHora();
    if (seg == 0)
    {
        seg = 59;
        minutos--;
        if (minutos < 0)
        {
            hora--;
            if(hora != 0){minutos = 59;}
            else{minutos = 0;}
            if (hora < 0) { hora = 0; }
        }
    }
    seg--;
}

void loop(void)
{
    if(contador == limite + 1){
        noInterrupts();
    }
    if (digitalRead(btnConfig) == HIGH)
    {
        delay(delayPush);
        // hora = 2;
        // minutos = seg = 0;
        // ConfigurarLimite();
        ConfigurarTiempos();
    }
    if (digitalRead(btnMas) == HIGH)
    {
        delay(delayPush);
        interrupts();
        // lcd.clear();
    }
    if (digitalRead(btnMin) == HIGH)
    {
        delay(delayPush);
        noInterrupts();
        // AsignarTiempo();
        // lcd.clear();
    }
}


// METODOS
// ImprimirLineas();
void ImprimirLineas(){
    lcd.setCursor(6, 1);
    lcd.print(":");
    lcd.setCursor(9, 1);
    lcd.print(":");
}

void ImprimirSeg(){ 
    if(seg < 10){
        lcd.setCursor(10, 1);
        lcd.print("0");
        lcd.setCursor(11, 1);
        lcd.print(seg);
        lcd.leftToRight();
    }else{
        lcd.setCursor(9, 1);
        lcd.print(":");
        lcd.setCursor(10, 1);
        lcd.print(seg);
    }
}

void ImprimirMin(){
    if(minutos < 10){
        lcd.setCursor(7, 1);
        lcd.print("0");
        lcd.setCursor(8, 1);
        lcd.print(minutos);
    }else{
        lcd.setCursor(7, 1);
        lcd.print(minutos);
    } 
}

void ImprimirHora(){ 
    if(hora < 10){
        lcd.setCursor(4, 1);
        lcd.print("0");
        lcd.setCursor(5, 1);
        lcd.print(hora);
    }else{
        lcd.setCursor(4, 1);
        lcd.print(hora);
    }
}

void ConfigurarLimite(){
    limite = seg + minutos*60 + hora*60*60;
}

void ConfigurarTiempos()
{
    noInterrupts();
    uint8_t item = 1;
    bool flag = false;
    while (true)
    {
        switch (item)
        {
            case 1:
            {
                lcd.setCursor(2, 0);
                lcd.print("Editando HORA");

                ImprimirLineas();
                ImprimirSeg();
                ImprimirMin();
                ImprimirHora();
                while (true)
                {
                    if (digitalRead(btnMas) == HIGH)
                    {
                        delay(delayPush + 1000);
                        if (digitalRead(btnMas) == HIGH){
                            
                            hora++;
                            if (hora > 24)
                            {
                                hora = 0;
                            }
                            ImprimirHora();
                        }
                    }
                    if (digitalRead(btnMin) == HIGH)
                    {
                        delay(delayPush + 1000);
                        if (digitalRead(btnMin) == HIGH){
                            hora--;
                            if (hora < 0)
                            {
                                hora == 24;
                            }
                            ImprimirHora();
                        }
                    }
                    if (digitalRead(btnConfig) == HIGH)
                    {
                        delay(delayPush + 1000);
                        if (digitalRead(btnConfig) == HIGH){
                            item = 2;
                            flag = true;
                            break;
                        }
                    }
                    if (digitalRead(btnSalir) == HIGH)
                    {
                        delay(delayPush);
                        if (digitalRead(btnSalir) == HIGH){
                            flag = false;
                            break;
                        }
                    }
                }
                break;
            }
        }
        interrupts();
    }
}

