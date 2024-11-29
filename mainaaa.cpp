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

float X_erro;
float X_vel;
float Y_erro;
float Y_vel;
int Ux;
float Uxmax=20;
float Uymax=20;

void Controle_X(){
    float erro = 305*X_erro;
    erro = erro + 37465;
    erro = erro/254;
    float velocidade = X_vel*20/127;
    float ux = 6*(erro*2)-6*(0.8*velocidade);
    //Serial.println(erro);
    //Serial.println(ux);
    //Serial.println(velocidade);
    if(ux>Uxmax){ux=Uxmax;}if(ux<-Uxmax){ux=-Uxmax;}
    Ux = ux*127/20;

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
        float x_erro = (float)byteToInt(received);
        if(x_erro>128){x_erro=x_erro-256;}
        //Serial.print(">");Serial.println(x_erro);
        X_erro = x_erro;
        Controle_X();
        byte byteToSend = intToByte(Ux);
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
void POS_Y()
{
    if (cl_1.connected()) //Detecta se há clientes conectados no servidor
    {
        if (cl_1.available() > 0) //Verifica se o cliente conectado tem dados para serem lidos
        {
        digitalWrite(GPIO_NUM_2, 1);
        byte received_1;
        received_1 = cl_1.read();
        float y_erro = (float)byteToInt(received_1);
        int u_1 = y_erro;
        byte byteToSend_1 = intToByte(u_1);
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
        float x_speed = (float)byteToInt(received_2);
        X_vel = x_speed;

        int u_2 = x_speed;
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
        float y_speed = (float)byteToInt(received_3);
        Y_vel = y_speed;
        //int u_3 = y_speed;
        //byte byteToSend_3 = intToByte(u_3);
        //cl_3.write(byteToSend_3);
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
    //Serial.begin(9600);
}

void loop()
{
    Erro_X(); //Funçao que gerencia os pacotes e clientes TCP.
    //POS_Y();
    VELO_X();
    //VELO_Y();
    //Serial.print("X_erro: ");
    //Serial.println(X_erro);
    //Serial.print("X_vel: ");
    //Serial.println(X_vel*20/127);
}
