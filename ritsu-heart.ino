// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Analog pin for reading flow rate potentiometer value
#define FLOW_RATE_POT_PIN 1

// Analog pin for reading pressure potentiometer value
#define PRESSURE_POT_PIN 2

// Analog read range
#define ANALOG_RANGE 1023

// NeoPixels
#define LED_PIN 12
#define LED_COUNT 8
#define LED_DELAY 5

// Blood flow constants
#define MIN_SPD 0.003
#define MAX_SPD 0.035
#define MIN_PRESSURE 1.0
#define MAX_PRESSURE 2.0

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


/**
 * Runs once at startup.
 */
void setup() {
  Serial.begin(9600); // Need this to write to the console (Serial monitor)

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  // Testing
  Serial.println(mapf(0.5, 0.0, 3.0, 0.0, 10.0) - 1.66666666 < 0.001);
  Serial.println(mapf(0.0, 0.0, 3.0, 0.0, 10.0) < 0.001);
  Serial.println(mapf(3.0, 0.0, 3.0, 0.0, 10.0) - 10.0 < 0.001);
}

/**
 * Runs repeatedly as fast as the board can execute it, like a while(1) loop.
 */
void loop() {
  // Read pot voltage and map to an appropriate speed for the blood flow rate
  float pinValue = analogRead(FLOW_RATE_POT_PIN);
  float bloodSpeed = mapf(pinValue, 0, ANALOG_RANGE, MIN_SPD, MAX_SPD);
  
  // Read pot voltage and map to an appropriate pressure for the blood coloration
  pinValue = analogRead(PRESSURE_POT_PIN);
  float bloodPressure = mapf(pinValue, 0, ANALOG_RANGE, MIN_PRESSURE, MAX_PRESSURE);

  //Test blood flow light effect
  bloodFlowLED(bloodPressure, bloodSpeed);

  // Example light functions
  /*
  // Fill along the length of the strip in various colors...
  colorWipe(strip.Color(255,   0,   0), 50); // Red
  colorWipe(strip.Color(  0, 255,   0), 50); // Green
  colorWipe(strip.Color(  0,   0, 255), 50); // Blue

  // Do a theater marquee effect in various colors...
  theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

  rainbow(10);             // Flowing rainbow cycle along the whole strip
  //theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
  */
  delay(LED_DELAY);
}

float timeLED = 0;
/** 
 * Creates a "blood flow" light design with on the given strip with the given pressure (kPa)
 * and speed (independent of LED_DELAY). Call in a loop to animate.
 */
void bloodFlowLED(float pressure, float spd) {
  // Frequency of light wave effect
  float sinFreq = 0.07;

  // Update time
  timeLED += spd * LED_DELAY;
  
  for (int i = 0; i < LED_COUNT; i++) {
    float intensity = 127 * sin(sinFreq * (2 * PI) * i + timeLED) + 127;
    strip.setPixelColor(i, getColorFromPressure(pressure, intensity));
  }
  
  // Write the set values to the real-world LEDs
  strip.show();
}

/**
 * Returns a color that represents the given pressure.
 */
uint32_t getColorFromPressure(float pressure, float intensity) {
  float redValue = mapf(pressure, MIN_PRESSURE, MAX_PRESSURE, 0.0, 1.0);
  float blueValue = 1.0 - redValue;

  return strip.Color(intensity * redValue, 0, intensity * blueValue);
}

/**
 * Maps a number in the specified "from" range to the "to" range (e.g. mapping 0.5 from the range [0, 1]
 * to the range [0, 10] returns 5.0). 
 */
float mapf(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
  // Map to 0.0 to 1.0 (inclusive)
  float rangeLow = fromHigh - fromLow;
  value = (value - fromLow) / rangeLow;
  
  // Map to toLow to toHigh (inclusive)
  float rangeHigh = toHigh - toLow;
  value = value * rangeHigh + toLow;
  
  return value;
}

// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
