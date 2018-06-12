#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <SoftwareSerial.h>

SoftwareSerial ESP8266(10, 11);

String NomduReseauWifi = "ReseauWifi"; // Garder les guillements
String MotDePasse      = "MotDePasse"; // Garder les guillements

/****************************************************************/
/*                             INIT                             */
/****************************************************************/
void setup()
{
  Serial.begin(9600);
  ESP8266.begin(9600);
  initESP8266();
  envoieMessage("HELLO WORLD");
}
/****************************************************************/
/*                        BOUCLE INFINIE                        */
/****************************************************************/
void loop()
{
  while (ESP8266.available())
  {
    Serial.println(ESP8266.readString());
  }
}
/****************************************************************/
/*                Fonction qui initialise l'ESP8266             */
/****************************************************************/
void initESP8266()
{
  Serial.println("**********************************************************");
  Serial.println("**************** DEBUT DE L'INITIALISATION ***************");
  Serial.println("**********************************************************");
  envoieAuESP8266("AT");
  recoitDuESP8266(2000);
  Serial.println("**********************************************************");
  envoieAuESP8266("AT+RST");
  recoitDuESP8266(2000);
  Serial.println("**********************************************************");
  envoieAuESP8266("AT+CWMODE=3");
  recoitDuESP8266(5000);
  Serial.println("**********************************************************");
  envoieAuESP8266("AT+CWLAP");
  recoitDuESP8266(10000);
  Serial.println("**********************************************************");
  envoieAuESP8266("AT+CWJAP=\"" + NomduReseauWifi + "\",\"" + MotDePasse + "\"");
  recoitDuESP8266(10000);
  Serial.println("**********************************************************");
  envoieAuESP8266("AT+CIFSR");
  recoitDuESP8266(2000);
  Serial.println("**********************************************************");
  envoieAuESP8266("AT+CIPMUX=1");
  recoitDuESP8266(2000);
  Serial.println("**********************************************************");
  //envoieAuESP8266("AT+CIPSERVER=1,80");
  //recoitDuESP8266(2000);
  Serial.println("**********************************************************");
  Serial.println("***************** INITIALISATION TERMINEE ****************");
  Serial.println("**********************************************************");
  Serial.println("");
}

/****************************************************************/
/*        Fonction qui envoie une commande à l'ESP8266          */
/****************************************************************/
void envoieAuESP8266(String commande)
{
  ESP8266.println(commande);
}
/****************************************************************/
/*Fonction qui lit et affiche les messages envoyés par l'ESP8266*/
/****************************************************************/
void recoitDuESP8266(const int timeout)
{
  String reponse = "";
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (ESP8266.available())
    {
      char c = ESP8266.read();
      reponse += c;
    }
  }
  Serial.print(reponse);
}


void envoieMessage(String message){
  int long_mess = message.length();
  String longueur_message = String(long_mess);
  envoieAuESP8266("AT+SEND=0.\""+ longueur_message + "\"");
  envoieAuESP8266(message);
  recoitDuESP8266(1000);
  
}

