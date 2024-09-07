#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SH1106 display(OLED_RESET);

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

void setup() {
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  display.clearDisplay();
  display.drawPixel(10, 10, WHITE);
  display.display();
  delay(1000);

  // testdrawchar();
  // display.display();
  // delay(2000);

  // // text display tests
  // display.clearDisplay();
  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(0, 0);
  // display.println("Hello, world!");
  // display.setTextColor(BLACK, WHITE);  // 'inverted' text
  // display.println(3.141592);
  // display.setTextSize(2);
  // display.setTextColor(WHITE);
  // display.print("0x");
  // display.println(0xDEADBEEF, HEX);
  // display.display();
  // delay(2000);

  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}

void loop() {
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);

  if (Serial.available() > 0) {
    String text = Serial.readStringUntil('/');
    if (text.startsWith("!-")) {
      processCommand(text);
    } else {
      display.print(text);
    }
    display.display();
  }
}

void processCommand(String text) {
  if (text.equals("!-cls")) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
  } else if (text.equals("!-fontSize")) {
    display.setTextSize(Serial.parseInt());
  } else if (text.equals("!-fontColor:White")) {
    display.setTextColor(WHITE);
  } else if (text.equals("!-fontColor:Black")) {
    display.setTextColor(BLACK, WHITE);
  } else if (text.equals("!-invert")) {
    display.invertDisplay(true);
  } else if (text.equals("!-revert")) {
    display.invertDisplay(false);
  }
}

void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  for (uint8_t i = 0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }
  display.display();
}
