#include <LoRa.h>

#define LORA_BAND 923000000

void setup(void) {
	Serial.begin(9600);
	delay(1000);

	Serial.println("setup LoRa");
	SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
	LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
	while (!LoRa.begin(LORA_BAND)) {}
}

char message[] = "Hello, world! ";
signed int number = 0;

void loop(void) {
	Serial.print(message);
	Serial.println(number);

	LoRa.beginPacket();
	// LoRa.write((uint8_t*)message, sizeof message - 1);
	LoRa.print(message);
	LoRa.print(number);
	LoRa.endPacket();
	number += 1;
	delay(3000);
}
