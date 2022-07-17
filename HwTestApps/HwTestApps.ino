// Used Libraries
// * Found in library manager:
//   * PCF8574_library: https://github.com/xreef/PCF8574_library
//   * Adafruit_GFX: https://github.com/adafruit/Adafruit-GFX-Library
//   * Adafruit_ILI9341: https://github.com/adafruit/Adafruit_ILI9341
//   * Adafruit_FRAM_SPI: https://github.com/adafruit/Adafruit_FRAM_SPI
//   * SdFat - Adafruit Fork: https://github.com/adafruit/SdFat
//     with modification: #define USE_STANDARD_SPI_LIBRARY 2 in SdFatConfig.h
//   * Adafruit_ImageReader: https://github.com/adafruit/Adafruit_ImageReader
// * manual install 
//   * OV7670-ESP32: https://github.com/kobatan/OV7670-ESP32

// SD expectation: SD or SDHC, with FAT16 or FAT32, /algyan_logo.bmp at root directory

#include <SPI.h>
#include "algyan7th.h"
#include "Algyan_logo/algyan_logo.h"
#include "PCF8574.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Adafruit_FRAM_SPI.h"
#include "OV7670.h"
// #define USE_STANDARD_SPI_LIBRARY 2 in SdFatConfig.h
#include "SdFat.h"
#include "Adafruit_ImageReader.h"

// Library modules
Adafruit_ILI9341 tft( TFT_CS, TFT_DC, TFT_RST );
PCF8574 pcf8574( PCF8574_ADDR );
Adafruit_FRAM_SPI fram1( FRAM1_CS ), fram2( FRAM2_CS );
#define CAM_MODE QVGA
#if CAM_MODE == QVGA
#define CAM_WIDTH 320
#define CAM_HEIGHT 240
#else
#define CAM_WIDTH 176
#define CAM_HEIGHT 144
uint16_t buf[ CAM_WIDTH * CAM_HEIGHT ];
#endif
OV7670 cam;
const camera_config_t cam_conf = {
    .D0 = 36,
    .D1 = 39,
    .D2 = 34,
    .D3 = 35,
    .D4 = 12,
    .D5 = 2,
    .D6 = 16,
    .D7 = 17,
    .XCLK = 15,
    .PCLK = 14,
    .VSYNC = 13,
    .xclk_freq_hz = 10000000,     // XCLK 10MHz
    .ledc_timer   = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0  
};

// Demo settings
enum State {
    INFO,
    WAIT1,
    BLINK,
    WAIT2,
    FRAM,
    WAIT3,
    LCD,
    WAIT4,
    CAM,
    WAIT5,
    SD,
    WAIT6,
    STATE_NUM
};

State show_info   ( State state, unsigned long wait, char *next_scene );
State wait_sw     ( State state, unsigned long wait, char *next_scene );
State blink_led   ( State state, unsigned long wait, char *next_scene );
State rw_fram     ( State state, unsigned long wait, char *next_scene );
State draw_lcd    ( State state, unsigned long wait, char *next_scene );
State capture_cam ( State state, unsigned long wait, char *next_scene );
State draw_from_sd( State state, unsigned long wait, char *next_scene );
typedef struct {
    State (*func)( State state, unsigned long wait, char *next_scene );
    unsigned long wait;
    char *next_scene;
} TableEntry;
#define NA 0
TableEntry table[STATE_NUM] = {
    { show_info,    NA,   NA              }, /* INFO  */
    { wait_sw,      3000, "LED BLINK"     }, /* WAIT1 */
    { blink_led,    3000, NA              }, /* BLINK */
    { wait_sw,      0,   "FRAM R/W"      }, /* WAIT2 */
    { rw_fram,      NA,   NA              }, /* FRAM  */
    { wait_sw,      3000, "LCD DISP LOGO" }, /* WAIT3 */
    { draw_lcd,     NA,   NA              }, /* LCD   */
    { wait_sw,      3000, "CAM TO LCD"    }, /* WAIT4 */
    { capture_cam,  5000, NA              }, /* CAM   */
    { wait_sw,      0,    "SD TO LCD"     }, /* WAIT5 */
    { draw_from_sd, NA,   NA              }, /* SD    */    
    { wait_sw,      3000, "INFO"          }  /* WAIT6 */
};
inline State next( State state )
{
    return static_cast<State>( ( static_cast<int>( state ) + 1 ) % STATE_NUM );
}

bool pcf8574_init;
bool fram1_init;
bool fram2_init;
bool ov7670_init;
unsigned long lastTime;

enum S_DEV { S_CAM, S_SD };
void SelectDevice( int s_dev ) // Due to unknown reasons, S_DEV instead of int leads compile error
{
    if( s_dev == S_CAM ) {
        pinMode( CAM_VSYNC, INPUT );
        pinMode( CAM_PCLK,  INPUT );
        pcf8574.digitalWrite( CAM_OR_SD , LOW ); // SD
        delay(100);
        Serial.println( "OV7670 camera Init..." );
        esp_err_t err = cam.init( &cam_conf, CAM_MODE, RGB565 );    // カメラを初期化
        if( err != ESP_OK ) {
            Serial.println( "cam.init ERROR" );
        } else {
            ov7670_init = true;
        }
        cam.setPCLK( 2, DBLV_CLK_x4 );  // PCLK 設定 : 10MHz / (pre+1) * 4 --> 13.3MHz  
        cam.vflip( false );
    } else { // S_SD
        pinMode( SD_MOSI, INPUT );
        pinMode( SD_SCK,  INPUT );
        pcf8574.digitalWrite( CAM_OR_SD, HIGH ); // SD
        delay(100);
        pinMode( SD_MOSI, OUTPUT );
        pinMode( SD_SCK,  OUTPUT );
    }
}

