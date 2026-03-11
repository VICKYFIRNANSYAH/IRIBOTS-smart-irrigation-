//SISTEM PENYIRAMAN TANAMAN OTOMATIS MENGGUNAKAN BLYNK SERVER_SUDAH DI OPTIMALISASI
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

#define BLYNK_PRINT Serial

// Koneksi ESP-01 dengan Arduino melalui SoftwareSerial
SoftwareSerial EspSerial(3, 2);  // RX, TX
ESP8266 wifi(&EspSerial);

char ssid[] = "ArdShare";
char pass[] = "11223344";

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pinDigital = A0;
const int relay = 4;
const int alarm = 5;
const int ledGreen = 6;
const int ledYellow = 7;
const int ledRed = 8;

bool manualControl = false;  // Mode manual atau otomatis

BlynkTimer timer;  // Timer untuk membaca sensor tanpa delay

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

  timer.setInterval(1000L, bacaSensor);  // Baca sensor setiap 1 detik
}

// Fungsi untuk menangani tombol mode manual di Blynk
BLYNK_WRITE(V1) {
  int buttonState = param.asInt();
  manualControl = (buttonState == 1);
  
  if (manualControl) {
    digitalWrite(relay, HIGH);  // Nyalakan pompa di mode manual
  }
}


void bacaSensor() {
  int dataAnalog = analogRead(pinDigital);
  Serial.print("A0 : ");
  Serial.println(dataAnalog);

  Blynk.virtualWrite(V0, dataAnalog);  // Kirim data sensor ke Blynk

  if (!manualControl) {  // Hanya jalankan otomatis jika mode manual tidak aktif
    if (dataAnalog < 500) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Kelembapan:");
      lcd.setCursor(12, 0);
      lcd.print(dataAnalog);
      lcd.setCursor(0, 1);
      lcd.print("Basah");

      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, LOW);
      digitalWrite(relay, LOW);
      digitalWrite(alarm, LOW);

      Blynk.virtualWrite(V2, 255);  // LED Hijau ON
      Blynk.virtualWrite(V3, 0);
      Blynk.virtualWrite(V4, 0);
    } 
    else if (dataAnalog >= 500 && dataAnalog < 800) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Kelembapan:");
      lcd.setCursor(12, 0);
      lcd.print(dataAnalog);
      lcd.setCursor(0, 1);
      lcd.print("Sedang");

      digitalWrite(ledGreen, LOW);
      digitalWrite(ledYellow, HIGH);
      digitalWrite(ledRed, LOW);
      digitalWrite(relay, HIGH);
      digitalWrite(alarm, HIGH);

      Blynk.virtualWrite(V2, 0);
      Blynk.virtualWrite(V3, 255);  // LED Kuning ON
      Blynk.virtualWrite(V4, 0);
    } 
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Kelembapan:");
      lcd.setCursor(12, 0);
      lcd.print(dataAnalog);
      lcd.setCursor(0, 1);
      lcd.print("Kering");

      digitalWrite(ledGreen, LOW);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, HIGH);
      digitalWrite(relay, HIGH);
      digitalWrite(alarm, HIGH);

      Blynk.virtualWrite(V2, 0);
      Blynk.virtualWrite(V3, 0);
      Blynk.virtualWrite(V4, 255);  // LED Merah ON
    }
  }
}

// Fungsi untuk mengecek & menyambung ulang ke Blynk jika terputus
void reconnectBlynk() {
  if (!Blynk.connected()) {
    Serial.println("Menyambungkan ulang ke Blynk...");
    if (Blynk.connect()) {
      Serial.println("Terhubung kembali ke Blynk.");
    } else {
      Serial.println("Gagal terhubung ke Blynk.");
    }
  }
}

void loop() {
  if (Blynk.connected()) {
    Blynk.run();
  } else {
    reconnectBlynk();
  }
  timer.run();  // Jalankan timer untuk baca sensor setiap 1 detik
}
