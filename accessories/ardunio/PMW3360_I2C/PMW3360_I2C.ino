#include <PMW3360.h>
#include <Wire.h>
#include <ezButton.h>

/*
# PMW3360_DATA struct format and description
  - PMW3360_DATA.isMotion      : bool, True if a motion is detected.
  - PMW3360_DATA.isOnSurface   : bool, True when a chip is on a surface
  - PMW3360_DATA.dx, data.dy   : integer, displacement on x/y directions.
  - PMW3360_DATA.SQUAL         : byte, Surface Quality register, max 0x80
                               * Number of features on the surface = SQUAL * 8
  - PMW3360_DATA.rawDataSum    : byte, It reports the upper byte of an 18‐bit counter
                               which sums all 1296 raw data in the current frame;
                               * Avg value = Raw_Data_Sum * 1024 / 1296
  - PMW3360_DATA.maxRawData    : byte, Max/Min raw data value in current frame, max=127
    PMW3360_DATA.minRawData
  - PMW3360_DATA.shutter       : unsigned int, shutter is adjusted to keep the average
                               raw data values within normal operating ranges.
 */

#define SS  10   // Slave Select pin. Connect this to SS on the module.
#define CPI 1600
#define ADDRESS 0x0A

#define J1X 18
#define J1Y 19
#define J2X 9
#define J2Y 8
#define J3X 20
#define J3Y 21

ezButton j1Button(5);
ezButton j2Button(6);
ezButton j3Button(4);

// NOTE: When enabling any of the below debugging pragmas, you must have a
// USB (or serial) cable connected, or the program will never initialize

// Enable basic debugging
// #define DEBUG

// Enable verbose debugging (in case absolutely nothing seems to work)
// #define DEBUG_V

// Enable send debugging (in case you're struggling with data being sent)
//#define DEBUG_S

// Enable receive debugging (in case you're struggling with receiving data)
//#define DEBUG_R

// Enable mouse debugging (in case you're struggling with the trackball working)
// note that this will stop from sending data over the I2C connection
//#define DEBUG_M

// Enable joystick debugging
// note that this will stop from sending data over the I2c connection
// #define DEBUG_J

// Enabe joystick calibration logging, use this to get the min/max readings of the joysticks (move them around to get values)
// note that this will stop from sending data over the I2c connection
// #define CALIB_J

// Keep this in sync with the struct on the receiver side (e.g. QMK)
typedef struct __attribute__((packed)) {
    int16_t dx;
    int16_t dy;
    int16_t j1x;
    int16_t j1y;
    int16_t j1b;
    int16_t j2x;
    int16_t j2y;
    int16_t j2b;
    int16_t j3x;
    int16_t j3y;
    int16_t j3b;
} mouse_data_t;

PMW3360 sensor;

// Map data from SPI data structure for I2C transport
mouse_data_t mapData(PMW3360_DATA spiData) {
  mouse_data_t mouse_data = {0};
  mouse_data.dx = spiData.dx;
  mouse_data.dy = spiData.dy;
  return mouse_data;
}

#ifdef CALIB_J
  int j1xMax = 0;
  int j1xMin = 1000;
  int j1yMax = 0;
  int j1yMin = 1000;
  int j2xMax = 0;
  int j2xMin = 1000;
  int j2yMax = 0;
  int j2yMin = 1000;
  int j3xMax = 0;
  int j3xMin = 1000;
  int j3yMax = 0;
  int j3yMin = 1000;
#endif

