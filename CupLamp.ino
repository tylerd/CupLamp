#include <Adafruit_CircuitPlayground.h>

#define CAP_THRESHOLD   20
#define DEBOUNCE        250
#define BRIGHTNESS      60

uint8_t pads[] = {3, 2, 0, 1, 12, 6, 9, 10};
uint8_t numberOfPads = sizeof(pads)/sizeof(uint8_t);

void padPressed(uint8_t pad) {
  
  Serial.print("PAD "); Serial.println(pad); //DEBUG Print Pad Number

  if(pad == 3) {
    setColorRGB(255, 0, 0); //RED
    return;
  }

  if(pad == 10) {
    turnOff();
    return;
  }
}


////////////////////////////////////////////////////////////////////////////
boolean capButton(uint8_t pad) {
  if (CircuitPlayground.readCap(pad) > CAP_THRESHOLD) {
    return true;  
  } else {
    return false;
  }
}

void setColorRGB(int r, int g, int b)
{
  for (int i=0; i<CircuitPlayground.strip.numPixels();++i) {
    CircuitPlayground.setPixelColor(i, r, g, b);
  }
}

void turnOff()
{
  CircuitPlayground.clearPixels();
}

////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
void setup() {
  // Initialize serial.
  Serial.begin(9600); 
  
  // Initialize Circuit Playground library.
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(BRIGHTNESS);
  CircuitPlayground.clearPixels();
}

void loop() {

  // Loop over every pad.
  for (int i=0; i<numberOfPads; i++) {
    
    // Check if pad is touched.
    if (capButton(pads[i])) {
      
      // Do something.
      padPressed(pads[i]);
      
      // But not too often.
      delay(DEBOUNCE);
    }
  }
}
