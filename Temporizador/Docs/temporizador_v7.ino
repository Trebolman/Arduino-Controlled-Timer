#include <LiquidCrystal.h>
#include <TimerOne.h>

int seg = 0, _seg = 0;
int minutos = 0, _minutos = 0;
int hora = 0, _hora = 0;

//  ENTRADAS
const uint8_t btnInicioPara    = 14;
// const uint8_t btnInicioPara  = 15;
const uint8_t btnConfig   = 16;
const uint8_t btnMas      = 17;
const uint8_t btnMin      = 18;
// const uint8_t btnSalir    = 19;
const uint8_t btnEmergencia = 20;

// SALIDAS
uint8_t backLight   = 21;
uint8_t outTiempo      = 3;    //
uint8_t outEmergencia  = 4;    // 
uint8_t outFinalTiempo = 5;    //

// VARIABLES DE CONTROL
int     delayPush   = 200;
bool    TempActivo  = false;
int     limite      = 0, contador = 0;
bool    Emergencia  = false;
bool    EstadoEmergencia = false;
// unsigned long   previo = 0;
int     TiempoBackLight = 10;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// VARIABLES ANTIREBOTE
const int tiempoAntirebote = 10;
int estadoBtnInicioPara;
int estadoBtnEmergencia;
int estadoBtnMas;
int estadoBtnMin;
int estadoBtnSalir;
int estadoBtnConfig;
int estadoBotonAnterior;

// INICIO DE PROGRAMA
void setup(void)
{ 
    // MODOS DE PINES
    pinMode(btnInicioPara, INPUT);
    // pinMode(btnInicioPara, INPUT);
    pinMode(btnConfig, INPUT);
    pinMode(btnMas, INPUT);
    pinMode(btnMin, INPUT);
    // pinMode(btnSalir, INPUT);
    pinMode(btnEmergencia, INPUT);
    
    pinMode(outTiempo, OUTPUT);
    pinMode(outEmergencia, OUTPUT);
    pinMode(outFinalTiempo, OUTPUT);
    pinMode(backLight, OUTPUT);

    // CONFIGURAMOS EL TIMER
    Timer1.initialize(1000000);        // Dispara cada segundo
    Timer1.attachInterrupt(ISR_Blink); // Activa la interrupcion y la
    Serial.begin(9600);
    noInterrupts();

    digitalWrite(outTiempo, HIGH);
    digitalWrite(outEmergencia, HIGH);
    digitalWrite(outFinalTiempo, HIGH);
    digitalWrite(backLight, HIGH);

    // CONFIGURANDO EL LCD
    lcd.begin(16, 2);
    ImprimirEstado();
    ImprimirLineas();
    ImprimirSeg();
    ImprimirMin();
    ImprimirHora();
    // OTRAS CONFIGURACIONES
}

void ISR_Blink()
{
    contador++;
    TiempoBackLight++;
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
            if (hora >= 0)
            {
                minutos = 59;
            }
            else
            {
                minutos = 0;
            }
            if (hora < 0)
            {
                hora = 0;
            }
        }
    }
    seg--;
}

void loop(void)
{
    // ImprimirEstado();

    if (contador > limite)
    {
        // Serial.println("contador > limite");
        noInterrupts();
        TempActivo = false;
        contador = 0;
        seg = _seg;
        minutos = _minutos;
        hora = _hora;
        digitalWrite(outFinalTiempo, LOW);
        ImprimirEstado();
        digitalWrite(backLight, HIGH);
        ReiniciarTiempoBackLight();
    }

    VerificarEstadoTemporizador();

    if(TiempoBackLight > 10){digitalWrite(backLight,LOW);}

    VerificarBtnEmergencia();

    estadoBotonAnterior = estadoBtnConfig;
    estadoBtnConfig = digitalRead(btnConfig);
    if (estadoBtnConfig != estadoBotonAnterior)
    {
        if (antirebote(btnConfig)){
            ReiniciarTiempoBackLight();
            if(!TempActivo)
            ConfigurarTiempos();
            ImprimirEstado();
        }
    }

    estadoBotonAnterior = estadoBtnInicioPara;
    estadoBtnInicioPara = digitalRead(btnInicioPara);
    if (estadoBtnInicioPara != estadoBotonAnterior) // ACTIVAR TEMPORIZADOR
    {
        if (antirebote(btnInicioPara)){
            ReiniciarTiempoBackLight();
            if(TempActivo){ReiniciarTiempoBackLight(); noInterrupts(); TempActivo = false;}
            else{
                interrupts(); 
                TempActivo = true;
                ReiniciarTiempoBackLight();
                digitalWrite(outFinalTiempo,HIGH);
            }
            ImprimirEstado();
        }
    }
}

// METODOS
void ReiniciarTiempoBackLight(){
    TiempoBackLight = 0;
    digitalWrite(backLight,HIGH);
}

