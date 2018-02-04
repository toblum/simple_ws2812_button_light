#include <WS2812FX.h>

#define LED_COUNT 7
#define LED_PIN 2

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int mode = 0;
bool trigger = false;
bool dimmed = false;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
int buttonState;


void singleClick() {
  mode++;
  trigger = true;

  Serial.print("Single click, mode: ");
  Serial.println(mode);
}


void setup() {
  Serial.begin(115200);
  Serial.println("Start up ...");

  ws2812fx.init();
  ws2812fx.setBrightness(255);
  ws2812fx.setSpeed(48000);
  ws2812fx.setMode(FX_MODE_RAINBOW);

  pinMode(6, INPUT_PULLUP);
  ws2812fx.start();
}


void loop() {
  int reading = digitalRead(6);

  if (mode == 15) {
    mode = 0;
  }

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > 100) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        singleClick();
      }
    }
  }

  // Mode 1: White
  if (mode == 0 && trigger) {
    ws2812fx.setSpeed(200);
    ws2812fx.setColor(0xFFFFFF);
    ws2812fx.setMode(FX_MODE_STATIC);
    trigger = false;
  }

  // Mode 1: Red
  if (mode == 1 && trigger) {
    ws2812fx.setSpeed(200);
    ws2812fx.setColor(0xFF0000);
    ws2812fx.setMode(FX_MODE_STATIC);
    trigger = false;
  }

  // Mode 2: Blue
  if (mode == 2 && trigger) {
    ws2812fx.setSpeed(200);
    ws2812fx.setColor(0x0006FF);
    ws2812fx.setMode(FX_MODE_STATIC);
    trigger = false;
  }

  // Mode 3: Pink
  if (mode == 3 && trigger) {
    ws2812fx.setSpeed(200);
    ws2812fx.setColor(0xFF0041);
    ws2812fx.setMode(FX_MODE_STATIC);
    trigger = false;
  }

  // Mode 4: Yellow
  if (mode == 4 && trigger) {
    ws2812fx.setSpeed(200);
    ws2812fx.setColor(0xFF4C00);
    ws2812fx.setMode(FX_MODE_STATIC);
    trigger = false;
  }

  // Mode 5: Green
  if (mode == 5 && trigger) {
    ws2812fx.setSpeed(200);
    ws2812fx.setColor(0x50FF00);
    ws2812fx.setMode(FX_MODE_STATIC);
    trigger = false;
  }

  // Mode 6: Rainbow
  if (mode == 6 && trigger) {
    ws2812fx.setSpeed(16000);
    ws2812fx.setMode(FX_MODE_RAINBOW);
    trigger = false;
  }

  // Mode 7: Breathe
  if (mode == 7 && trigger) {
    ws2812fx.setSpeed(12000);
    ws2812fx.setColor(0xEC00FF);
    ws2812fx.setMode(FX_MODE_BREATH);
    trigger = false;
  }

  // Mode 8: Twinkle random
  if (mode == 8 && trigger) {
    ws2812fx.setSpeed(2000);
    ws2812fx.setMode(FX_MODE_TWINKLE_RANDOM);
    trigger = false;
  }

  // Mode 9: Sparkle
  if (mode == 9 && trigger) {
    ws2812fx.setSpeed(2000);
    ws2812fx.setColor(0xFF0066);
    ws2812fx.setMode(FX_MODE_SPARKLE);
    trigger = false;
  }

  // Mode 10: Color sweep random
  if (mode == 10 && trigger) {
    ws2812fx.setSpeed(4000);
    ws2812fx.setColor(0xFF0066);
    ws2812fx.setMode(FX_MODE_COLOR_SWEEP_RANDOM);
    trigger = false;
  }

  // Mode 11: Comet
  if (mode == 11 && trigger) {
    ws2812fx.setSpeed(2000);
    ws2812fx.setColor(0xFF8D00);
    ws2812fx.setMode(FX_MODE_COMET);
    trigger = false;
  }

  // Mode 12: Fireworks random
  if (mode == 12 && trigger) {
    ws2812fx.setSpeed(2000);
    ws2812fx.setColor(0xFF8D00);
    ws2812fx.setMode(FX_MODE_FIREWORKS_RANDOM);
    trigger = false;
  }

  // Mode 13: Fire flicker
  if (mode == 13 && trigger) {
    ws2812fx.setSpeed(2000);
    ws2812fx.setColor(0xFF2D00);
    ws2812fx.setMode(FX_MODE_FIRE_FLICKER);
    trigger = false;
  }

  // Mode 14: Fire flicker (intense)
  if (mode == 14 && trigger) {
    ws2812fx.setSpeed(2000);
    ws2812fx.setColor(0xFF7800);
    ws2812fx.setMode(FX_MODE_FIRE_FLICKER_INTENSE);
    trigger = false;
  }


  lastButtonState = reading;
  ws2812fx.service();
}
