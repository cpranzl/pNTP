#include "application.h"
#line 1 "/home/cpranzl/projects/particle/pNTP/src/pNTP.ino"
#include "SparkTime.h"
#include "ledmatrix-max7219-max7221.h"

void drawText(String s, int x);
void setup();
void loop();
#line 4 "/home/cpranzl/projects/particle/pNTP/src/pNTP.ino"
UDP UDPClient;
SparkTime rtc;

unsigned long currentTime;
unsigned long lastTime = 0UL;

LEDMatrix *led;

int bitmapWidth = 24;
String text;
int textLength;
// default position of the text is outside and then scrolls left
int textX = bitmapWidth;
int fontWidth = 5, space = 1;

int sensor_output;

// draw text
void drawText(String s, int x)
{
  int y = 0;
  for(int i = 0; i < s.length(); i++) {
    // Adafruit_GFX method
    led->drawChar(x + i*(fontWidth+space), y, s[i], true, false, 1);
  }
}

void setup() {
  rtc.begin(&UDPClient, "0.at.pool.ntp.org");
  rtc.setTimeZone(+1);

  Serial.begin(9600);

  // setup pins and library
  // 1 display per row, 1 display per column
  // optional pin settings - default: CLK = A0, CS = A1, D_OUT = A2
  // (pin settings is independent on HW SPI)
  led = new LEDMatrix(3, 1, A0, A1, A2);
  // > add every matrix in the order in which they have been connected <
  // the first matrix in a row, the first matrix in a column
  // vertical orientation (-90°) and no mirroring - last three args optional
  led->addMatrix(2, 0, 270, false, false);
  led->addMatrix(1, 0, 270, false, false);
  led->addMatrix(0, 0, 270, false, false);

  pinMode(0, INPUT);
}

void loop() {
  sensor_output = digitalRead(0);

  if (currentTime != lastTime) {
    Serial.println(rtc.ISODateString(currentTime));
    if(sensor_output == LOW ) {
      Serial.println("No object in sight\n\n");
    } else {
      Serial.println("Object detected\n\n");
    }
  }

  currentTime = rtc.now();
  
  if (currentTime != lastTime) {
    Serial.println(rtc.ISODateString(currentTime));
    Serial.println(rtc.ISODateUTCString(currentTime));
  }

  lastTime = currentTime;
  text = rtc.ISODateString(currentTime);
  textLength = text.length();

  if(led != NULL) {
    drawText(text, textX--);
    // text animation is ending when the whole text is outside the bitmap
    if(textX < textLength*(fontWidth+space)*(-1)) {
      // set default text position
      textX = bitmapWidth;
      led->flush();
      delay(50);
      // turn all pixels off (takes effect after led->flush())
      led->fillScreen(false);
    }
    // draw text
    led->flush();
    delay(50);
  }
  // animations end
  else if (led != NULL) {
    // shutdown all displays
    led->shutdown(true);
    // free memory
    delete led;
    led = NULL;
  }
}
