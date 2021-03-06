#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define LED 21

/* GLOBAL VARS */
const char *ssid = "MOVISTAR_42BE";
const char *password = "yR4reQ59TUn5eggk2ieq";
String dId= "tempestira";
float potValue = 0;
String bulb="false";

/*EXECUTED AT START*/
void setup()
{
  delay(10);
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
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
    PostPetition();
    GetPetition();
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
    
     /* RESOLVE THE PETITION RESPONSE*/
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

void PostPetition(){
    /*we prepare the JSON to send*/
    String output=SetUpJson();
  
    /*Instantiate httpClient*/
    HTTPClient http;
    
    /** SERVER API PATH **/
    http.begin("http://192.168.1.39:3000/api/data/"+dId);
    
    /*WE SET THE HEADERS FOR THE PETITION, THIS IS KEY TO HAVE A GOOD DATA CORRELATION BETWEEN THE DEVICE AND THE SERVER*/
    http.addHeader("Content-Type", "application/json; charset=utf-8"); 

    /*WE SEND THE PETITION TO THE API AND RECOVER THE API RESPONSE*/
    http.POST(output);
    
    /*FREE RESOURCES*/   
    http.end(); //libero recursos
}

String SetUpJson(){
  String output;
  StaticJsonDocument<2048> doc;
  JsonObject variables = doc.createNestedObject("variables");
   /**
     * JSON CONFIG TO SEND
    */ 
    doc["dId"] = dId;   
    variables["bulb"]= bulb;
    /* JSON SERIALIZE AND SAVE IT IN OUTPUT*/
    serializeJson(doc, output); 
    doc.clear();  
    return output;
}
