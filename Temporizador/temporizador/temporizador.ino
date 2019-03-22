#include <LiquidCrystal.h>
#include <TimerOne.h>
#include <TimerThree.h>

int seg = 0, seg2 = 0, _seg = 0, _seg2_On = 0, _seg2_Off = 0;
int minutos = 0, minutos2 = 0, _minutos = 0, _min2_On = 0, _min2_Off = 0;
int hora = 0, hora2 = 0, _hora = 0, _hora2_On = 0, _hora2_Off = 0;

//  ENTRADAS
const uint8_t btnConfig = 15;
const uint8_t btnMas = 16;
const uint8_t btnMin = 17;
const uint8_t btnInicioPara = 18;
const uint8_t btnEmergencia = 19;

// SALIDAS
uint8_t backLight = 3;
uint8_t outTiempo = 12;      //
uint8_t outEmergencia = 11;  //
uint8_t outFinalTiempo = 10; //

// VARIABLES DE CONTROL
int delayPush = 200;
bool TempActivo = false;
int limite = 0, limite2 = 0, contador = 0, contador2 = 0, segundero = 0;
bool Emergencia = false;

bool permutador = false;
int temp2_encendido = 0, temp2_apagado = 0;
bool EstadoEmergencia = true;
int TiempoBackLight = 10;

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

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
    pinMode(btnConfig, INPUT);
    pinMode(btnMas, INPUT);
    pinMode(btnMin, INPUT);
    // pinMode(btnSalir, INPUT);
    pinMode(btnEmergencia, INPUT);

    pinMode(outTiempo, OUTPUT);
    pinMode(outEmergencia, OUTPUT);
    pinMode(outFinalTiempo, OUTPUT);
    pinMode(backLight, OUTPUT);

    digitalWrite(outTiempo, HIGH);
    digitalWrite(outEmergencia, HIGH);
    digitalWrite(outFinalTiempo, HIGH);
    digitalWrite(backLight, HIGH);

    // CONFIGURAMOS EL TIMER1
    Timer1.initialize(1000000);        // Dispara cada segundo
    Timer1.attachInterrupt(ISR_Blink); //

    // CONFIGURAMOS EL TIMER3
    Timer3.initialize(1000000);      // Dispara cada segundo
    Timer3.attachInterrupt(ISR_Seg); //
    Timer3.stop();
    // Serial.begin(9600);
    noInterrupts();

    // CONFIGURANDO EL LCD
    // Serial.begin(9600);
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
    contador2++;
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

    if (seg2 == 0)
    {
        seg2 = 59;
        minutos2--;
        if (minutos2 < 0)
        {
            hora2--;
            if (hora2 >= 0)
            {
                minutos2 = 59;
            }
            else
            {
                minutos2 = 0;
            }
            if (hora2 < 0)
            {
                hora2 = 0;
            }
        }
    }
    seg--;
    seg2--;
}

void ISR_Seg()
{
    segundero++;
}

