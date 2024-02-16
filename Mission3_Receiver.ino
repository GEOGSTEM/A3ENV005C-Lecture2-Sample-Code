#include <LoRa.h>
#include <Adafruit_SSD1306.h>

#define LORA_BAND 923000000
Adafruit_SSD1306 SSD1306(128, 64);

char key[] = "abcdef";

void setup(void) {
	Serial.begin(9600);
 
  SSD1306.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  SSD1306.setRotation(2);
  SSD1306.setTextSize(1);
  SSD1306.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  SSD1306.invertDisplay(false);
  SSD1306.clearDisplay();
  SSD1306.display();
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
  String payload(buffer);
  String stringkey(key);
  String incomingkey = payload.substring(0,6);
  String message = payload.substring(6,read_size);
  
	if (read_size != available_size) {
		Serial.print("Fail to read LoRa packet ");
		Serial.print(read_size);
		Serial.print(" != ");
		Serial.println(available_size);
		return;
	}

  if (stringkey == incomingkey) {
	  Serial.print("Received ");
	  Serial.print(read_size);
	  Serial.print(':');
	  Serial.write(buffer, read_size);
	  Serial.println();

    SSD1306.clearDisplay();
    SSD1306.setCursor(0, 0);
    SSD1306.print("***LoRa RECEIVER:***");
    SSD1306.setCursor(0, 30);
    SSD1306.print("MSG:");
    SSD1306.setCursor(25, 30);
    SSD1306.print(message);
    SSD1306.display();
  }
}
