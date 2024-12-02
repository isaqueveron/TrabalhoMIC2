#include <Arduino.h>
#include <WiFiServer.h>
#include <WiFi.h>
#include <math.h>

int Negative_handle(int x)
{
    if(x>128)
    {
        int r;
        r = x - 256;
        return r;
    }
    else{return x;}
}

float Inversa_erro_x(float x)
{
    x = (x*305 + 37465)/254;
    return x;
}

float Inversa_erro_y(float x)
{
    x = (x*55 - 5715)/254;
    return x;
}

float Inversa(float x)
{
    x = x*20/127;
    return x;
}

WiFiServer sv(5000);//Cria o objeto servidor na porta 5000
WiFiClient cl;  //Cria o objeto cliente.
WiFiServer sv_1(5001); 
WiFiClient cl_1;      
WiFiServer sv_2(5002); 
WiFiClient cl_2;  
WiFiServer sv_3(5003); 
WiFiClient cl_3;  

int byteToInt(byte byteValue) {
    return (int)byteValue;
}

byte intToByte(int8_t intValue) {
    return (byte)intValue;
}

float X_ERRO;
float Y_ERRO;
float X_VELO;
float Y_VELO;
int Lim_ay = 20;
int Lim_ax = 20;
float Ax;
float Ay;
int ux_ToSend;
int uy_ToSend;

void Control_X(float errox, float velox)
{
    Ax = 6*(errox*2) - 6*(velox*0.8);
    if(Ax>Lim_ax){Ax=Lim_ax;}
    if(Ax<-Lim_ax){Ax=-Lim_ax;}
    Ax = Ax*127/20;
    ux_ToSend = (int)Ax;
}

void Control_Y(float erroy, float veloy)
{
    Ay = 3*(erroy*0.35) - 3*(veloy);
    Ay = Ay + 9.8;
    if(Ay>Lim_ay){Ay=Lim_ay;}
    if(Ay<-Lim_ay){Ay=-Lim_ay;}
    Ay = Ay*127/20;
    uy_ToSend = (int)Ay;
}

void Erro_X()
{
    if (cl.connected()) //Detecta se há clientes conectados no servidor
    {
        if (cl.available() > 0) //Verifica se o cliente conectado tem dados para serem lidos
        {
        digitalWrite(GPIO_NUM_2, 1);
        byte received;
        received = cl.read();
        X_ERRO = Inversa_erro_x(Negative_handle((float)byteToInt(received)));
        byte byteToSend = intToByte(ux_ToSend);
        cl.write(byteToSend);
        }
    }
    else //Se nao houver cliente conectado
    {
        digitalWrite(GPIO_NUM_2, !digitalRead(GPIO_NUM_2));
        cl = sv.available(); //Disponabiliza o servidor para o cliente se conectar
        delay(100);
    }
}
void Erro_Y()
{
    if (cl_1.connected()) //Detecta se há clientes conectados no servidor
    {
        if (cl_1.available() > 0) //Verifica se o cliente conectado tem dados para serem lidos
        {
        digitalWrite(GPIO_NUM_2, 1);
        byte received_1;
        received_1 = cl_1.read();
        Y_ERRO = Inversa_erro_y(Negative_handle((float)byteToInt(received_1)));
        byte byteToSend_1 = intToByte(uy_ToSend);
        cl_1.write(byteToSend_1);
        }
    }
    else //Se nao houver cliente conectado
    {
        digitalWrite(GPIO_NUM_2, !digitalRead(GPIO_NUM_2));
        cl_1 = sv_1.available(); //Disponabiliza o servidor para o cliente se conectar
        delay(100);
    }
}
void VELO_X()
{
    if (cl_2.connected()) //Detecta se há clientes conectados no servidor
    {
        if (cl_2.available() > 0) //Verifica se o cliente conectado tem dados para serem lidos
        {
        digitalWrite(GPIO_NUM_2, 1);
        byte received_2;
        received_2 = cl_2.read();
        X_VELO = Inversa(Negative_handle((float)byteToInt(received_2)));
        int u_2 = 0;
        byte byteToSend_2 = intToByte(u_2);
        cl_2.write(byteToSend_2);
        }
    }
    else //Se nao houver cliente conectado
    {
        digitalWrite(GPIO_NUM_2, !digitalRead(GPIO_NUM_2));
        cl_2 = sv_2.available(); //Disponabiliza o servidor para o cliente se conectar
        delay(100);
    }
}
void VELO_Y()
{
    if (cl_3.connected()) //Detecta se há clientes conectados no servidor
    {
        if (cl_3.available() > 0) //Verifica se o cliente conectado tem dados para serem lidos
        {
        digitalWrite(GPIO_NUM_2, 1);
        byte received_3;
        received_3 = cl_3.read();
        Y_VELO = Inversa(Negative_handle((float)byteToInt(received_3)));
        int u_3 = 0;
        byte byteToSend_3 = intToByte(u_3);
        cl_3.write(byteToSend_3);
        }
    }
    else //Se nao houver cliente conectado
    {
        digitalWrite(GPIO_NUM_2, !digitalRead(GPIO_NUM_2));
        cl_3 = sv_3.available(); //Disponabiliza o servidor para o cliente se conectar
        delay(100);
    }
}

void setup()
{
    pinMode(GPIO_NUM_2, OUTPUT);
    WiFi.mode(WIFI_AP);   //Define o WiFi como Acess_Point
    WiFi.softAP("NodeMCU", ""); //Cria a rede de Acess_Point
    sv.begin(); //Inicia o servidor TCP na porta declarada no começo (5000)
    sv_1.begin();
    sv_2.begin();
    sv_3.begin();
    
    
    //Serial.begin(9600);
}

void loop()
{
    Erro_X(); //Funçao que gerencia os pacotes e clientes TCP.
    Erro_Y();
    VELO_X();
    VELO_Y();
    Control_X(X_ERRO,X_VELO);
    Control_Y(Y_ERRO,Y_VELO);


    //Serial.print("Velocidade Y: ");
    //Serial.println();
}
