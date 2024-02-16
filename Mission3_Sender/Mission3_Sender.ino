#include <LoRa.h>
#include <Adafruit_SSD1306.h>

#define LORA_BAND 923000000
Adafruit_SSD1306 SSD1306(128, 64);

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

char key[] = "abcdef";
char message[] = "Hello, world! ";
signed int number = 0;

void loop(void) {
	SSD1306.clearDisplay();
  SSD1306.setCursor(0, 0);
  SSD1306.print("*** LoRa SENDER: ***");
  SSD1306.setCursor(0, 15);
  SSD1306.print("KEY:");
  SSD1306.setCursor(25, 15);
  SSD1306.print(key);
  SSD1306.setCursor(0, 30);
  SSD1306.print("MSG:");
  SSD1306.setCursor(25, 30);
  SSD1306.print(message);
  SSD1306.display();

	LoRa.beginPacket();
	// LoRa.write((uint8_t*)message, sizeof message - 1);
  LoRa.print(key);       //6 charaters password
	LoRa.print(message);
	LoRa.print(number);
	LoRa.endPacket();
	number += 1;
	delay(3000);
}
