// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      2
#define MAX_RGB        255
#define INIT_BRIGHT    128
#define MAX_STEP       8
#define RAND_DELAY     8

#define R              0
#define G              1
#define B              2
#define R_INIT         3
#define G_INIT         4
#define B_INIT         5
#define BRIGHT         6
#define STEP           7
#define INIT_DELAY     8
#define BLACK_DELAY    9


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 20; // delay for half a second
int pixelArr[NUMPIXELS][10]; // R, G, B, Brightness, Step


void setup() {
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
    // End of trinket special code

    pixels.begin(); // This initializes the NeoPixel library.
    randomSeed(analogRead(1));

    for (int i=0; i<NUMPIXELS; i++) {
        mkPixelColor(pixelArr[i]);

        int r = pixelArr[R];
        int g = pixelArr[G];
        int b = pixelArr[B];

        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(r,g,b)); // Moderately bright green color.
    }
}


void mkPixelColor(int pix[]) {
    pix[BRIGHT] = 128 + random(INIT_BRIGHT);
    pix[STEP] = random(MAX_STEP)+1;
    pix[INIT_DELAY] = 30 + (random(RAND_DELAY) * 5);
    pix[BLACK_DELAY] = 10 + (random(RAND_DELAY) * 10);

    pix[R_INIT] = random(MAX_RGB);
    pix[G_INIT] = random(MAX_RGB);
    pix[B_INIT] = random(MAX_RGB);

    pix[R] = (int) ( (float) pix[R_INIT] * ( (float) pix[BRIGHT] / 255.0) );
    pix[G] = (int) ( (float) pix[G_INIT] * ( (float) pix[BRIGHT] / 255.0) );
    pix[B] = (int) ( (float) pix[B_INIT] * ( (float) pix[BRIGHT] / 255.0) );
}


void stepPixel(int pix[]) {
    if (pix[INIT_DELAY] > 0) {
        pix[INIT_DELAY] -= 1;
        return;
    }

    if (pix[BRIGHT] <= 0) {
        if (pix[BLACK_DELAY] >= 0) {
            pix[BLACK_DELAY] -= 1;
            return;
        }

        mkPixelColor(pix);
        return;
    }

    pix[BRIGHT] -= pix[STEP];
    if (pix[BRIGHT] < 0) {
        pix[BRIGHT] = 0;
    }

    pix[R] = (int) ( (float) pix[R_INIT] * ( (float) pix[BRIGHT] / 255.0) );
    pix[G] = (int) ( (float) pix[G_INIT] * ( (float) pix[BRIGHT] / 255.0) );
    pix[B] = (int) ( (float) pix[B_INIT] * ( (float) pix[BRIGHT] / 255.0) );
}


void loop() {

    // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
    for(int i=0;i<NUMPIXELS;i++){
        int r = pixelArr[i][R];
        int g = pixelArr[i][G];
        int b = pixelArr[i][B];

        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(r,g,b)); // Moderately bright green color.
        stepPixel(pixelArr[i]);
    }
   
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
 
}
