#define RXD2 16  // GPIO16 for RX
#define TXD2 17  // GPIO17 for TX

void setup() {
  Serial.begin(115200);  // USB serial monitor
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);  // UART2 on ESP32
  Serial.println("ESP32 ready to receive data.");
}

void loop() {
  if (Serial2.available()) {
    String receivedData = Serial2.readStringUntil('\n');
    Serial.println("Received from STM32: " + receivedData);
  }
}
