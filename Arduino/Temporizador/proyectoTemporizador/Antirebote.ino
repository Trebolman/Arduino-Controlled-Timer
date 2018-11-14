/* Practica 6 - Función antirebote
 Funcion antirebote para leer correctamente
 el estado del boton */

const int boton = 15; // boton conectado al pin 4
const int tiempoAntirebote = 10;

int cuenta = 0; //Guarda el numero de veces que el boton ha sido presionado
int estadoBoton;
int estadoBotonAnterior;

/*Función antirebote*/
boolean antirebote(int pin)
{
    int contador = 0;
    boolean estado;         // guarda el estado del boton
    boolean estadoAnterior; // guarda el ultimo estado del boton

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

void setup()
{
    Serial.begin(9600);    //Iniciamos la comunicacion serial
    pinMode(boton, INPUT); //declaramos el boton como entrada
}

void loop()
{
    estadoBoton = digitalRead(boton); //leemos el estado del boton
    if (estadoBoton != estadoBotonAnterior)
    { //si hay cambio con respeto al estado
        if (antirebote(boton))
        {             //checamos  si esta preionado y si lo esta
            cuenta++; //aumentamos la cuenta
            Serial.println(cuenta);
        }
    }
    estadoBotonAnterior = estadoBoton; // guardamos el estado del boton
}