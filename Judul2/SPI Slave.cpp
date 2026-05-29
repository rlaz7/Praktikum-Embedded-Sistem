#include <SPI.h>

volatile boolean messageComplete = false;
String message = "";

void setup() {
  Serial.begin(9600);
  
  // Pin MISO (Master In Slave Out) harus diset sebagai OUTPUT pada Slave
  pinMode(MISO, OUTPUT);
  
  // Mengaktifkan mode SPI Slave pada register SPCR
  SPCR |= _BV(SPE);
  
  // Mengaktifkan interupsi SPI
  SPI.attachInterrupt();
}

// Rutin Layanan Interupsi (Interrupt Service Routine) untuk SPI
// Otomatis terpanggil setiap kali ada data masuk dari Master
ISR (SPI_STC_vect) {
  char c = SPDR; // Membaca data dari SPI Data Register
  
  if (c == '\n') {
    messageComplete = true; // Jika menerima newline, pesan selesai
  } else {
    message += c; // Tambahkan karakter ke string pesan
  }
}

void loop() {
  // Jika pesan sudah lengkap diterima
  if (messageComplete) {
    Serial.print("Message received: ");
    Serial.println(message);
    
    // Kosongkan kembali variabel untuk pesan berikutnya
    message = "";
    messageComplete = false;
  }
}