void ImprimirEstado(){

    if(TempActivo){
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("ACTIVADO");
        ImprimirLineas();
        ImprimirHora();
        ImprimirMin();
        ImprimirSeg();
    }else{
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("DETENIDO");
        ImprimirLineas();
        ImprimirHora();
        ImprimirMin();
        ImprimirSeg();
    }
    if(Emergencia){
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("EMERGENCIA");
        ImprimirLineas();
        ImprimirHora();
        ImprimirMin();
        ImprimirSeg();
    }
}

void ImprimirLineas()
{
    lcd.setCursor(6, 1);
    lcd.print(":");
    lcd.setCursor(9, 1);
    lcd.print(":");
}

void ImprimirSeg()
{
    if (seg < 10)
    {
        lcd.setCursor(10, 1);
        lcd.print("0");
        lcd.setCursor(11, 1);
        lcd.print(seg);
        lcd.leftToRight();
    }
    else
    {
        lcd.setCursor(9, 1);
        lcd.print(":");
        lcd.setCursor(10, 1);
        lcd.print(seg);
    }
}

void ImprimirMin()
{
    if (minutos < 10)
    {
        lcd.setCursor(7, 1);
        lcd.print("0");
        lcd.setCursor(8, 1);
        lcd.print(minutos);
    }
    else
    {
        lcd.setCursor(7, 1);
        lcd.print(minutos);
    }
}

void ImprimirHora()
{
    if (hora < 10)
    {
        lcd.setCursor(4, 1);
        lcd.print("0");
        lcd.setCursor(5, 1);
        lcd.print(hora);
    }
    else
    {
        lcd.setCursor(4, 1);
        lcd.print(hora);
    }
}

void ConfigurarLimite()
{
    limite = seg + minutos * 60 + hora * 60 * 60;
    Serial.println(limite);
    TempActivo = false;
}

void ConfigurarTiempos()
{
    // noInterrupts();
    uint8_t item = 1;
    bool flag = false;
    do
    {
        switch (item)
        {
            case 1:
            {
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Editando HORA");

                ImprimirLineas();
                ImprimirSeg();
                ImprimirMin();
                ImprimirHora();
                while (true)
                {
                    VerificarBtnEmergencia();
                    estadoBotonAnterior = estadoBtnMas;
                    estadoBtnMas = digitalRead(btnMas);
                    if (estadoBtnMas != estadoBotonAnterior)
                    {
                        if (antirebote(btnMas))
                        {             //checamos  si esta preionado y si lo esta
                            hora++;
                            if (hora > 24)
                            {
                                hora = 0;
                            }
                            ImprimirHora();
                        }
                    }
                    
                    estadoBotonAnterior = estadoBtnMin;
                    estadoBtnMin = digitalRead(btnMin);
                    if (estadoBtnMin != estadoBotonAnterior)
                    {
                        if (antirebote(btnMin))
                        {             //checamos  si esta preionado y si lo esta
                            hora--;
                            if (hora < 0)
                            {
                                hora = 24;
                            }
                            ImprimirHora();
                        }
                    }

                    estadoBotonAnterior = estadoBtnInicioPara;
                    estadoBtnInicioPara = digitalRead(btnInicioPara);
                    if (estadoBtnInicioPara != estadoBotonAnterior)
                    {
                        if (antirebote(btnInicioPara))
                        {
                            flag = false;
                            break;
                        }
                    }

                    estadoBotonAnterior = estadoBtnConfig;
                    estadoBtnConfig = digitalRead(btnConfig);
                    if (estadoBtnConfig != estadoBotonAnterior)
                    {
                        if (antirebote(btnConfig)){
                            // goto case 2;
                            item = 2;
                            flag = true;
                            break;
                        }
                    }
                }
                // if(flag){goto case 2;}
                break;
            }

            case 2:
            {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Editando MINUTOS");

                ImprimirLineas();
                ImprimirSeg();
                ImprimirMin();
                ImprimirHora();
                while (true)
                {
                    VerificarBtnEmergencia();
                    estadoBotonAnterior = estadoBtnMas;
                    estadoBtnMas = digitalRead(btnMas);
                    if (estadoBtnMas != estadoBotonAnterior)
                    {
                        if (antirebote(btnMas))
                        {             //checamos  si esta preionado y si lo esta
                            minutos++;
                            if (minutos > 59)
                            {
                                minutos = 0;
                            }
                            ImprimirMin();
                        }
                    }
                    
                    estadoBotonAnterior = estadoBtnMin;
                    estadoBtnMin = digitalRead(btnMin);
                    if (estadoBtnMin != estadoBotonAnterior)
                    {
                        if (antirebote(btnMin))
                        {             //checamos  si esta preionado y si lo esta
                            minutos--;
                            if (minutos < 0)
                            {
                                minutos = 59;
                            }
                            ImprimirMin();
                        }
                    }

                    estadoBotonAnterior = estadoBtnInicioPara;
                    estadoBtnInicioPara = digitalRead(btnInicioPara);
                    if (estadoBtnInicioPara != estadoBotonAnterior)
                    {
                        if (antirebote(btnInicioPara))
                        {
                            flag = false;
                            break;
                        }
                    }

                    estadoBotonAnterior = estadoBtnConfig;
                    estadoBtnConfig = digitalRead(btnConfig);
                    if (estadoBtnConfig != estadoBotonAnterior)
                    {
                        if (antirebote(btnConfig)){
                            item = 3;
                            flag = true;
                            break;
                        }
                    }
                }
                break;
            }

            case 3:
            {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Editando SEGUNDOS");

                ImprimirLineas();
                ImprimirSeg();
                ImprimirMin();
                ImprimirHora();
                while (true)
                {
                    VerificarBtnEmergencia();

                    estadoBotonAnterior = estadoBtnMas;
                    estadoBtnMas = digitalRead(btnMas);
                    if (estadoBtnMas != estadoBotonAnterior)
                    {
                        if (antirebote(btnMas))
                        {             //checamos  si esta preionado y si lo esta
                            seg++;
                            if (seg > 59 )
                            {
                                seg = 0;
                            }
                            ImprimirSeg();
                        }
                    }
                    
                    estadoBotonAnterior = estadoBtnMin;
                    estadoBtnMin = digitalRead(btnMin);
                    if (estadoBtnMin != estadoBotonAnterior)
                    {
                        if (antirebote(btnMin))
                        {             //checamos  si esta preionado y si lo esta
                            seg--;
                            if (seg < 0 )
                            {
                                seg = 59;
                            }
                            ImprimirSeg();
                        }
                    }

                    estadoBotonAnterior = estadoBtnInicioPara;
                    estadoBtnInicioPara = digitalRead(btnInicioPara);
                    if (estadoBtnInicioPara != estadoBotonAnterior)
                    {
                        if (antirebote(btnInicioPara))
                        {
                            flag = false;
                            break;
                        }
                    }

                    estadoBotonAnterior = estadoBtnConfig;
                    estadoBtnConfig = digitalRead(btnConfig);
                    if (estadoBtnConfig != estadoBotonAnterior)
                    {
                        if (antirebote(btnConfig)){
                            item = 1;
                            flag = true;
                            break;
                        }
                    }
                }
                break;
            }
        }
        // interrupts();
    }while (flag);
    lcd.clear();
    ConfigurarLimite();
    _seg = seg;
    _minutos = minutos;
    _hora = hora;
    ReiniciarTiempoBackLight();
    TempActivo = true;
    // interrupts();
}

