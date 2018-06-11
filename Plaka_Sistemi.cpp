#include <RFID.h>
#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9

#define Kpin  2 
#define Ypin  4
#define Mpin  3

RFID rfid(SS_PIN, RST_PIN);

int Plaka[5];
int KayitliPlakalar[][5] = {
  {136, 4, 225, 225, 140}
  //{136, 4, 225, 225, 140}
};

bool durum = false;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  pinMode(Kpin, OUTPUT);
  pinMode(Ypin, OUTPUT);
  pinMode(Mpin, OUTPUT);
  analogWrite(Kpin,255); 
  analogWrite(Ypin,255);
  analogWrite(Mpin,255);  
  Serial.println("Plaka Sistemi Baslatiliyor...");
  Serial.println("Sistem Yuklendi..");
  Serial.println("--------------------------");
  Serial.println();
}

void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      Serial.print(rfid.Plaka[0]);
      Serial.print(" ");
      Serial.print(rfid.Plaka[1]);
      Serial.print(" ");
      Serial.print(rfid.Plaka[2]);
      Serial.print(" ");
      Serial.print(rfid.Plaka[3]);
      Serial.print(" ");
      Serial.print(rfid.Plaka[4]);
      Serial.println("");

      for (int x = 0; x < sizeof(KayitliPlakalar); x++) {
        for (int i = 0; i < sizeof(rfid.Plaka); i++ ) {
          if (rfid.Plaka[i] != KayitliPlakalar[x][i]) {
            durum = false;
            break;
          } else {
            durum = true;
          }
        }
        if (durum) break;
      }
    }
    if (durum) {
      Serial.println("Plaka Sistemde Kayıtlı !");

      analogWrite(Kpin,0); 
      analogWrite(Ypin,255);
      analogWrite(Mpin,0);  
      delay(200);

      analogWrite(Kpin,255); 
      analogWrite(Ypin,255);
      analogWrite(Mpin,255);  
    }
else {
      Serial.println("Plaka Sistemde Kayıtlı Degil !");
      }
  }
  rfid.halt();
}