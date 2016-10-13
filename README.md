# NeoTwinkle

### Description
NeoTwinkle is an Arduino program that controls a series of [NeoPixels](https://www.adafruit.com/category/168) so that they glow random colors for a random amount of time.

### Control
The behavior of NeoTwinkle is controlled by a few globals:

* `NUMPIXELS`: The number of NeoPixels chained together
* `MAX_RGB`: The maximum possible value for the red, green, and blue channels
* `MAX_BRIGHT`: Controls how bright the pixel can be when fully lit.  The name is a little bit misleading since the base level of brightness is 128 (out of a possible 0-255) and a random number with the range of 0 to `MAX_BRIGHT` is added to it.
* `MAX_STEP`: Is the maximum possible  step for the change in brightness
* `RAND_DELAY`: This sort of controls how long the pixel should be at max bright or black.  This value is used to control the "life" of each pixel
