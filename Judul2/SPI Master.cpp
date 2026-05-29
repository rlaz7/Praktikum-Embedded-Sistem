#include <SPI.h>

void setup() {
  Serial.begin(9600);
  
  // Memulai bus SPI
  SPI.begin();
  
  // Mengatur pin Slave Select (SS) secara default Arduino Uno ada di pin 10
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH); // HIGH berarti Slave belum aktif
}

void loop() {
  if (Serial.available() > 0) {
    String message = Serial.readString();
    
    // Tarik pin SS ke LOW untuk memulai komunikasi dengan Slave
    digitalWrite(SS, LOW); 
    
    // Kirim pesan karakter demi karakter
    for (int i = 0; i < message.length(); i++) {
      SPI.transfer(message[i]);
      delay(10); // Jeda kecil agar Slave punya waktu untuk memproses
    }
    
    // Kirim karakter newline ('\n') sebagai penanda akhir pesan
    SPI.transfer('\n'); 
    
    // Tarik kembali pin SS ke HIGH untuk mengakhiri komunikasi
    digitalWrite(SS, HIGH); 
    
    Serial.print("Message sent: " + message);
  }
  delay(1000);
}