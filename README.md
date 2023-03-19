# bluepill-android-wii-classiccon-mouse

Arduino sample code that use wii classic controller as a mouse.

## Requirement

- [STM32F103C8T6 minimum Development Board(BluePill)](https://www.aitendo.com/product/13348)
- [ST Link V2 Programmer For STM8 STM32](https://www.aitendo.com/product/16082)
- Arduino IDE (Version: 1.8.5)
- wii classic controller : RVL-005(02)

##  Pin connections

|Controller  |BluePill  |Note  |
|---|---|---|
|GND  | GND ||
|5V  | 5V ||
|SDA  | PB_7 ||
|SCL  | PB_6 ||

## Usage 

1. Install [Arduino_STM32](https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Installation)

1. Build & upload project with Arduino

1. Use controller  
　Left-Stick：mouse cursor  
　B-Button：Left-Click 
　A-Button：Right-Click 
     ※wait for about 2 seconds until calibration

## Licence

   see [LICENSE.md](./LICENSE.md) 

## Related Links
* [pinout](https://ht-deko.com/arduino/pic/stm32_pinout_01.png)
* [iroiro](http://www.mf.ccnw.ne.jp/kamehouse102/STM32F103.html)
* [i2c](https://www.electronicshub.org/how-to-use-i2c-in-stm32f103c8t6/)
* [Mouse.h](https://github.com/arduino-libraries/Mouse/blob/master/src/Mouse.h)
* [Wii Classic Controllerの接続](http://try3dcg.world.coocan.jp/note/i2c/wiicontroller.html)