// Called when controller asks for data
void requestEvent() {
  #ifdef DEBUG_R
    Serial.println("I2C requested");
  #endif
  PMW3360_DATA data = sensor.readBurst();
  int j1x = analogRead(J1X);
  int j1y = analogRead(J1Y);
  int j2x = analogRead(J2X);
  int j2y = analogRead(J2Y);
  int j3x = analogRead(J3X);
  int j3y = analogRead(J3Y);

  #ifdef CALIB_J
    j1xMax = max(j1xMax, j1x);
    j1xMin = min(j1xMin, j1x);
    j1yMax = max(j1yMax, j1y);
    j1yMin = min(j1yMin, j1y);
    j2xMax = max(j2xMax, j2x);
    j2xMin = min(j2xMin, j2x);
    j2yMax = max(j2yMax, j2y);
    j2yMin = min(j2yMin, j2y);
    j3xMax = max(j3xMax, j3x);
    j3xMin = min(j3xMin, j3x);
    j3yMax = max(j3yMax, j3y);
    j3yMin = min(j3yMin, j3y);

    Serial.print("\tj1xMax:");
    Serial.print(   j1xMax);
    Serial.print("\tj1xMin:");
    Serial.print(   j1xMin);
    Serial.print("\tj1yMax:");
    Serial.print(   j1yMax);
    Serial.print("\tj1yMin:");
    Serial.print(   j1yMin);

    Serial.print("\tj2xMax:");
    Serial.print(   j2xMax);
    Serial.print("\tj2xMin:");
    Serial.print(   j2xMin);
    Serial.print("\tj2yMax:");
    Serial.print(   j2yMax);
    Serial.print("\tj2yMin:");
    Serial.print(   j2yMin);

    Serial.print("\tj3xMax:");
    Serial.print(   j3xMax);
    Serial.print("\tj3xMin:");
    Serial.print(   j3xMin);
    Serial.print("\tj3yMax:");
    Serial.print(   j3yMax);
    Serial.print("\tj3yMin:");
    Serial.println(   j3yMin);
  #endif
  #ifdef DEBUG_J
    Serial.print("j1x:");
    Serial.print(j1x);
    Serial.print("\tj1y:");
    Serial.print(j1y);
    Serial.print("\tj2x:");
    Serial.print(j2x);
    Serial.print("\tj2y:");
    Serial.print(j2y);
    Serial.print("\tj3x:");
    Serial.print(j3x);
    Serial.print("\tj3y:");
    Serial.print(j3y);
    Serial.print("\t\tjb1:");
    Serial.print(j1Button.getState());
    Serial.print("\tjb2:");
    Serial.print(j2Button.getState());
    Serial.print("\tjb3:");
    Serial.println(j3Button.getState());
  #endif

  mouse_data_t mouse_data;
  if(data.isOnSurface && data.isMotion) {
    #ifdef DEBUG_M
      Serial.print("dx: ");
      Serial.print(data.dx);
      Serial.print("\tdy: ");
      Serial.println(data.dy);
    #endif
    #ifdef DEBUG_S
      Serial.print("up: ");
      Serial.print(mouse_data.up);
      Serial.print("\t\tdown: ");
      Serial.print(mouse_data.down);
      Serial.print("\t\tleft: ");
      Serial.print(mouse_data.left);
      Serial.print("\t\tright: ");
      Serial.println(mouse_data.right);
    #endif
    mouse_data = mapData(data);
  } else {
    #ifdef DEBUG_V
      Serial.println("no mouse data");
    #endif
    mouse_data = {0};
  }
  mouse_data.j1b = j1Button.getState();
  mouse_data.j2b = j2Button.getState();
  mouse_data.j3b = j3Button.getState();
  mouse_data.j1x = j1x;
  mouse_data.j1y = j1y;
  mouse_data.j2x = j2x;
  mouse_data.j2y = j2y;
  mouse_data.j3x = j3x;
  mouse_data.j3y = j3y;
  mouseWrite(&mouse_data);
}

// Write mouse data to I2C bus
void mouseWrite(mouse_data_t* data) {
  Wire.write((uint8_t*)data, sizeof(*data));
}


void setup() {
  #if defined(DEBUG) || defined(DEBUG_R) || defined(DEBUG_S) || defined(DEBUG_V) || defined(DEBUG_M) || defined(DEBUG_J) || defined(CALIB_J)
    Serial.begin(9600);
    while(!Serial);
  #endif

  bool signatureCheck = sensor.begin(SS, CPI);
  #ifdef DEBUG
    if(sensor.begin(SS)) {
      Serial.println("Sensor initialization successed");
    }
    else {
      Serial.println("Sensor initialization failed");
    }
  #endif
  #if !defined(DEBUG_M) && !defined(DEBUG_J)
    Wire.begin(ADDRESS);
    Wire.onRequest(requestEvent);
  #endif
  #if defined(DEBUG_R) || defined(DEBUG_S)
    Serial.print("I2C listening at address: ");
    Serial.println(ADDRESS);
  #endif
}

void loop() {
  j2Button.loop();
  j1Button.loop();
  j3Button.loop();
  #if defined(DEBUG_M) || defined(DEBUG_J) || defined(CALIB_J)
    requestEvent();
  #endif
}
