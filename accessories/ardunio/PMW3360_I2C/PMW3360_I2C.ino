#include <PMW3360.h>
#include <Wire.h>

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

// NOTE: When enabling any of the below debugging pragmas, you must have a 
// USB (or serial) cable connected, or the program will never initialize 

// Enable basic debugging 
//#define DEBUG
// Enable verbose debugging (in case absolutely nothing seems to work)
//#define DEBUG_V
// Enable send debugging (in case you're struggling with data being sent)
//#define DEBUG_S
// Enable receive debugging (in case you're struggling with receiving data)
//#define DEBUG_R
// Enable mouse debugging (in case you're struggling with the trackball working)
//#define DEBUG_M

// Keep this in sync with the struct on the receiver side (e.g. QMMK)
typedef struct __attribute__((packed)) {
    uint8_t up;
    uint8_t down;
    uint8_t left;
    uint8_t right;
} mouse_data_t;

PMW3360 sensor;

// Map data from 16 bit signed ints to the 8 bit unsigned ints for I2C transport
mouse_data_t mapData(int16_t dx, int16_t dy) {
  mouse_data_t mouse_data = {0};
  if (dx < 0) {
    mouse_data.down = (uint8_t) abs(dx);
  } else {
    mouse_data.up = (uint8_t) dx;
  }
  if (dy < 0) {
    mouse_data.left = (uint8_t) abs(dy);
  } else {
    mouse_data.right = (uint8_t) dy;
  }
  return mouse_data;
}

// Called when controller asks for data
void requestEvent() {
  #ifdef DEBUG_R
    Serial.println("I2C requested");
  #endif
  PMW3360_DATA data = sensor.readBurst();
  
  if(data.isOnSurface && data.isMotion) {
    #ifdef DEBUG
      Serial.print("dx: ");
      Serial.print(data.dx);
      Serial.print("\tdy: ");
      Serial.println(data.dy);
    #endif
    mouse_data_t mouse_data = mapData(data.dx, data.dy);
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
    mouseWrite(&mouse_data);
  } else {
    #ifdef DEBUG_V
      Serial.println("no mouse data");
    #endif
    mouse_data_t mouse_data = {0};
    mouseWrite(&mouse_data);
  }
}

// Write mouse data to I2C bus
void mouseWrite(mouse_data_t* data) {
  Wire.write((uint8_t*)data, sizeof(data) * 2);
}


void setup() {
  #if defined(DEBUG) || defined(DEBUG_R) || defined(DEBUG_S) || defined(DEBUG_V) || defined(DEBUG_M)
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
  #ifndef DEBUG_M
    Wire.begin(ADDRESS);
    Wire.onRequest(requestEvent);
  #endif
  #if defined(DEBUG_R) || defined(DEBUG_S)
    Serial.print("I2C listening at address: ");
    Serial.println(ADDRESS);
  #endif
}

void loop() {
  #ifdef DEBUG_M
    requestEvent();
  #endif
}
