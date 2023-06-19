#include <Arduino.h>
#include "FastLED.h"
#include "constants.h"
#include "ledmodes.h"
#include "pulse.h"

#define deltaHue 3

uint8_t hueOffset = 0;

//Lava and water modes brightness variance scale
uint16_t brightnessScale = 150;

uint16_t indexScale = 100;

extern Pulse pulse;

//LEDs blinking yellow for cones
void cone()
{
    fill_solid(g_leds, NUM_LEDS, CRGB(255, 137, 0));
}

//LEDs blinking purple for cubes
void cube()
{
    fill_solid(g_leds, NUM_LEDS, CRGB(128, 0, 128));   
}

//LEDs blinking red when disabled on red alliance
void redDisabled()
{
    fill_solid(g_leds, NUM_LEDS, CRGB(255, 0, 0));   
}

//LEDs blinking blue when disabled on blue alliance
void blueDisabled()
{
    fill_solid(g_leds, NUM_LEDS, CRGB(0, 0, 255));
}

//LEDs blinking white when no auto is selected on dashboard when disabled
void noAutoWarning()
{
  pulse.init(CRGB(255, 255, 255), 750, 100);
  pulse.update();
}

//LEDs flash orange when intake is current limiting
void currentLimiting()
{
    fill_solid(g_leds, NUM_LEDS, CRGB(255, 255, 255));
}

//LEDs rotate in rainbow pattern
void rainbowStatusMode()
{
  fill_rainbow(g_leds, NUM_LEDS, hueOffset, deltaHue);
  hueOffset += deltaHue;
  hueOffset %= 256;
}

//Lava effect color palette
CRGBPalette16 lavaPalette = CRGBPalette16(
    CRGB::OrangeRed, CRGB::Maroon, CRGB::DarkRed, CRGB::Maroon,
    CRGB::DarkRed, CRGB::Orange, CRGB::Red, CRGB::DarkRed,
    CRGB::Maroon, CRGB::DarkRed, CRGB::Red, CRGB::OrangeRed,
    CRGB::Red, CRGB::OrangeRed, CRGB::OrangeRed, CRGB::Red
);
//LEDs are in different shades and colors for lava
void lavaMode()
{
   for(int i = 0; i < NUM_LEDS; i++)
   {
        uint8_t brightness = inoise8(i * brightnessScale, millis() / 5);
        uint8_t index = inoise8(i * indexScale, millis());
        g_leds[i] = ColorFromPalette(lavaPalette, index, brightness);
   }
}

//Water effect color palette
CRGBPalette16 waterPalette = CRGBPalette16(
    CRGB::DarkBlue, CRGB::Blue, CRGB::DarkBlue, CRGB::SkyBlue,
    CRGB::DarkBlue, CRGB::SkyBlue, CRGB::BlueViolet, CRGB::Blue,
    CRGB::SkyBlue, CRGB::DarkBlue, CRGB::Blue, CRGB::BlueViolet,
    CRGB::FloralWhite, CRGB::FloralWhite, CRGB::LightPink, CRGB::Blue
);

//LEDs are in different shades and colors for water
void waterMode()
{
    for(int i = 0; i < NUM_LEDS; i++)
    {
        uint8_t brightness = inoise8(i * brightnessScale, millis() / 5);
        uint8_t index = inoise8(i * indexScale, millis());
        g_leds[i] = ColorFromPalette(waterPalette, index, brightness);
    }
}