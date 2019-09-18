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

#define FRAME_DELAY 0.01

// NeoPixels
#define LED_PIN 12
#define LED_COUNT 8

// Pins
#define BUZZER_PIN 53

// Blood flow constants
#define MIN_SPD -200
#define MAX_SPD 100
#define MIN_PRESSURE 4.0
#define MAX_PRESSURE 13.0
#define BEEP_DURATION 0.15

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

// Loop/animation timing variables (in seconds)
double prevTime = 0;
double deltaTime = 0;
double timeLED = 0;
double timeBeep = BEEP_DURATION;

// things for the model (all times in seconds)
double Vlv = 100.0;
double Pa = 80.0;

double Pv = 10.0; // we can change this
double Po = 10.0;
double Rv = 0.01;
double R0 = 0.005;
double R = 1.0; // we can change this
double C = 5.0; // we can change this

double maxtime = 1.0;
double dt = 0.001;
double trr = 1.0;
double ts;
double es = 1.0;
double ed = 0.1;
double e;

int i;
int maxstep;
double t;

// end of things for the model

/**
 * Runs once at startup.
 */
void setup() {
    ts = 0.3 * sqrt(trr);
    maxstep = maxtime / dt;

    setupDigit(20); // run setup for the first motor
    Serial.begin(9600); // Need this to write to the console (Serial monitor)

    strip.begin();            // INITIALIZE NeoPixel strip object (REQUIRED)
    strip.show();             // Turn OFF all pixels ASAP
    strip.setBrightness(50);  // Set BRIGHTNESS to about 1/5 (max = 255)

    pinMode(BUZZER_PIN, OUTPUT); // Setup buzzer for digital control
}

long simSteps = 0;
int heartbeatNum = 0;

/**
 * Runs repeatedly as fast as the board can execute it, like a while(1) loop.
 */
void loop() {
    double fv;
    double f1;
    double f2;

    // E(t)の計算 (calculation)
    for (int i = 0; i < FRAME_DELAY / dt; i++) {
        t = fmod(simSteps * dt, trr);
        simSteps++;
        if (t < ts) {
            e = ed + (es - ed)/2.0 * (1.0 - cos(M_PI * t / (0.3 * sqrt(trr))));
        } else if (t < (ts * 3.0 / 2.0)) {
            e = ed + (es - ed)/2.0 * (1.0 + cos(2.0 * M_PI * (t - 0.3 * sqrt(trr)) / (0.3 * sqrt(trr))));
        } else {
            e = ed;
        }

        double Plv = e * Vlv;
        
        // fv, f1, f2
        fv = (Pv - Plv) / Rv;
        f1 = (Plv - Pa) / R0;
        f2 = (Pa - Po) / R;
        
        // Vlv, Pa
        Vlv += (fv - f1) * dt;
        Pa += (f1 - f2) * e * dt;
    }

    /*
    Serial.print(t);
    Serial.print(" ");
    Serial.print(Vlv);
    Serial.print(" ");
    Serial.print(Pa);
    Serial.print(" ");
    Serial.print(fv);
    Serial.print(" ");
    Serial.print(f1);
    Serial.print(" ");
    Serial.print(f2);
    Serial.print("\n");
    */

    // Arduino stuff (not related to model)

    // Number of heartbeats
    int prevNum = heartbeatNum;
    heartbeatNum = (int) floor(simSteps * dt) % 10;
    if (heartbeatNum != prevNum) {
        startBeep();
        writeNumber(heartbeatNum, 20);
    }

    // Animate blood flow according to model
    bloodFlowLED(Pa, f1);

    // Step buzzer so it turns off after BEEP_DURATION
    stepBeep();

    // Loop timing
    double curTime = micros() / 1000000.0;
    deltaTime = curTime - prevTime;
    prevTime = curTime;

    // Loop timing stuff
    double timeLeftInFrame = FRAME_DELAY - deltaTime;
    if (timeLeftInFrame >= 0) {
        // Delay for the remainder of FRAME_DELAY
        delay(timeLeftInFrame * 1000); // delay() takes milliseconds
    } else {
        // Don't delay, program is lagging behind
        Serial.print("WARNING: Simulation ran ");
        Serial.print(timeLeftInFrame);
        Serial.println("ms too long this frame.");
    }
}

/** 
 * Creates a "blood flow" light design with on the given strip with the given
 * pressure (kPa) and speed (independent of FRAME_DELAY). Call in a loop to
 * animate.
 */
void bloodFlowLED(float pressure, float spd) {
    // Frequency of light wave effect
    float sinFreq = 0.2;

    // Update time
    float minLightSpd = 0;
    float maxLightSpd = 25;
    timeLED += mapf(spd, MIN_SPD, MAX_SPD, minLightSpd, maxLightSpd) * deltaTime;

    for (int i = 0; i < LED_COUNT; i++) {
        uint32_t intensity = floor(127.0 * sin(sinFreq * (2 * PI) * i + timeLED) + 127.0);
        strip.setPixelColor(i, getColorFromPressure(pressure, intensity));
    }

    // Write the set values to the real-world LEDs
    strip.show();
}

/**
 * Begins the beep noise and resets the beep timer
 */
 void startBeep() {
    timeBeep = BEEP_DURATION;
    digitalWrite(BUZZER_PIN, HIGH);
 }

/**
 * Decrements the beep timer and turns off the buzzer if it has been playing for BEEP_DURATION seconds
 */
void stepBeep() {
    // Decrement beep timer
    timeBeep -= deltaTime;

    // Check if buzzer should trn off
    if (timeBeep <= 0.0) {
        digitalWrite(BUZZER_PIN, LOW);
    }
}

/**
 * Returns a color that represents the given pressure.
 */
uint32_t getColorFromPressure(float pressure, int intensity) {
    pressure = clamp(pressure, MIN_PRESSURE, MAX_PRESSURE);
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

float clamp(float n, float lo, float hi) {
    return n < lo ? lo : (n > hi ? hi : n);
}
