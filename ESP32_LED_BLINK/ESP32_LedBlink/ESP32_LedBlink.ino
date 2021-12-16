#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define LED 21
#define LED2 22
#define LED3 23

/* GLOBAL VARS */
const char *ssid = "MOVISTAR_42BE";
const char *password = "yR4reQ59TUn5eggk2ieq";
String dId= "tempestira";
String bulb="false";
String bulb2="false";
String bulb3="false";

/*EXECUTED AT START*/
void setup()
{
  delay(10);
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  WiFi.begin(ssid, password);

  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED)
  { //Check for the connection
    delay(500);
    Serial.print(".");
  }
  
  Serial.print("Conectado con éxito, mi IP es: ");
  Serial.println(WiFi.localIP());
}

/*MAIN LOOP FOR THE APP*/
void loop()
{
  /*Check WiFi connection status IS WORKING*/
  if (WiFi.status() == WL_CONNECTED)
  {   
    GetPetition();
    GetPetition2();
    GetPetition3();
  }
  else
  {
    Serial.println("Error en la conexión WIFI");
  }
    
  Serial.println("bulb es "+bulb);
  if(bulb=="true"){
    digitalWrite(LED,HIGH); 
  }else{
    digitalWrite(LED,LOW);
  }

  Serial.println("bulb es "+bulb2);
  if(bulb2=="true"){
    digitalWrite(LED2,HIGH); 
  }else{
    digitalWrite(LED2,LOW);
  }

  Serial.println("bulb es "+bulb3);
  if(bulb3=="true"){
    digitalWrite(LED3,HIGH); 
  }else{
    digitalWrite(LED3,LOW);
  }
  
  delay(2000); 
}

void GetPetition(){
    /*Instantiate httpClient*/
    HTTPClient http;
  
    http.begin("http://192.168.1.39:3000/api/data/boolean/"+dId+"/bulb");
    
    /*WE SET THE HEADERS FOR THE PETITION, THIS IS KEY TO HAVE A GOOD DATA CORRELATION BETWEEN THE DEVICE AND THE SERVER*/
    http.addHeader("Content-Type", "application/json; charset=utf-8"); 

    /*WE SEND THE PETITION TO THE API AND RECOVER THE API RESPONSE*/
    int codigo_respuesta = http.GET();
    
     /* RESOLVE THE PETITION RESPONSE */
    if (codigo_respuesta > 0)
    {     
      if (codigo_respuesta == 200)
      {
        bulb = http.getString();        
        Serial.println(bulb);                     
      }
    } 

    /*FREE RESOURCES*/   
    http.end(); //libero recursos
}

void GetPetition2(){
    /*Instantiate httpClient*/
    HTTPClient http;
  
    http.begin("http://192.168.1.39:3000/api/data/boolean/"+dId+"/bulb2");
    
    /*WE SET THE HEADERS FOR THE PETITION, THIS IS KEY TO HAVE A GOOD DATA CORRELATION BETWEEN THE DEVICE AND THE SERVER*/
    http.addHeader("Content-Type", "application/json; charset=utf-8"); 

    /*WE SEND THE PETITION TO THE API AND RECOVER THE API RESPONSE*/
    int codigo_respuesta = http.GET();
    
     /* RESOLVE THE PETITION RESPONSE */
    if (codigo_respuesta > 0)
    {     
      if (codigo_respuesta == 200)
      {
        bulb2 = http.getString();        
        Serial.println(bulb);                     
      }
    } 

    /*FREE RESOURCES*/   
    http.end(); //libero recursos
}

void GetPetition3(){
    /*Instantiate httpClient*/
    HTTPClient http;
  
    http.begin("http://192.168.1.39:3000/api/data/boolean/"+dId+"/bulb3");
    
    /*WE SET THE HEADERS FOR THE PETITION, THIS IS KEY TO HAVE A GOOD DATA CORRELATION BETWEEN THE DEVICE AND THE SERVER*/
    http.addHeader("Content-Type", "application/json; charset=utf-8"); 

    /*WE SEND THE PETITION TO THE API AND RECOVER THE API RESPONSE*/
    int codigo_respuesta = http.GET();
    
     /* RESOLVE THE PETITION RESPONSE */
    if (codigo_respuesta > 0)
    {     
      if (codigo_respuesta == 200)
      {
        bulb3 = http.getString();        
        Serial.println(bulb);                     
      }
    } 

    /*FREE RESOURCES*/   
    http.end(); //libero recursos
}
