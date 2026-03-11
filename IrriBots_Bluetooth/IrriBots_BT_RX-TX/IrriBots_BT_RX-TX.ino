#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial bt(2, 3); // RX, TX
//Penyiram tanaman otomatis

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int soil = A0; //inisialisasi pin sensor
const int relay = 4;       //inisialisasi pin relay
const int alarm = 5;
const int ledGreen = 6;    //inisialisasi pin led hijau
const int ledYellow = 7;   //inisialisasi pin led kuning
const int ledRed = 8;      //inisialisasi pin merah
int kel;                   //data di apk
char input_aplikasi = 0;

void setup() {
Serial.begin (9600);          //memanggil serial monitor
  lcd.begin();
  lcd.backlight();

bt.begin(9600); 

pinMode(soil, INPUT);   //menetapkan pin A0 sebagai input
pinMode(relay, OUTPUT);       //menetapkan pin 6 sebagai output
pinMode(alarm, OUTPUT);
pinMode(ledGreen, OUTPUT);    //menetapkan pin 7 sebagai output
pinMode(ledYellow, OUTPUT);   //menetapkan pin 8 sebagai output
pinMode(ledRed, OUTPUT);      //menetapkan pin 9 sebagai output
}

void loop() {
int dataAnalog = analogRead (soil);  //membaca nilai dari pin sensor
//print hasil ke serial monitor
Serial.print (dataAnalog);

//jika nilai A0 kurang dari 500, print kata serta nyalakan led hijau dan matikan led kuning, merah dan juga relay
if (dataAnalog < 500) { 
  Serial.println("");
  lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Kelembapan:");
     lcd.setCursor(12, 0);
     lcd.print(dataAnalog);
     lcd.setCursor(0,1);
     lcd.print("basah");

  digitalWrite (ledGreen, HIGH);
  digitalWrite (ledYellow, LOW);
  digitalWrite (ledRed, LOW);
  digitalWrite (relay, LOW);
  digitalWrite (alarm, LOW);
  }

 //tetapi, jika nilai A0 kurang dari 900, print kata serta nyalakan led kuning dan relay kemudian matikan led hijau dan juga merah
 else if (dataAnalog  < 800) {
  Serial.println("");
  lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Kelembapan:");
     lcd.setCursor(12, 0);
     lcd.print(dataAnalog);
     lcd.setCursor(0,1);
     lcd.print("Sedang");

  digitalWrite (ledGreen, LOW);
  digitalWrite (ledYellow, HIGH);
  digitalWrite (ledRed, LOW);
  digitalWrite (relay, HIGH);
  digitalWrite (alarm, HIGH);
  }

 //selain dari itu, hanya nyalakan led merah dan juga relay
 else { Serial.println ("");
  lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Kelembapan:");
     lcd.setCursor(12, 0);
     lcd.print(dataAnalog);
     lcd.setCursor(0,1);
     lcd.print("Kering");

  digitalWrite (ledGreen, LOW);
  digitalWrite (ledYellow, LOW);
  digitalWrite (ledRed, HIGH);
  digitalWrite (relay, HIGH);
  digitalWrite (alarm,HIGH);
  }

  if(Serial.available() > 0)  
  {
    input_aplikasi = Serial.read();      
    Serial.print(input_aplikasi);        
    Serial.print("\n");        
    if(input_aplikasi == '1')             
      digitalWrite(relay, HIGH);  
    else if(input_aplikasi == '0')       
      digitalWrite(relay, LOW);   
  }                            

 bt.print(kel); //send distance to MIT App
 bt.print(";");


 delay (1500);
}
