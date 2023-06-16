#ifndef CONST_H
#define CONST_H

#define NUM_LEDS 256 //how many LEDs are in your strip/panel
#define DATA_PIN 48 //signal wire is connected to this pin on arduino
#define COLOR_ORDER GRB //surprisingly, many LED strips don't use the color order Red,Green,Blue
#define CHIP_SET WS2812B //KnightKrawler uses WS2812B Leds, but there are many other options
#define BRIGHTNESS 255 //255 is maximum brightness, lower this value to limit brightness
#define VOLTS 5 //All WS2812B LED strips are 5v
#define MAX_AMPS 2500 //this value is in milliamps, our power converter allows for 3 amp at 5v. Choose a value at or bellow 3000 milliamps

#define OLED_CLOCK 18
#define OLED_DATA 17
#define OLED_RESET 21

//pin definitions for reading from roborio
extern int LED_PIN_ONE;
extern int LED_PIN_TWO;
extern int LED_PIN_FOUR;
extern int LED_PIN_EIGHT;
extern int LED_PIN_SIXTEEN;
extern int LED_PIN_THIRTY_TWO;
extern int LED_PIN_SIXTY_FOUR;
extern int LED_PIN_ONE_HUNDRED_TWENTY_EIGHT;

#endif