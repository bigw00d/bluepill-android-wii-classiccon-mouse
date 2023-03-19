// wii classic controller mouse keyboard converter

#include <USBComposite.h>
#include <Wire.h>

USBHID HID;
HIDKeyboard Keyboard(HID);
HIDMouse mouse(HID);

//I2C1:
//SDA  PB7 (23)
//SCL PB6 (22)
//
//I2C2:
//SDA PB11 (27)
//SCL PB10 (26)

#define CONTROLLER_ADDRESS 0x52
static uint8_t values[8];

static uint8_t analogLX; // Left Side Anarog Stick X  - 6Bit
static uint8_t analogLY; // Left Side Anarog Stick Y  - 6Bit
//static uint8_t analogRX; // Right Side Anarog Stick X - 5Bit
//static uint8_t analogRY; // Right Side Anarog Stick Y - 5Bit
//static uint8_t analogLB; // Left Side Anarog Buttob   - 5Bit
//static uint8_t analogRB; // Right Side Anarog Button  - 5Bit
static uint16_t pushButton ;

uint8_t oldAnalogLX; // Left Side Anarog Stick X  - 6Bit
uint8_t oldAnalogLY; // Left Side Anarog Stick Y  - 6Bit
uint16_t oldPushButton ;

#define STABILIZE_COUNT 10
static uint8_t initXposi;
static uint8_t initYposi;
static uint8_t initCnt;

void setup() {
  initCnt = 0;
  initXposi = 0;
  initYposi = 0;
  
  analogLX = 0;
  analogLY = 0;
  pushButton = 0;

  oldAnalogLX = 0;
  oldAnalogLY = 0;
  oldPushButton = 0;

//  Wire2.begin();
  Wire.begin();

  HID.begin(HID_KEYBOARD_MOUSE);
  Keyboard.begin();
  delay(2000);
//  Keyboard.println("Hello");            // 文字列を出力
  init_con();
}

void init_con() {
  Wire.beginTransmission(CONTROLLER_ADDRESS);
  Wire.write(0xF0);
  Wire.write(0x55);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(CONTROLLER_ADDRESS);
  Wire.write(0xFB);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(10);  
}

void send_zero() {
  Wire.beginTransmission(CONTROLLER_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(10);
}

void scan() {
  int count = 0;
  int readLen = Wire.requestFrom(CONTROLLER_ADDRESS, 8);
  
  while(Wire.available()) {
    values[count] = Wire.read();
    delay(2);
    count++;
    if (count >= 8) {
      break;
    }
  }
  send_zero();

  if(count > 0){

    if (readLen == 8 && count == 8) {
      if (initCnt < STABILIZE_COUNT)
      {
        initCnt++;
      }
      else {
        if (initXposi == 0) {
          initXposi = analogLX;
          initYposi  = analogLY;
        }
        analogLX = values[0] & 0b00111111 ;
        analogLX = values[0] & 0b00111111 ;
        analogLY = values[1] & 0b00111111 ;
        ((uint8_t *)&pushButton)[0] = ~values[4] ;
        ((uint8_t *)&pushButton)[1] = ~values[5] ;
      }
    }
  }
 
}

void loop() {
  scan();
  delay(10);

  mouse.move(((signed char)(analogLX - initXposi)/2)*2, ((signed char)(initYposi - analogLY)/2)*2);

  if (pushButton != oldPushButton)
  {
      if (pushButton & 0x4000) {
        mouse.press(MOUSE_LEFT);
      }
      else {
        mouse.release(MOUSE_LEFT);
      }

      if (pushButton & 0x1000) {
        mouse.press(MOUSE_RIGHT);
      }
      else {
        mouse.release(MOUSE_RIGHT);
      }

      if (pushButton & 0x0008) { //HOME
        Keyboard.print("HOME");
      }

      oldPushButton = pushButton;
  }

}
