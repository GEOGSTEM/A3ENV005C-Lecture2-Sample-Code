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

void loop(void) {
	int packet_size = LoRa.parsePacket();
	if (packet_size < 1) return;
	int available_size = LoRa.available();
	if (available_size != packet_size) {
		Serial.print("LoRa packet data not available");
		Serial.print(available_size);
		Serial.print(" != ");
		Serial.println(packet_size);
		return;
	}
	char buffer[available_size];
	int read_size = LoRa.readBytes(buffer, available_size);
	if (read_size != available_size) {
		Serial.print("Fail to read LoRa packet ");
		Serial.print(read_size);
		Serial.print(" != ");
		Serial.println(available_size);
		return;
	}
	Serial.print("Received ");
	Serial.print(read_size);
	Serial.print(':');
	Serial.write(buffer, read_size);
	Serial.println();
}