void setup() {
    Serial.begin( 115200 );
    delay(1000);
    while( !Serial ) { delay(10); }
    Wire.begin();
    pcf8574.pinMode( CAM_OR_SD, OUTPUT );
    pcf8574.pinMode( SW, INPUT );
    Serial.print( "Init pcf8574..." );
    if( pcf8574.begin() ) {
        Serial.println( "OK" );
        pcf8574_init = true;
    } else {
        Serial.println( "KO" );
    }
    tft.begin();
    tft.setRotation( 3 );
    pinMode( LED, OUTPUT );
    if( fram1.begin() ) {
        Serial.println( "Found SPI FRAM1" );
        fram1_init = true;
    } else {
        Serial.println( "No SPI FRAM1 found ... check your connections\r\n" );
    }
    if( fram2.begin() ) {
        Serial.println( "Found SPI FRAM2" );
        fram2_init = true;
    } else {
        Serial.println( "No SPI FRAM2 found ... check your connections\r\n" );
    }
    SelectDevice( S_CAM );
    gpio_set_pull_mode( GPIO_NUM_12, GPIO_PULLDOWN_ONLY );
}

void loop() {
  static State state = INFO;
  state = table[state].func( state, table[state].wait, table[state].next_scene );
}

#define PRINT( arg )   do { tft.print( arg );   Serial.print( arg ); } while(0)
#define PRINTLN( arg ) do { tft.println( arg ); Serial.println( arg ); } while(0)

State show_info   ( State state, unsigned long wait, char *next_scene )
{
    tft.fillScreen( ILI9341_BLACK );
    tft.setCursor( 0, 0 );
    tft.setTextColor( ILI9341_WHITE );  tft.setTextSize( 2 );
    PRINT( "PCF8574: " );
    PRINTLN( pcf8574_init ? "OK" : "NG" );
    PRINT( "FRAM1: " );
    PRINTLN( fram1_init ? "OK" : "NG" );
    PRINT( "FRAM2: " );
    PRINTLN( fram2_init ? "OK" : "NG" );
    PRINT( "OV7670: " );
    PRINTLN( ov7670_init ? "OK" : "NG" );
    return next( state );
}

State wait_sw     ( State state, unsigned long wait, char *next_scene )
{
    static bool show_message;
    unsigned long curTime = millis();
    if ( curTime - lastTime > wait && !show_message ) {
        tft.fillScreen( ILI9341_BLACK );
        tft.setCursor( 0, 0);
        tft.setTextColor( ILI9341_WHITE );  tft.setTextSize(2);
        PRINT( "Push SW to " );
        PRINTLN( next_scene );
        show_message = true;
    }
    if ( show_message && pcf8574.digitalRead(SW) ) {
        state = next( state );
        show_message = false;
        lastTime = curTime;
    }
    delay( 100 );
    return state;
}

State blink_led   ( State state, unsigned long  wait, char *next_scene )
{
    unsigned long curTime = millis();
    digitalWrite( LED, HIGH );
    delay( 500 );
    digitalWrite( LED, LOW );
    delay(500);
    if ( curTime - lastTime > wait ) {
        state = next( state );
        lastTime = curTime;
    }
    return state;
}

State rw_fram     ( State state, unsigned long  wait, char *next_scene )
{
    uint8_t old1 = fram1.read8( 0x0 );
    fram1.writeEnable( true );
    fram1.write8( 0x0, old1 + 1 );
    fram1.writeEnable( false );
    uint8_t new1 = fram1.read8( 0x0 );

    uint8_t old2 = fram2.read8( 0x0 );
    fram2.writeEnable( true );
    fram2.write8( 0x0, old2 + 2 );
    fram2.writeEnable( false );
    uint8_t new2 = fram2.read8( 0x0 );

    PRINT( "The 1st byte of FRAM1: " ); PRINT( old1 ); PRINT( " -> " ); PRINTLN( new1 );
    PRINT( "The 1st byte of FRAM2: " ); PRINT( old2 ); PRINT( " -> " ); PRINTLN( new2 );

    return next( state );
}

State draw_lcd    ( State state, unsigned long  wait, char *next_scene )
{
    tft.drawRGBBitmap( 0, 0, algyan_logo, ALGYAN_WIDTH, ALGYAN_HEIGHT );
    return next( state );
}

State capture_cam ( State state, unsigned long  wait, char *next_scene )
{
    unsigned long curTime = millis();
#if CAM_MODE == QVGA
    uint16_t *buf;
    for( int y = 0; y < CAM_HEIGHT; ++y ) {
        buf = cam.getLine( y + 1 );
        tft.drawRGBBitmap( 0, y, buf, CAM_WIDTH, 1 );
    }
#else
    cam.getFrame( (uint8_t*)buf );
    tft.drawRGBBitmap( 0, 0, buf, CAM_WIDTH, CAM_HEIGHT );
#endif
    if ( curTime - lastTime > wait ) {
        state = next( state );
        lastTime = curTime;
    }
    return state;
}

State draw_from_sd( State state, unsigned long  wait, char *next_scene )
{
    static bool select;
    if( !select ) {
        SelectDevice( S_SD );
        select = true;
    }
    SPIClass spiSD( HSPI );
    SdFat Sd( &spiSD );
    Adafruit_ImageReader reader( Sd );
    if( Sd.begin( SD_CS, SD_SCK_MHZ( 24 ) ) ) {
        reader.drawBMP("/algyan_logo.bmp", tft, 0, 0);
        SelectDevice( S_CAM );
        select = false;
        state = next( state );
    }
    return state;
}
