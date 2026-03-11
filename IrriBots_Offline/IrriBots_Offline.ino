#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Penyiram tanaman otomatis

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinDigital = A0; //inisialisasi pin sensor
const int relay = 2;       //inisialisasi pin relay
const int alarm = 3;
const int ledGreen = 8;    //inisialisasi pin led hijau
const int ledYellow = 7;   //inisialisasi pin led kuning
const int ledRed = 6;      //inisialisasi pin hijau

void setup() {
Serial.begin (9600);          //memanggil serial monitor
  lcd.begin();
  lcd.backlight();
pinMode(pinDigital, INPUT);   //menetapkan pin A0 sebagai input
pinMode(relay, OUTPUT);       //menetapkan pin 6 sebagai output
pinMode(alarm, OUTPUT);
pinMode(ledGreen, OUTPUT);    //menetapkan pin 7 sebagai output
pinMode(ledYellow, OUTPUT);   //menetapkan pin 8 sebagai output
pinMode(ledRed, OUTPUT);      //menetapkan pin 9 sebagai output
}

void loop() {
int dataAnalog = analogRead (pinDigital);  //membaca nilai dari pin sensor
//print hasil ke serial monitor
Serial.print ("A0 : ");
Serial.print (dataAnalog);

//jika nilai A0 kurang dari 500, print kata serta nyalakan led hijau dan matikan led kuning, merah dan juga relay
if (dataAnalog < 500) { 
  Serial.println(". Media Masih Basah");
     lcd.setCursor(0, 0);
     lcd.print("Kondisi Tanah");
     lcd.setCursor(0, 1);
     lcd.print("Basah");
  digitalWrite (ledGreen, HIGH);
  digitalWrite (ledYellow, LOW);
  digitalWrite (ledRed, LOW);
  digitalWrite (relay, LOW);
  digitalWrite (alarm, LOW);
  }

 //tetapi, jika nilai A0 kurang dari 900, print kata serta nyalakan led kuning dan relay kemudian matikan led hijau dan juga merah
 else if (dataAnalog  < 800) {
  Serial.println(". Kelembaban Tanah Masih Cukup");
     lcd.setCursor(0, 0);
     lcd.print("Kondisi Tanah");
     lcd.setCursor(0, 1);
     lcd.print("Sedang");
  digitalWrite (ledGreen, LOW);
  digitalWrite (ledYellow, HIGH);
  digitalWrite (ledRed, LOW);
  digitalWrite (relay, HIGH);
  digitalWrite (alarm, HIGH);
  }

 //selain dari itu, hanya nyalakan led merah dan juga relay
 else { Serial.println (". Perlu Tambahan Air");
     lcd.setCursor(0, 0);
     lcd.print("Kondisi Tanah");
     lcd.setCursor(0, 1);
     lcd.print("Kering");
  digitalWrite (ledGreen, LOW);
  digitalWrite (ledYellow, LOW);
  digitalWrite (ledRed, HIGH);
  digitalWrite (relay, HIGH);
  digitalWrite (alarm,HIGH);
  }

 delay (500);
}