void VerificarBtnEmergencia(){
    estadoBotonAnterior = estadoBtnEmergencia;
    estadoBtnEmergencia = digitalRead(btnEmergencia);
    if (estadoBtnEmergencia != estadoBotonAnterior)
    {
        // Serial.println("btnEmergencia");
        if (antirebote(btnEmergencia)){
            Emergencia = true;
            TempActivo = false; //desactiva el temporizador siempre
            noInterrupts();
            digitalWrite(outEmergencia,LOW); //activa pin de emergencia
            digitalWrite(outTiempo,HIGH); //desactiva pin de tiempo
            digitalWrite(outFinalTiempo,HIGH);
            ReiniciarTiempoBackLight();
            ImprimirEstado();
            while(true){
                if(digitalRead(btnEmergencia) == LOW){
                    break;
                }
            }
            Emergencia = false;
            digitalWrite(outEmergencia,HIGH);
            ReiniciarTiempoBackLight();
            ImprimirEstado();
        }
    }
}

void VerificarEstadoTemporizador(){
    if(TempActivo){
        digitalWrite(outTiempo,LOW);
        interrupts();
        // ImprimirEstado();
    }else{
        digitalWrite(outTiempo,HIGH);
        noInterrupts();
        // ImprimirEstado();
    }
}

void LimpiarVariables(){
    hora = minutos = seg = limite = contador = 0;
    lcd.clear();
    ImprimirLineas();
    ImprimirHora();
    ImprimirMin();
    ImprimirSeg();
}
// FUNCION ANTIREBOTE
bool antirebote(int pin)
{
    int contador = 0;
    bool estado;         // guarda el estado del boton
    bool estadoAnterior; // guarda el ultimo estado del boton

    do
    {
        estado = digitalRead(pin);
        if (estado != estadoAnterior)
        {                 // comparamos el estado actual
            contador = 0; // reiniciamos el contador
            estadoAnterior = estado;
        }
        else
        {
            contador = contador + 1; // aumentamos el contador en 1
        }
        delay(1);
    } while (contador < tiempoAntirebote);
    return estado;
}
