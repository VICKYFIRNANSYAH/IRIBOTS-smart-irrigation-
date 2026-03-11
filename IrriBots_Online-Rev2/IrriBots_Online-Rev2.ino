//Penyiram tanaman otomatis
#define BLYNK_DEBUG
#define BLYNK_TEMPLATE_ID "TMPL6TWnbBtLd"  // Ganti dengan Template ID dari Blynk
#define BLYNK_TEMPLATE_NAME "IrriBotS Ard"  // Ganti dengan nama template
#define BLYNK_AUTH_TOKEN "ks-Hq3yVasEpOJdABI9xjFk18J0fJJyX5"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <ESP8266_Lib.h>

// Konfigurasi WiFi & Blynk
#define BLYNK_PRINT Serial
SoftwareSerial espSerial(13, 12); // RX, TX untuk ESP-01
char* ssid = "AndroidShare";     //nama WiFi / Hotspot
char* pass = "11223344";     //password WiFi / Hotspot
ESP8266 wifi(&espSerial);  // Gunakan objek ESP8266

//Konfigurasi LCD
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

  Serial.begin(9600);   // Serial Monitor
  espSerial.begin(9600); // ESP-01 default baud rate
  Serial.println("Menghubungkan ke WiFi...");
  setWifi(ssid, pass);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass, "blynk.cloud", 80);

pinMode(pinDigital, INPUT);   //pin A0 sebagai input
pinMode(relay, OUTPUT);       //pin 6 sebagai output
pinMode(alarm, OUTPUT);
pinMode(ledGreen, OUTPUT);    //pin 7 sebagai output
pinMode(ledYellow, OUTPUT);   //pin 8 sebagai output
pinMode(ledRed, OUTPUT);      //pin 9 sebagai output
}

void setWifi(char* ssid, char* pass) {
  espSerial.println("AT"); // Cek apakah ESP-01 aktif
  delay(1000);

  espSerial.println("AT+CWMODE=1"); // Mode station
  delay(1000);

  String command = "AT+CWJAP=\"" + String(ssid) + "\",\"" + String(pass) + "\"";
  espSerial.println(command); // Sambungkan ke WiFi
  delay(5000);

  Serial.println("ESP-01 Terhubung ke WiFi");
}


void loop() {
Blynk.run();
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
  if (espSerial.available()) {
    Serial.write(espSerial.read()); // Tampilkan data dari ESP-01
  }
}
