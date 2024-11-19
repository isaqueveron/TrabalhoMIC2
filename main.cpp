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
WiFiServer sv_1(5001); 
WiFiClient cl;  //Cria o objeto cliente.
WiFiClient cl_1;      

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

void setup()
{
    pinMode(GPIO_NUM_2, OUTPUT);
    WiFi.mode(WIFI_AP);   //Define o WiFi como Acess_Point
    WiFi.softAP("NodeMCU", ""); //Cria a rede de Acess_Point
    sv.begin(); //Inicia o servidor TCP na porta declarada no começo (5000)
    sv_1.begin();
}

void loop()
{
    TCP(); //Funçao que gerencia os pacotes e clientes TCP.
    TCP_1();
}

