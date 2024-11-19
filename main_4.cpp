  ///////   //     //   
 //     //  //    //  
 //     //  //   //   
 //     //  //  //    
 //     //  //   //     
 //     //  //     //     
  ///////   //      //
#include <WiFiServer.h>
#include <WiFi.h>

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

void TCP()
{
    if (cl.connected()) //Detecta se há clientes conectados no servidor
    {
        if (cl.available() > 0) //Verifica se o cliente conectado tem dados para serem lidos
        {
        digitalWrite(GPIO_NUM_2, 1);
        byte received;
        received = cl.read();
        float erro = (float)byteToInt(received);
        int u = erro;
        byte byteToSend = intToByte(u);
        cl.write(byteToSend);
        }
    }
    else //Se nao houver cliente conectado
    {
        digitalWrite(GPIO_NUM_2, !digitalRead(GPIO_NUM_2));
        cl = sv.available(); //Disponabiliza o servidor para o cliente se conectar
        delay(50);
    }
}
void TCP_1()
{
    if (cl_1.connected()) //Detecta se há clientes conectados no servidor
    {
        if (cl_1.available() > 0) //Verifica se o cliente conectado tem dados para serem lidos
        {
        digitalWrite(GPIO_NUM_2, 1);
        byte received_1;
        received_1 = cl_1.read();
        float erro_1 = (float)byteToInt(received_1);
        int u_1 = erro_1;
        byte byteToSend_1 = intToByte(u_1);
        cl_1.write(byteToSend_1);
        }
    }
    else //Se nao houver cliente conectado
    {
        digitalWrite(GPIO_NUM_2, !digitalRead(GPIO_NUM_2));
        cl_1 = sv_1.available(); //Disponabiliza o servidor para o cliente se conectar
        delay(50);
    }
}
void TCP_2()
{
    if (cl_2.connected()) //Detecta se há clientes conectados no servidor
    {
        if (cl_2.available() > 0) //Verifica se o cliente conectado tem dados para serem lidos
        {
        digitalWrite(GPIO_NUM_2, 1);
        byte received_2;
        received_2 = cl_2.read();
        float erro_2 = (float)byteToInt(received_2);
        int u_2 = erro_2;
        byte byteToSend_2 = intToByte(u_2);
        cl_2.write(byteToSend_2);
        }
    }
    else //Se nao houver cliente conectado
    {
        digitalWrite(GPIO_NUM_2, !digitalRead(GPIO_NUM_2));
        cl_2 = sv_2.available(); //Disponabiliza o servidor para o cliente se conectar
        delay(50);
    }
}
void TCP_3()
{
    if (cl_3.connected()) //Detecta se há clientes conectados no servidor
    {
        if (cl_3.available() > 0) //Verifica se o cliente conectado tem dados para serem lidos
        {
        digitalWrite(GPIO_NUM_2, 1);
        byte received_3;
        received_3 = cl_3.read();
        float erro_3 = (float)byteToInt(received_3);
        int u_3 = erro_3;
        byte byteToSend_3 = intToByte(u_3);
        cl_3.write(byteToSend_3);
        }
    }
    else //Se nao houver cliente conectado
    {
        digitalWrite(GPIO_NUM_2, !digitalRead(GPIO_NUM_2));
        cl_3 = sv_3.available(); //Disponabiliza o servidor para o cliente se conectar
        delay(50);
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
}

void loop()
{
    TCP(); //Funçao que gerencia os pacotes e clientes TCP.
    TCP_1();
    TCP_2();
    TCP_3();
}

