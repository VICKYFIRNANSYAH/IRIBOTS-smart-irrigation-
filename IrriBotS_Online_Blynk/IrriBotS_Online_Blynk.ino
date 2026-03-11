//SISTEM PENYIRAMAN TANAMAN OTOMATIS MENGGUNAKAN BLYNK SERVER
//BY MUHAMMAD VICKY FIRNANSYAH 
//https://github.com/VICKYFIRNANSYAH

#define BLYNK_TEMPLATE_ID "TMPL6TWnbBtLd"
#define BLYNK_TEMPLATE_NAME "IrriBotS Ard"
#define BLYNK_AUTH_TOKEN "ks-Hq3yVasEpOJdABI9xjFk18J0fJJyX"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <ESP8266_Lib.h>

// Konfigurasi WiFi & Blynk
#define BLYNK_PRINT Serial
SoftwareSerial EspSerial(3, 2); // RX, TX untuk ESP-01
char ssid[] = "ArdShare";
char pass[] = "11223344";
ESP8266 wifi(&EspSerial);

// Konfigurasi LCD & Sensor
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinDigital = A0;
const int relay = 4;
const int alarm = 5;
const int ledGreen = 6;
const int ledYellow = 7;
const int ledRed = 8;

bool manualControl = false; // Mode manual atau otomatis

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  EspSerial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass, "blynk.cloud", 80);

  pinMode(pinDigital, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(alarm, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
}

BLYNK_WRITE(V1) { // Baca input tombol dari Blynk
  int buttonState = param.asInt();
  if (buttonState == 1) {
    manualControl = true;
    digitalWrite(relay, HIGH); // Nyalakan pompa
  } else {
    manualControl = false;
  }
}


void loop() {
  Blynk.run();
  int dataAnalog = analogRead(pinDigital); //membaca nilai dari pin sensor
  Serial.print("A0 : ");
  Serial.print(dataAnalog);

  Blynk.virtualWrite(V0, dataAnalog);   // Kirim data sensor ke Blynk

 if (!manualControl) { // Jika mode manual tidak aktif
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

        // Indikator LED di Blynk
      Blynk.virtualWrite(V2, 255); // LED Hijau ON
      Blynk.virtualWrite(V3, 0);
      Blynk.virtualWrite(V4, 0);
  }

 //tetapi, jika nilai A0 kurang dari 900, print kata serta nyalakan led kuning dan relay kemudian matikan led hijau dan juga merah
  else if (dataAnalog >= 500 && dataAnalog < 800) {
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

        // Indikator LED di Blynk
      Blynk.virtualWrite(V2, 0);
      Blynk.virtualWrite(V3, 255); // LED Kuning ON
      Blynk.virtualWrite(V4, 0);
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

        // Indikator LED di Blynk
      Blynk.virtualWrite(V2, 0);
      Blynk.virtualWrite(V3, 0);
      Blynk.virtualWrite(V4, 255); // LED Merah ON
  }
 }
  delay(500);
}
