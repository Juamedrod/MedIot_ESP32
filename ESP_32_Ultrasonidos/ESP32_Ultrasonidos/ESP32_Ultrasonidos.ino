#include <HCSR04.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>


/* GLOBAL VARS */
const char *ssid = "MOVISTAR_42BE";
const char *password = "yR4reQ59TUn5eggk2ieq";
String dId= "esp32ultrasound";
UltraSonicDistanceSensor distanceSensor(13, 12);
double distance;

/*EXECUTED AT START*/
void setup()
{  
  delay(10);
  Serial.begin(115200); 
 
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
  distance=distanceSensor.measureDistanceCm();// Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
  String(distance);
  PostPetition();     
  delay(2000); 
}

void showInMeters(double distanceInCm){
  distance=distanceInCm/100;  
}

void PostPetition(){
    /*we prepare the JSON to send*/
    String output=SetUpJson();
  
    /*Instantiate httpClient*/
    HTTPClient http;
    
    /** SERVER API PATH **/
    http.begin("https://mediot.herokuapp.com/api/data/"+dId);
    
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
    variables["ultrasonidos"]= distance;
    
    /* JSON SERIALIZE AND SAVE IT IN OUTPUT*/
    serializeJson(doc, output); 
    doc.clear();  
    return output;
}
