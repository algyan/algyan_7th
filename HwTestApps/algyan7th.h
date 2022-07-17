#pragma once
#ifndef ALGYAN7TH_H
#define ALGYAN7TH_H

/////////////////////////////
// misc

#define LED  26 /* out */
#define MIC  33 /* analog in  */
#define JACK 25 /* analog out */

/////////////////////////////
// IO EXPANDER: PCF8574

#define PCF8574_ADDR 0x20
#define CAM_OR_SD    P4
#define SW           P5
// I2C
// SDA 21
// SCL 22

/////////////////////////////
// SPI TFT: ILI9341

#define TFT_CS   5   /* out */
#define TFT_DC   27  /* out */
#define TFT_RST  255 /* not used */
// VSPI
// TFT_SCK  18 /* out */
// TFT_MISO 19 /* in  */
// TFT_MOSI 23 /* out */

/////////////////////////////
// SD on ILI9341

#define SD_CS   15 /* out */
// HSPI
#define SD_SCK  14 /* out */
#define SD_MISO 12 /* in  */
#define SD_MOSI 13 /* out */

/////////////////////////////
// CAMERA: OV7670

#define CAM_ADDR 0x21
#define CAM_VSYNC 13 /* in */
// CAM_HREF /* not used */
#define CAM_PCLK  14 /* in */
#define CAM_XCLK  15 /* out */
#define CAM_D0    36 /* in */
#define CAM_D1    39 /* in */
#define CAM_D2    34 /* in */
#define CAM_D3    35 /* in */
#define CAM_D4    12 /* in */
#define CAM_D5    2  /* in */
#define CAM_D6    16 /* in */
#define CAM_D7    17 /* in */
// I2C
// SDA 21
// SCL 22

/////////////////////////////
// FRAM

#define FRAM1_CS 4  /* out */
#define FRAM2_CS 32 /* out */
// VSPI
// FRAM_SCK  18 /* out */
// FRAM_MISO 19 /* in  */
// FRAM_MOSI 23 /* out */

#endif
