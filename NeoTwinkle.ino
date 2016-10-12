// Code based on:
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit
// NeoPixel library

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

struct pixData {
    byte rInit;
    byte gInit;
    byte bInit;
    int maxBright;
    int curBright;
    int step;
    int initDelay;
    int blackDelay;
};

// When we setup the NeoPixel library, we tell it how many pixels, and
// which pin to use to send signals.  Note that for older NeoPixel
// strips you might need to change the third parameter--see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// delay for 20 milli sec.
int delayval = 20;
struct pixData pixelArr[NUMPIXELS];

void initPixelColor(struct pixData *pix) {
    pix->curBright = 0;
    pix->maxBright = 128 + random(INIT_BRIGHT);
    pix->step = random(MAX_STEP)+1;
    pix->initDelay = 30 + (random(RAND_DELAY) * 5);
    pix->blackDelay = 10 + (random(RAND_DELAY) * 10);

    pix->rInit = random(MAX_RGB);
    pix->gInit = random(MAX_RGB);
    pix->bInit = random(MAX_RGB);
}


void mkPixel(struct pixData *pixInfo, byte retPix[]) {
    float brightPer = (float) pixInfo->curBright / 255.0;
    retPix[R] = (int) ( (float) pixInfo->rInit * brightPer );
    retPix[G] = (int) ( (float) pixInfo->gInit * brightPer );
    retPix[B] = (int) ( (float) pixInfo->bInit * brightPer );



    if (pixInfo->step > 0) {
        // Achieved max brightness
        if (pixInfo->curBright >= pixInfo->maxBright) {
            if (pixInfo->initDelay > 0) {
                pixInfo->initDelay -= 1;
                return;
            }

            pixInfo->step *= -1;
            return;
        }

        // Step up to max brightness
        else {
            pixInfo->curBright += pixInfo->step;
            if (pixInfo->curBright > 255) {
                pixInfo->curBright = 255;
            }

            return;
        }
    } // if (pixInfo->step > 0) {

    
    else {
        if (pixInfo->curBright <= 0) {
            // Pixel should be black
            if (pixInfo->blackDelay >= 0) {
                pixInfo->blackDelay -= 1;
                return;
            }

            // Pixel is done being black, get new color
            initPixelColor(pixInfo);
            return;
        }

        // Fade to black
        pixInfo->curBright += pixInfo->step;
        if (pixInfo->maxBright < 0) {
            pixInfo->maxBright = 0;
        }
    }
}


void setup() {
    // This is for Trinket 5V 16MHz, you can remove these three lines
    // if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
    // End of trinket special code

    pixels.begin(); // This initializes the NeoPixel library.
    randomSeed(analogRead(1));

    for (int i=0; i<NUMPIXELS; i++) {
        initPixelColor(&pixelArr[i]);

        byte pixRGB[3];
        mkPixel(&pixelArr[i], pixRGB);
        pixels.setPixelColor(i, pixels.Color(pixRGB[R],
                                             pixRGB[G],
                                             pixRGB[B]));
    }
}


void loop() {
    // For a set of NeoPixels the first NeoPixel is 0, second is 1,
    // all the way up to the count of pixels minus one.

    for(int i=0;i<NUMPIXELS;i++){
        byte pixRGB[3];
        mkPixel(&pixelArr[i], pixRGB);

        pixels.setPixelColor(i, pixels.Color(pixRGB[R],
                                             pixRGB[G],
                                             pixRGB[B]));
    }
   
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
 
}