void loop(void)
{

    if (contador > limite)
    {
        // digitalWrite(outTiempo, HIGH);
        TempActivo = false;
        contador = 0;
        contador2 = 0;
        permutador = true;
        
        seg = _seg;
        minutos = _minutos;
        hora = _hora;
        seg2 = _seg2_On;
        minutos2 = _min2_On;
        hora2 = _hora2_On;

        Timer1.stop();
        segundero = 0;
        Timer3.start();
        while (segundero < 4)
        {
            digitalWrite(outFinalTiempo, LOW);
        }
        digitalWrite(outFinalTiempo, HIGH);
        Timer3.stop();
        Timer1.start();
        noInterrupts();

        digitalWrite(backLight, HIGH);
        ReiniciarTiempoBackLight();
    }

    // temporizador 2
    if (contador2 > limite2)
    {
        if(permutador){
            limite2 = temp2_apagado;
            digitalWrite(outTiempo, HIGH);
            seg2 = _seg2_Off;
            minutos2 = _min2_Off;
            hora2 = _hora2_Off;
            permutador = false;
        }else{
            limite2 = temp2_encendido;
            digitalWrite(outTiempo, LOW);
            seg2 = _seg2_On;
            minutos2 = _min2_On;
            hora2 = _hora2_On;
            permutador = true;
        }
        contador2 = 0;

        ImprimirEstado();
    }

    VerificarEstadoTemporizador();

    if (TiempoBackLight > 10)
    {
        digitalWrite(backLight, LOW);
    }

    VerificarBtnEmergencia();

    estadoBotonAnterior = estadoBtnConfig;
    estadoBtnConfig = digitalRead(btnConfig);
    if (estadoBtnConfig != estadoBotonAnterior)
    {
        if (antirebote(btnConfig))
        {
            ReiniciarTiempoBackLight();
            if (!TempActivo)
                ElegirTemporizador();
            // ImprimirEstado();
        }
    }

    estadoBotonAnterior = estadoBtnMas;
    estadoBtnMas = digitalRead(btnMas);
    if (estadoBtnMas != estadoBotonAnterior)
    {
        if (antirebote(btnMas))
        {
            ReiniciarTiempoBackLight();
        }
    }

    estadoBotonAnterior = estadoBtnMin;
    estadoBtnMin = digitalRead(btnMin);
    if (estadoBtnMin != estadoBotonAnterior)
    {
        if (antirebote(btnMin))
        {
            ReiniciarTiempoBackLight();
        }
    }

    estadoBotonAnterior = estadoBtnInicioPara;
    estadoBtnInicioPara = digitalRead(btnInicioPara);
    if (estadoBtnInicioPara != estadoBotonAnterior) // ACTIVAR TEMPORIZADOR
    {
        if (antirebote(btnInicioPara))
        {
            ReiniciarTiempoBackLight();
            if (TempActivo)
            {
                ReiniciarTiempoBackLight();
                noInterrupts();
                TempActivo = false;
                hora = _hora;
                minutos = _minutos;
                seg = _seg;
                limite = 0;
                contador = 0;
                permutador = true;
                ElegirTemporizador();
                ReiniciarTiempoBackLight();
                ImprimirEstado();
            }
            else
            {
                interrupts();
                TempActivo = true;
                ReiniciarTiempoBackLight();
                digitalWrite(outFinalTiempo, HIGH);
            }
            ImprimirEstado();
        }
    }
}

// METODOS
void ReiniciarTiempoBackLight()
{
    TiempoBackLight = 0;
    digitalWrite(backLight, HIGH);
}

void ImprimirEstado()
{

    if (TempActivo)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ACT");
        lcd.setCursor(4, 0);
        lcd.print("T1:");
        lcd.setCursor(4, 1);
        lcd.print("T2:");
        ImprimirLineas();
        ImprimirHora();
        ImprimirMin();
        ImprimirSeg();
    }
    else
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DES");
        lcd.setCursor(4, 0);
        lcd.print("T1:");
        lcd.setCursor(4, 1);
        lcd.print("T2:");
        ImprimirLineas();
        ImprimirHora();
        ImprimirMin();
        ImprimirSeg();
    }
    if (Emergencia)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("EMR");
        lcd.setCursor(4, 0);
        lcd.print("T1:");
        lcd.setCursor(4, 1);
        lcd.print("T2:");
        ImprimirLineas();
        ImprimirHora();
        ImprimirMin();
        ImprimirSeg();
    }
}

void ImprimirLineas()
{
    // Primer temporizador
    lcd.setCursor(10, 0);
    lcd.print(":");
    lcd.setCursor(13, 0);
    lcd.print(":");

    // Segundo temporizador
    lcd.setCursor(10, 1);
    lcd.print(":");
    lcd.setCursor(13, 1);
    lcd.print(":");
}

void ImprimirPuntosConf(){
    lcd.setCursor(6, 1);
    lcd.print(":");
    lcd.setCursor(9, 1);
    lcd.print(":");
}

