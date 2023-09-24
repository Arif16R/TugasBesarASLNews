#include <ESP8266HTTPClient.h>
#include<ESP8266Wifi.h>
#include <Servo.h>
#include "DHT.h"

#define triggerPin 12 //d6
#define echoPin 14//d5
long durasi;
int tinggi;

#define DHTTYPE DHT11
#define DHTPIN 5 //gpio5 //D1
#define pin_relay 13 //D7
#define pin_relay2 15 //D8

//#define pin_relay3 15   //D8

#define pin_servo 4   //D2
Servo myservo;
DHT dht(DHTPIN,DHTTYPE);

const char* ssid="rokhmad dot com";
const char* pass="1122334455";
const char* host="smkn2sragen.sch.id";






void setup(){
Serial.begin(9600);

pinMode (echoPin, INPUT);
pinMode (triggerPin, OUTPUT);

dht.begin();
WiFi.hostname("NodeMCU");
WiFi.begin(ssid,pass);
while(WiFi.status()!=WL_CONNECTED)
{
  Serial.print(".");
  delay(500);
}
 Serial.println("berhasil konek");
 dht.begin();

pinMode(pin_relay, OUTPUT);
digitalWrite(pin_relay,0);


pinMode(pin_relay2, OUTPUT);
digitalWrite(pin_relay2,0);

//pinMode(pin_relay3, OUTPUT);
//digitalWrite(pin_relay3,0);



 myservo.attach(pin_servo);
 myservo.write(0);
 
}
void loop(){


  
  float suhu=dht.readTemperature();
  int kelembaban=dht.readHumidity();
  Serial.println("suhu: "+ String(suhu));
  Serial.println("kelembaban: "+ String(kelembaban));
 //kirim ke server
WiFiClient client ;
  const int httpPort=80;
  if(!client.connect(host,httpPort))
  {
    Serial.println ("gagal Koneksi ke server");
    return;
  }
  //Serial.println("berhasil koneksi");

digitalWrite (triggerPin, LOW);
delayMicroseconds(2);
digitalWrite (triggerPin, HIGH);
delayMicroseconds(10);
digitalWrite (triggerPin, LOW);
durasi=pulseIn(echoPin, HIGH);
tinggi=durasi*0.034/2;
Serial.println(tinggi);
delay(1000);

  
String Link;
HTTPClient http;
Link="http://" +String(host)+ "/twosra-iot/kirimdata.php?suhu="+String(suhu)+"&kelembaban="+ String(kelembaban)+"&tinggi="+ String(tinggi);

http.begin(Link);
http.GET();
String response=http.getString();
Serial.println(response);
http.end();
delay(1000);

String LinkRelay;
HTTPClient httpRelay;
LinkRelay="http://" +String(host)+ "/twosra-iot/bacarelay.php";
httpRelay.begin(LinkRelay);
httpRelay.GET();
String responseRelay =httpRelay.getString();
Serial.println(responseRelay);
httpRelay.end();
digitalWrite(pin_relay,responseRelay.toInt());

////////////////////////////////////relay2
String LinkRelay2;
HTTPClient httpRelay2;
LinkRelay2="http://" +String(host)+ "/twosra-iot/bacarelay2.php";
httpRelay2.begin(LinkRelay2);
httpRelay2.GET();
String responseRelay2 =httpRelay2.getString();
Serial.println(responseRelay2);
httpRelay2.end();
digitalWrite(pin_relay2,responseRelay2.toInt());

/*
////////////////////////////////////relay3
String LinkRelay3;
HTTPClient httpRelay3;
LinkRelay3="http://" +String(host)+ "/twosra-iot/bacarelay3.php";
httpRelay3.begin(LinkRelay3);
httpRelay3.GET();
String responseRelay3 =httpRelay3.getString();
Serial.println(responseRelay3);
httpRelay3.end();
digitalWrite(pin_relay3,responseRelay3.toInt());

*/
///servo
String LinkServo;
HTTPClient httpServo;
LinkServo="http://" +String(host)+ "/twosra-iot/bacaservo.php";
httpServo.begin(LinkServo);
httpServo.GET();
String responseServo =httpServo.getString();
Serial.println(responseServo);
httpServo.end();
myservo.write(responseServo.toInt());



}

