#include <Arduino.h>
#include <WiFi.h>
#include <string>

#include "FastLED.h"

#include "constants.h"
#include "pulse.h"
#include "ledmodes.h"

#include "U8g2lib.h"

U8G2_SSD1306_128X64_NONAME_F_SW_I2C g_OLED(U8G2_R2, OLED_CLOCK, OLED_DATA, OLED_RESET);
int g_lineHeight = 0;

int currentCode = -1;

CRGB g_leds[NUM_LEDS]; //create our LED array object for all our LEDs
Pulse pulse = Pulse();

void setup() 
{
  currentCode = -1;
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  FastLED.addLeds<CHIP_SET, DATA_PIN, COLOR_ORDER>(g_leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  g_OLED.begin();

  pinMode(LED_PIN_ONE, INPUT);
  pinMode(LED_PIN_TWO, INPUT);
  pinMode(LED_PIN_FOUR, INPUT);
  pinMode(LED_PIN_EIGHT, INPUT);
  pinMode(LED_PIN_SIXTEEN, INPUT);
  pinMode(LED_PIN_THIRTY_TWO, INPUT);
  pinMode(LED_PIN_SIXTY_FOUR, INPUT);
  pinMode(LED_PIN_ONE_HUNDRED_TWENTY_EIGHT, INPUT);
  pinMode(DATA_PIN, OUTPUT);
}

void loop() 
{
    int code = 0;
    if (digitalRead(LED_PIN_ONE))
    {
      code += 1;
    }
    if (digitalRead(LED_PIN_TWO))
    {
      code += 2;
    }
    if (digitalRead(LED_PIN_FOUR))
    {
      code += 4;
    }
    if (digitalRead(LED_PIN_EIGHT))
    {
      code += 8;
    }
    if (digitalRead(LED_PIN_SIXTEEN))
    {
      code += 16;
    }
    if (digitalRead(LED_PIN_THIRTY_TWO))
    {
      code += 32;
    }
    if (digitalRead(LED_PIN_SIXTY_FOUR))
    {
      code += 64;
    }
    if (digitalRead(LED_PIN_ONE_HUNDRED_TWENTY_EIGHT))
    {
      code += 128;
    }
      std::string intStr = "Current Code Input: " + std::to_string(code);

      g_OLED.clearBuffer();					// clear the internal memory
      g_OLED.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
      g_OLED.drawStr(0, 10, intStr.c_str());	// write something to the internal memory
      g_OLED.sendBuffer();					// transfer internal memory to the display 

    if (currentCode != code && code == 5)
    {
      //initialize pulse modes
      switch (code) 
      {
        case 5:
          noAutoWarning();
          break;
      }
    } 
    //update pulse modes if already started
    else if (currentCode == code && code == 5)
    {
      pulse.update();
    }
    //all other led modes that are not pulse
    else if (code != 5)
    {
      switch(code)
      {
        case 1:
          cone();
          break;
        case 2:
          cube();
          break;
        case 3:
          redDisabled();
          break;
        case 4:
          blueDisabled();
          break;
        case 6:
          currentLimiting();
          break;
         case 7:
          rainbowStatusMode();
          break;
        case 8:
          lavaMode();
          break;
        case 9:
          waterMode();
          break;
      }
    }
    else
    {
      FastLED.clear(true);
    }

    currentCode = code;
    FastLED.show();
}