void ImprimirSeg()
{
    
    if (seg < 10)
    {
        lcd.setCursor(14, 0);
        lcd.print("0");
        lcd.setCursor(15, 0);
        lcd.print(seg);
        lcd.leftToRight();
    }
    else
    {
        lcd.setCursor(14, 0);
        lcd.print(seg);
    }

    // temporizador 2
    if (seg2 < 10)
    {
        lcd.setCursor(14, 1);
        lcd.print("0");
        lcd.setCursor(15, 1);
        lcd.print(seg2);
        lcd.leftToRight();
    }
    else
    {
        lcd.setCursor(14, 1);
        lcd.print(seg2);
    }
}

void ImprimirSeg2(){
    if (seg2 < 10)
    {
        lcd.setCursor(10, 1);
        lcd.print("0");
        lcd.setCursor(11, 1);
        lcd.print(seg2);
        lcd.leftToRight();
    }
    else
    {
        lcd.setCursor(10, 1);
        lcd.print(seg2);
    }
}

void ImprimirSegConf(){
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
        lcd.setCursor(10, 1);
        lcd.print(seg);
    }
}

void ImprimirMin()
{
    // temporizador 1
    if (minutos < 10)
    {
        lcd.setCursor(11, 0);
        lcd.print("0");
        lcd.setCursor(12, 0);
        lcd.print(minutos);
    }
    else
    {
        lcd.setCursor(11, 0);
        lcd.print(minutos);
    }

    // temporizador 2
    if (minutos2 < 10)
    {
        lcd.setCursor(11, 1);
        lcd.print("0");
        lcd.setCursor(12, 1);
        lcd.print(minutos2);
    }
    else
    {
        lcd.setCursor(11, 1);
        lcd.print(minutos2);
    }
}

void ImprimirMin2(){
   if (minutos2 < 10)
    {
        lcd.setCursor(7, 1);
        lcd.print("0");
        lcd.setCursor(8, 1);
        lcd.print(minutos2);
    }
    else
    {
        lcd.setCursor(7, 1);
        lcd.print(minutos2);
    } 
}

void ImprimirMinConf(){
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
        lcd.setCursor(8, 0);
        lcd.print("0");
        lcd.setCursor(9, 0);
        lcd.print(hora);
    }
    else
    {
        lcd.setCursor(8, 0);
        lcd.print(hora);
    }

    // temporizador 2
    if (hora2 < 10)
    {
        lcd.setCursor(8, 1);
        lcd.print("0");
        lcd.setCursor(9, 1);
        lcd.print(hora2);
    }
    else
    {
        lcd.setCursor(8, 1);
        lcd.print(hora2);
    }
}

void ImprimirHora2(){
    if (hora2 < 10)
    {
        lcd.setCursor(4, 1);
        lcd.print("0");
        lcd.setCursor(5, 1);
        lcd.print(hora2);
    }
    else
    {
        lcd.setCursor(4, 1);
        lcd.print(hora2);
    }
}

