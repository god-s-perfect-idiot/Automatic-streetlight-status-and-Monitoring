/*
 * Interface LDR with NodeMCU
 * By TheCircuit
 */
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

long distance,duration;
const int ledPin = 5;
const int ldrPin = A0;
const int trigPin = 14;  //D5
const int echoPin = 12;  //D6

void setup() {

Serial.begin(9600);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
//pinMode(17,INPUT);
pinMode(ldrPin, INPUT);
  WiFi.begin("Le2", "1234567890");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }

 }


void callIFTTT(){
  
 if(WiFi.status()== WL_CONNECTED){//Check WiFi connection status
 int ldrStatus = analogRead(ldrPin);
 Serial.println("Connected");
 if(ldrStatus<=20){
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://maker.ifttt.com/trigger/nitt/with/key/prW1-nT0CRhzPXNMihaXDOvq2MyFCv8MDxqfe8v21lW");      //Specify request destination
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
   int httpCode = http.POST("Message from ESP8266");   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }
 else{
  Serial.println("Connected");
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://maker.ifttt.com/trigger/day/with/key/prW1-nT0CRhzPXNMihaXDOvq2MyFCv8MDxqfe8v21lW");      //Specify request destination
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
   int httpCode2 = http.POST("Message from ESP8266");   //Send the request
   String payload2 = http.getString();                  //Get the response payload
 
   Serial.println(httpCode2);   //Print HTTP return code
   Serial.println(payload2);    //Print request response payload
 
   http.end();  //Close connection
 }
 }
 else{
    Serial.println("Error in WiFi connection");   
     
 }
}

void loop() {
int ldrStatus = analogRead(ldrPin);

if (ldrStatus <=20) {
    long state = digitalRead(17);
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(20);
    if(distance<20){
      digitalWrite(ledPin,HIGH);
      Serial.println("Motion detected!");
    }

  else{
    analogWrite(ledPin, 50);

    Serial.print(ldrStatus);
    Serial.println("LDR is DARK, LED is ON");
  }
}

else {

digitalWrite(ledPin, LOW);
Serial.println("LED is OFF");

}
callIFTTT();
}
