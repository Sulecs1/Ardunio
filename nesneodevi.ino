
#include <ESP8266WiFi.h>
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

const char *myWriteAPIKey = "O3KN3Z0V7MOZWH7M";
unsigned long myChannelNumber = 1263962;
const char *ssid = "TurkTelekom_ZVRRJ";   //Wifi Adı
const char *pass = "f7d1eF5249959";  //Wifi Şifresi

WiFiClient client; 

const int s0=D4;   //Renk sensor pinleri tanımlandı
const int s1=D5;
const int s2=D6;
const int s3=D7;
const int out=D8;

int Kirmizi = 0;  
int Yesil = 0;  
int mavi = 0; 
int renk=0;
int kirmizirenk = 0;
int yesilrenk = 0;
int turuncurenk = 0;
int sarirenk = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);  

  ThingSpeak.begin(client);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
     {
            delay(550);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");

}

void loop() {
  // put your main code here, to run repeatedly:
  //Renkler için frekans değerlerini aldım
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  Kirmizi=pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  mavi=pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  Yesil=pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  
  Serial.print("R Intensity:");  
  Serial.print(Kirmizi, DEC);  
  Serial.print(" G Intensity: ");  
  Serial.print(Yesil, DEC);  
  Serial.print(" B Intensity : ");  
  Serial.print(mavi, DEC);  
  if(Kirmizi<39 & Kirmizi>29 & Yesil<93 & Yesil>83 &mavi<78 & mavi>69){
    //DagitServo.write(73);
    delay(700);
    kirmizirenk++;
    Serial.print("Kirmizi");
//    open1();
    delay(200);
  //  close1();
    ThingSpeak.writeField(myChannelNumber, 1,kirmizirenk, myWriteAPIKey);
    
  }
   if(Yesil<75 & Yesil>65 & mavi<68 &mavi>60){
    delay(700);
    turuncurenk++;
    Serial.print("Turuncu");
 
    delay(200);
    ThingSpeak.writeField(myChannelNumber, 2,turuncurenk, myWriteAPIKey);
   }
   if(Kirmizi<46 & Kirmizi>36 & Yesil<46 & Yesil>37){
  
    delay(700);
    yesilrenk++;
    Serial.print("Yeşil");
    delay(200);
    ThingSpeak.writeField(myChannelNumber, 3,yesilrenk, myWriteAPIKey);
  }
  if(Kirmizi<34 & Kirmizi>25 & Yesil<37 & Yesil>28 & mavi<53 & mavi>43){
    delay(700);
    sarirenk++;
    Serial.print("Sarı");
    delay(200);
    ThingSpeak.writeField(myChannelNumber, 4,sarirenk, myWriteAPIKey);
  } 
    Serial.println();  
   
  
}
