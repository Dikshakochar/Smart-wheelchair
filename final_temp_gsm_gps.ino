#include<SoftwareSerial.h>
SoftwareSerial gsm(2,3);
 #include <TinyGPS++.h>
int sms_count;
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
float h;
float t;
float f;
String lt1, ln1, res;
TinyGPSPlus gps;
static const int RXPin =4 , TXPin = 5;
SoftwareSerial GPS(RXPin, TXPin);
void setup()
{
    dht.begin();
  delay(1000);
  gsm.begin(9600);
delay(1000);
 GPS.begin(9600);
 delay(1000);
}
void loop()
{
   while (GPS.available() > 0)
     if (gps.encode(GPS.read()))
   Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
      lt1= (gps.location.lat());
       ln1= (gps.location.lng());
         Serial.println("www.google.com/maps/@"+lt1+","+ln1+"");
  delay(2000);
  }
     float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("%  Temperature: "));
  Serial.println(t);
  delay(500);
    while(sms_count<2){
  delay(10000);
  Serial.begin(9600);
  gsm.begin(9600);
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CMGS=\"+917004222947\"\r"); //replace x by your number
  delay(1000);
  gsm.println("www.google.com/maps/@"+lt1+","+ln1+"");
   gsm.print(F("%  Temperature: "));
  gsm.println(t);
  delay(100);
  gsm.println((char)26);
  delay(1000);
  sms_count++;
}
}
