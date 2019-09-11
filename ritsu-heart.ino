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
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
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

float prevTime = 0;
float deltaTime;
float timeLED = 0;

/**
 * Runs once at startup.
 */
void setup() {
    setupDigit();
//    setupMotor();
    Serial.begin(9600); // Need this to write to the console (Serial monitor)

    strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
    strip.show();             // Turn OFF all pixels ASAP
    strip.setBrightness(50);  // Set BRIGHTNESS to about 1/5 (max = 255)
}

/**
 * Runs repeatedly as fast as the board can execute it, like a while(1) loop.
 */
void loop() {
    float currentTime = millis();
    deltaTime = currentTime - prevTime;
    prevTime = currentTime;
    // Read pot voltage and map to an appropriate speed for the blood flow rate
    float pinValue = analogRead(FLOW_RATE_POT_PIN);
    float bloodSpeed = mapf(pinValue, 0, ANALOG_RANGE, MIN_SPD, MAX_SPD);

    // Read pot voltage and map to an appropriate pressure for the blood coloration
    pinValue = analogRead(PRESSURE_POT_PIN);
    float bloodPressure = mapf(pinValue, 0, ANALOG_RANGE, MIN_PRESSURE, MAX_PRESSURE);

    writeNumber(map(pinValue, 0, ANALOG_RANGE, 0, 10));
    //Test blood flow light effect
    bloodFlowLED(bloodPressure, bloodSpeed);

    // Example light functions
    delay(LED_DELAY);
}

float clamp(float n, float lo, float hi) {
    return n < lo ? lo : (n > hi ? hi : n);
}

/** 
 * Creates a "blood flow" light design with on the given strip with the given pressure (kPa)
 * and speed (independent of LED_DELAY). Call in a loop to animate.
 */
void bloodFlowLED(float pressure, float spd) {
    // Frequency of light wave effect
    float sinFreq = 0.07;

    // Update time

    timeLED += spd * deltaTime;

    for (int i = 0; i < LED_COUNT; i++) {
        uint32_t intensity = floor(127.0 * sin(sinFreq * (2 * PI) * i + timeLED) + 127.0);
        strip.setPixelColor(i, getColorFromPressure(pressure, intensity));
    }

    // Write the set values to the real-world LEDs
    strip.show();
}

/**
 * Returns a color that represents the given pressure.
 */
uint32_t getColorFromPressure(float pressure, int intensity) {
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