void ImprimirHoraConf(){
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

void ElegirTemporizador(){
    lcd.clear();
    uint8_t temporizador = 1;
    ImprimirSeleccion(temporizador);
    while(true){
        estadoBotonAnterior = estadoBtnMas;
        estadoBtnMas = digitalRead(btnMas);
        if (estadoBtnMas != estadoBotonAnterior)
        {
            if (antirebote(btnMas))
            { 
                temporizador++;
                if (temporizador > 2)
                {
                    temporizador = 1;
                }
                ImprimirSeleccion(temporizador);
            }
        }

        estadoBotonAnterior = estadoBtnMin;
        estadoBtnMin = digitalRead(btnMin);
        if (estadoBtnMin != estadoBotonAnterior)
        {
            if (antirebote(btnMin))
            {
                temporizador--;
                if (temporizador < 1)
                {
                    temporizador = 1;
                }
                ImprimirSeleccion(temporizador);
            }
        }

        estadoBotonAnterior = estadoBtnConfig;
        estadoBtnConfig = digitalRead(btnConfig);
        if (estadoBtnConfig != estadoBotonAnterior)
        {
            if (antirebote(btnConfig))
            { 
                ConfigurarTiempos(temporizador);
                ImprimirSeleccion(temporizador);
            }
        }

        estadoBotonAnterior = estadoBtnInicioPara;
        estadoBtnInicioPara = digitalRead(btnInicioPara);
        if (estadoBtnInicioPara != estadoBotonAnterior)
        {
            if (antirebote(btnInicioPara))
            {
                lcd.clear();
                TempActivo = true;
                permutador = true;
                ImprimirEstado();
                digitalWrite(outTiempo, LOW);
                ImprimirLineas();
                interrupts();
                break;
            }
        }
    }     
}

void ImprimirSeleccion(uint8_t tempo){
    switch(tempo){
        case 1:{
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ELIJA TEMPORIZ.");
            lcd.setCursor(2, 1);
            lcd.print("Temporizador 1");
            break;
        }

        case 2:{
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ELIJA TEMPORIZ.");
            lcd.setCursor(2, 1);
            lcd.print("Temporizador 2");
            break;
        }
    }
}

void ConfigurarTiempos(uint8_t tempo)
{
    uint8_t item = 1, temp_estado = 1;
    bool flag = false;
    switch(tempo){

        case 1:{
            seg = _seg;
            minutos = _minutos;
            hora = _hora;
            do
            {
                switch (item)
                {
                    case 1:
                    {
                        lcd.clear();
                        lcd.setCursor(1, 0);
                        lcd.print("T1 ACTIV HORA");

                        ImprimirPuntosConf();
                        ImprimirHoraConf();
                        ImprimirMinConf();
                        ImprimirSegConf();
                        while (true)
                        {
                            VerificarBtnEmergencia();
                            estadoBotonAnterior = estadoBtnMas;
                            estadoBtnMas = digitalRead(btnMas);
                            if (estadoBtnMas != estadoBotonAnterior)
                            {
                                if (antirebote(btnMas))
                                {
                                    hora++;
                                    if (hora > 24)
                                    {
                                        hora = 0;
                                    }
                                    ImprimirHoraConf();
                                }
                            }

                            estadoBotonAnterior = estadoBtnMin;
                            estadoBtnMin = digitalRead(btnMin);
                            if (estadoBtnMin != estadoBotonAnterior)
                            {
                                if (antirebote(btnMin))
                                {
                                    hora--;
                                    if (hora < 0)
                                    {
                                        hora = 24;
                                    }
                                    ImprimirHoraConf();
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
                                if (antirebote(btnConfig))
                                {
                                    // goto case 2;
                                    item = 2;
                                    flag = true;
                                    break;
                                }
                            }
                        }
                        break;
                    }

                    case 2:
                    {
                        lcd.clear();
                        lcd.setCursor(1, 0);
                        lcd.print("T1 ACTIV MIN");

                        ImprimirPuntosConf();
                        ImprimirSegConf();
                        ImprimirMinConf();
                        ImprimirHoraConf();
                        while (true)
                        {
                            VerificarBtnEmergencia();
                            estadoBotonAnterior = estadoBtnMas;
                            estadoBtnMas = digitalRead(btnMas);
                            if (estadoBtnMas != estadoBotonAnterior)
                            {
                                if (antirebote(btnMas))
                                { //checamos  si esta preionado y si lo esta
                                    minutos++;
                                    if (minutos > 59)
                                    {
                                        minutos = 0;
                                    }
                                    ImprimirMinConf();
                                }
                            }

                            estadoBotonAnterior = estadoBtnMin;
                            estadoBtnMin = digitalRead(btnMin);
                            if (estadoBtnMin != estadoBotonAnterior)
                            {
                                if (antirebote(btnMin))
                                { //checamos  si esta preionado y si lo esta
                                    minutos--;
                                    if (minutos < 0)
                                    {
                                        minutos = 59;
                                    }
                                    ImprimirMinConf();
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
                                if (antirebote(btnConfig))
                                {
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
                        lcd.print("T1 ACTIV SEG");

                        ImprimirPuntosConf();
                        ImprimirSegConf();
                        ImprimirMinConf();
                        ImprimirHoraConf();
                        while (true)
                        {
                            VerificarBtnEmergencia();

                            estadoBotonAnterior = estadoBtnMas;
                            estadoBtnMas = digitalRead(btnMas);
                            if (estadoBtnMas != estadoBotonAnterior)
                            {
                                if (antirebote(btnMas))
                                { //checamos  si esta preionado y si lo esta
                                    seg++;
                                    if (seg > 59)
                                    {
                                        seg = 0;
                                    }
                                    ImprimirSegConf();
                                }
                            }

                            estadoBotonAnterior = estadoBtnMin;
                            estadoBtnMin = digitalRead(btnMin);
                            if (estadoBtnMin != estadoBotonAnterior)
                            {
                                if (antirebote(btnMin))
                                { //checamos  si esta preionado y si lo esta
                                    seg--;
                                    if (seg < 0)
                                    {
                                        seg = 59;
                                    }
                                    ImprimirSegConf();
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
                                if (antirebote(btnConfig))
                                {
                                    item = 1;
                                    flag = true;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            } while (flag);
            lcd.clear();
            limite = seg + minutos * 60 + hora * 60 * 60;
            _seg = seg;
            _minutos = minutos;
            _hora = hora;
            ReiniciarTiempoBackLight();
            // TempActivo = true;
            break;
        }

        case 2:{
            seg2 = _seg2_On;
            minutos2 = _min2_On;
            hora2 = _hora2_On;
            do
            {
                switch (item)
                {
                case 1:
                {
                    lcd.clear();
                    lcd.setCursor(1, 0);
                    lcd.print("T2 ACTIV HORA");

                    ImprimirPuntosConf();
                    ImprimirSeg2();
                    ImprimirMin2();
                    ImprimirHora2();
                    while (true)
                    {
                        VerificarBtnEmergencia();
                        estadoBotonAnterior = estadoBtnMas;
                        estadoBtnMas = digitalRead(btnMas);
                        if (estadoBtnMas != estadoBotonAnterior)
                        {
                            if (antirebote(btnMas))
                            { //checamos  si esta preionado y si lo esta
                                hora2++;
                                if (hora2 > 24)
                                {
                                    hora2 = 0;
                                }
                                ImprimirHora2();
                            }
                        }

                        estadoBotonAnterior = estadoBtnMin;
                        estadoBtnMin = digitalRead(btnMin);
                        if (estadoBtnMin != estadoBotonAnterior)
                        {
                            if (antirebote(btnMin))
                            { //checamos  si esta preionado y si lo esta
                                hora2--;
                                if (hora2 < 0)
                                {
                                    hora2 = 24;
                                }
                                ImprimirHora2();
                            }
                        }

                        estadoBotonAnterior = estadoBtnInicioPara;
                        estadoBtnInicioPara = digitalRead(btnInicioPara);
                        if (estadoBtnInicioPara != estadoBotonAnterior)
                        {
                            if (antirebote(btnInicioPara))
                            {
                                temp_estado = 2;
                                break;
                            }
                        }

                        estadoBotonAnterior = estadoBtnConfig;
                        estadoBtnConfig = digitalRead(btnConfig);
                        if (estadoBtnConfig != estadoBotonAnterior)
                        {
                            if (antirebote(btnConfig))
                            {
                                // goto case 2;
                                item = 2;
                                temp_estado = 1;
                                break;
                            }
                        }
                    }
                    break;
                }

                case 2:
                {
                    lcd.clear();
                    lcd.setCursor(1, 0);
                    lcd.print("T2 ACTIV MIN");

                    ImprimirPuntosConf();
                    ImprimirSeg2();
                    ImprimirMin2();
                    ImprimirHora2();
                    while (true)
                    {
                        VerificarBtnEmergencia();
                        estadoBotonAnterior = estadoBtnMas;
                        estadoBtnMas = digitalRead(btnMas);
                        if (estadoBtnMas != estadoBotonAnterior)
                        {
                            if (antirebote(btnMas))
                            { //checamos  si esta preionado y si lo esta
                                minutos2++;
                                if (minutos2 > 59)
                                {
                                    minutos2 = 0;
                                }
                                ImprimirMin2();
                            }
                        }

                        estadoBotonAnterior = estadoBtnMin;
                        estadoBtnMin = digitalRead(btnMin);
                        if (estadoBtnMin != estadoBotonAnterior)
                        {
                            if (antirebote(btnMin))
                            { //checamos  si esta preionado y si lo esta
                                minutos2--;
                                if (minutos2 < 0)
                                {
                                    minutos2 = 59;
                                }
                                ImprimirMin2();
                            }
                        }

                        estadoBotonAnterior = estadoBtnInicioPara;
                        estadoBtnInicioPara = digitalRead(btnInicioPara);
                        if (estadoBtnInicioPara != estadoBotonAnterior)
                        {
                            if (antirebote(btnInicioPara))
                            {
                                temp_estado = 2;
                                break;
                            }
                        }

                        estadoBotonAnterior = estadoBtnConfig;
                        estadoBtnConfig = digitalRead(btnConfig);
                        if (estadoBtnConfig != estadoBotonAnterior)
                        {
                            if (antirebote(btnConfig))
                            {
                                item = 3;
                                temp_estado = 1;
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
                    lcd.print("T2 ACTIV SEG");

                    ImprimirPuntosConf();
                    ImprimirSeg2();
                    ImprimirMin2();
                    ImprimirHora2();
                    while (true)
                    {
                        VerificarBtnEmergencia();

                        estadoBotonAnterior = estadoBtnMas;
                        estadoBtnMas = digitalRead(btnMas);
                        if (estadoBtnMas != estadoBotonAnterior)
                        {
                            if (antirebote(btnMas))
                            { //checamos  si esta preionado y si lo esta
                                seg2++;
                                if (seg2 > 59)
                                {
                                    seg2 = 0;
                                }
                                ImprimirSeg2();
                            }
                        }

                        estadoBotonAnterior = estadoBtnMin;
                        estadoBtnMin = digitalRead(btnMin);
                        if (estadoBtnMin != estadoBotonAnterior)
                        {
                            if (antirebote(btnMin))
                            { //checamos  si esta preionado y si lo esta
                                seg2--;
                                if (seg2 < 0)
                                {
                                    seg2 = 59;
                                }
                                ImprimirSeg2();
                            }
                        }

                        estadoBotonAnterior = estadoBtnInicioPara;
                        estadoBtnInicioPara = digitalRead(btnInicioPara);
                        if (estadoBtnInicioPara != estadoBotonAnterior)
                        {
                            if (antirebote(btnInicioPara))
                            {
                                temp_estado = 2;
                                break;
                            }
                        }

                        estadoBotonAnterior = estadoBtnConfig;
                        estadoBtnConfig = digitalRead(btnConfig);
                        if (estadoBtnConfig != estadoBotonAnterior)
                        {
                            if (antirebote(btnConfig))
                            {
                                item = 1;
                                temp_estado = 1;
                                break;
                            }
                        }
                    }
                    break;
                }
                }
            } while (temp_estado == 1);
            temp2_encendido = seg2 + minutos2 * 60 + hora2 * 60 * 60;
            limite2 = temp2_encendido;
            _seg2_On = seg2;
            _min2_On = minutos2;
            _hora2_On = hora2;

            seg2 = _seg2_Off;
            minutos2 = _min2_Off;
            hora2 = _hora2_Off;

            do
            {
                switch (item)
                {
                case 1:
                {
                    lcd.clear();
                    lcd.setCursor(1, 0);
                    lcd.print("T2 DESACT HORA");

                    ImprimirPuntosConf();
                    ImprimirSeg2();
                    ImprimirMin2();
                    ImprimirHora2();
                    while (true)
                    {
                        VerificarBtnEmergencia();
                        estadoBotonAnterior = estadoBtnMas;
                        estadoBtnMas = digitalRead(btnMas);
                        if (estadoBtnMas != estadoBotonAnterior)
                        {
                            if (antirebote(btnMas))
                            { //checamos  si esta preionado y si lo esta
                                hora2++;
                                if (hora2 > 24)
                                {
                                    hora2 = 0;
                                }
                                ImprimirHora2();
                            }
                        }

                        estadoBotonAnterior = estadoBtnMin;
                        estadoBtnMin = digitalRead(btnMin);
                        if (estadoBtnMin != estadoBotonAnterior)
                        {
                            if (antirebote(btnMin))
                            { //checamos  si esta preionado y si lo esta
                                hora2--;
                                if (hora2 < 0)
                                {
                                    hora2 = 24;
                                }
                                ImprimirHora2();
                            }
                        }

                        estadoBotonAnterior = estadoBtnInicioPara;
                        estadoBtnInicioPara = digitalRead(btnInicioPara);
                        if (estadoBtnInicioPara != estadoBotonAnterior)
                        {
                            if (antirebote(btnInicioPara))
                            {
                                temp_estado = 1;
                                break;
                            }
                        }

                        estadoBotonAnterior = estadoBtnConfig;
                        estadoBtnConfig = digitalRead(btnConfig);
                        if (estadoBtnConfig != estadoBotonAnterior)
                        {
                            if (antirebote(btnConfig))
                            {
                                // goto case 2;
                                item = 2;
                                temp_estado = 2;
                                break;
                            }
                        }
                    }
                    break;
                }

                case 2:
                {
                    lcd.clear();
                    lcd.setCursor(1, 0);
                    lcd.print("T2 DESACT MIN");

                    ImprimirPuntosConf();
                    ImprimirSeg2();
                    ImprimirMin2();
                    ImprimirHora2();
                    while (true)
                    {
                        VerificarBtnEmergencia();
                        estadoBotonAnterior = estadoBtnMas;
                        estadoBtnMas = digitalRead(btnMas);
                        if (estadoBtnMas != estadoBotonAnterior)
                        {
                            if (antirebote(btnMas))
                            { //checamos  si esta preionado y si lo esta
                                minutos2++;
                                if (minutos2 > 59)
                                {
                                    minutos2 = 0;
                                }
                                ImprimirMin2();
                            }
                        }

                        estadoBotonAnterior = estadoBtnMin;
                        estadoBtnMin = digitalRead(btnMin);
                        if (estadoBtnMin != estadoBotonAnterior)
                        {
                            if (antirebote(btnMin))
                            { //checamos  si esta preionado y si lo esta
                                minutos2--;
                                if (minutos2 < 0)
                                {
                                    minutos2 = 59;
                                }
                                ImprimirMin2();
                            }
                        }

                        estadoBotonAnterior = estadoBtnInicioPara;
                        estadoBtnInicioPara = digitalRead(btnInicioPara);
                        if (estadoBtnInicioPara != estadoBotonAnterior)
                        {
                            if (antirebote(btnInicioPara))
                            {
                                temp_estado = 1;
                                break;
                            }
                        }

                        estadoBotonAnterior = estadoBtnConfig;
                        estadoBtnConfig = digitalRead(btnConfig);
                        if (estadoBtnConfig != estadoBotonAnterior)
                        {
                            if (antirebote(btnConfig))
                            {
                                item = 3;
                                temp_estado = 2;
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
                    lcd.print("T2 DESAC SEG");

                    ImprimirPuntosConf();
                    ImprimirSeg2();
                    ImprimirMin2();
                    ImprimirHora2();
                    while (true)
                    {
                        VerificarBtnEmergencia();

                        estadoBotonAnterior = estadoBtnMas;
                        estadoBtnMas = digitalRead(btnMas);
                        if (estadoBtnMas != estadoBotonAnterior)
                        {
                            if (antirebote(btnMas))
                            { //checamos  si esta preionado y si lo esta
                                seg2++;
                                if (seg2 > 59)
                                {
                                    seg2 = 0;
                                }
                                ImprimirSeg2();
                            }
                        }

                        estadoBotonAnterior = estadoBtnMin;
                        estadoBtnMin = digitalRead(btnMin);
                        if (estadoBtnMin != estadoBotonAnterior)
                        {
                            if (antirebote(btnMin))
                            { //checamos  si esta preionado y si lo esta
                                seg2--;
                                if (seg2 < 0)
                                {
                                    seg2 = 59;
                                }
                                ImprimirSeg2();
                            }
                        }

                        estadoBotonAnterior = estadoBtnInicioPara;
                        estadoBtnInicioPara = digitalRead(btnInicioPara);
                        if (estadoBtnInicioPara != estadoBotonAnterior)
                        {
                            if (antirebote(btnInicioPara))
                            {
                                temp_estado = 1;
                                break;
                            }
                        }

                        estadoBotonAnterior = estadoBtnConfig;
                        estadoBtnConfig = digitalRead(btnConfig);
                        if (estadoBtnConfig != estadoBotonAnterior)
                        {
                            if (antirebote(btnConfig))
                            {
                                item = 1;
                                temp_estado = 2;
                                break;
                            }
                        }
                    }
                    break;
                }
                }
            } while (temp_estado == 2);

            lcd.clear();
            temp2_apagado = seg2 + minutos2 * 60 + hora2 * 60 * 60;
            _seg2_Off = seg2;
            _min2_Off = minutos2;
            _hora2_Off = hora2;
            ReiniciarTiempoBackLight();
            break;
        }
    }
}

void VerificarBtnEmergencia()
{
    if (digitalRead(btnEmergencia) == EstadoEmergencia)
    {
        Emergencia = true;
        TempActivo = false; //desactiva el temporizador siempre
        noInterrupts();
        digitalWrite(outEmergencia, LOW); //activa pin de emergencia
        digitalWrite(outTiempo, HIGH);    //desactiva pin de tiempo
        digitalWrite(outFinalTiempo, HIGH);
        hora = _hora;
        minutos = _minutos;
        seg = _seg;
        hora2 = _hora2_On;
        minutos2 = _min2_On;
        seg2 = _seg2_On;

        limite = seg + minutos * 60 + hora * 60 * 60;
        limite2 = temp2_encendido;
        contador = 0;
        contador2 = 0;
        
        ReiniciarTiempoBackLight();
        ImprimirEstado();
        while (digitalRead(btnEmergencia) == EstadoEmergencia)
        {
            if (digitalRead(btnEmergencia) == !EstadoEmergencia)
            {
                break;
            }
        }
        Emergencia = false;
        digitalWrite(outEmergencia, HIGH);
        ReiniciarTiempoBackLight();
        // ConfigurarTiempos();
        ElegirTemporizador();
        ImprimirEstado();
    }
}

void VerificarEstadoTemporizador()
{
    if (TempActivo)
    {
        // digitalWrite(outTiempo, LOW);
        interrupts();
        // ImprimirEstado();
    }
    else
    {
        // digitalWrite(outTiempo, HIGH);
        noInterrupts();
        // ImprimirEstado();
    }
}

void LimpiarVariables()
{
    hora = _hora;
    minutos = _minutos;
    seg = _seg;
    limite = 0;
    contador = 0;
    ReiniciarTiempoBackLight();
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
