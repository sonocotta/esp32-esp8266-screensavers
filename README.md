# ESP32/ESP8266 screensavers

6 classic screensavers for esp platform with TFT and VGA support.

This project is more of a nostalgia motivated, rather than technical excersize. You will NOT find here low level code and smart optimisations, only thing I did to make it smoother 
- got rid of FPU operations as much as possbile 
- implemented trigonometry using lookup tables

## Hardware 

Please see [platformio.ini](/src/platformio.ini) file for both TFT and VGA configurations. Tested on following boards

- TFT ST7789 320x240 on [ESP8266 Audio Development Board](https://hackaday.io/project/173620-perfect-i2s-audio-dac-for-esp8266esp32)
- TFT ILI9341 320x240 and ST7789 320x240 on [ESP32 Audio Development Board](https://www.crowdsupply.com/sonocotta/esp32-audio-development-board)
- VGA on [TTGO ESP32 VGA32](http://www.lilygo.cn/prod_view.aspx?TypeId=50033&Id=1083)

ESP8266 is not supported for the last 2 screensavers at the moment. It is definitely possible, but I was not persuasive enough to chase out-of-memory issues.

Generally VGA works much faster, so TFT optimisation are definitely possible and would improve frame rate a lot.

## Starfield

## Tunnel

## Firewall

## Firework

## Shadebobs

## Plasma
