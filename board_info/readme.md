[board_design]: img/algyan-7th.png
[board_sch]: img/algyan-7th-sch.png
[esp32_pin_assign]: img/esp32_pin_assign.png
[devkitc_pin_assign]: img/devkitc_pin_assign.png
[pcf8674_pin_assign]: img/pcf8674_pin_assign.png

# Board Info

## <a name="S0">0. Index</a>

* [1. Board Design](#S1)
* [2. Schematics](#S2)
* [3. Pin Assign](#S3)
* [4. Body of Materials](#S4)
  * [4-1. Parts set A(お手軽)](#S4-1)
  * [4-2. Parts set B(手作りFULL)](#S4-2)

---

## <a name="S1">1. Board Design</a>

This board is designed by **Designed by EAGLE 9.6.2**.

* File(brd) : **algyan-7th.brd**
* File(gerber) : **algyan-7th_2022-04-07.zip**
* Image(png) : **img/algyan-7th.png**
    ![Board][board_design]

[↑ Back to Index](#S0)

---

## <a name="S2">2. Schematics</a>

* File(sch) : **algyan-7th.sch**
* File(pdf) : **algyan-7th.pdf**
* Image(png) : **img/algyan-7th-sch.png**  
    ![Board_sch][board_sch]

[↑ Back to Index](#S0)

---

## <a name="S3">3. Pin Assign</a>

* Image(png) : **img/esp32_pin_assign.png**  
    ![esp32_pin_assign][esp32_pin_assign]

* Image(png) : **img/devkitc_pin_assign.png**  
    ![devkitc_pin_assign][devkitc_pin_assign]

* Image(png) : **img/pcf8674_pin_assign.png**  
    ![pcf8674_pin_assign][pcf8674_pin_assign]

[↑ Back to Index](#S0)

---

## <a name="S4">4. Body of Materials</a>

### <a name="S4-1">4-1. Parts set A(お手軽)</a>

|No.|部品名|型番・値|個数|購入リスト|種類|オンライン販売URL|
|:-:|:---:|:------:|:-:|:--------:|:----|:---------------|
|4|ESP32-DevKitC-32E(4MB)||1|M-15673 1|U4|https://akizukidenshi.com/catalog/g/gM-15673/|
|5|FRAM(2Mbit) MB85RS2MT|MB85RS2MT|2|-|U5、U6|https://www.chip1stop.com/view/dispDetail/DispDetail?partId=FJTU-0057134|
|6|I/Oエキスパンダー PCF8574N|PCF8674N|1|I-13522 1|U7|https://akizukidenshi.com/catalog/g/gI-13522/|
|7|Quad Bus Buffer|TC74VHC125F|1|-|U8|https://www.marutsu.co.jp/pc/i/14698/|
|8|Quad Bus Buffer|TC74VHC126F|1|-|U9|https://www.marutsu.co.jp/pc/i/14699/|
|9|2.2\" ILI9341 SPI TFT LCDディスプレイ240x320 ILI9341 LCDスクリーン|2.2_TFT_LCD|1|-|U10|https://www.amazon.co.jp/dp/B08D7D14X9<br>https://www.amazon.co.jp/dp/B01DXBI3I8|
|10|エレクトレットコンデンサーマイク（ＥＣＭ）|C9767|1|P-01810 1|U11|https://akizukidenshi.com/catalog/g/gP-01810/|
|11|CMOS OV7670 640x480 カメラモジュール|OV7670|1|-|CAM1|https://www.amazon.co.jp/dp/B08B39JGDS|
|12|チップ抵抗(2012)|10kΩ|3|R-11797 3|R8、R9、R11、R12、R13、R14、R15、R16、R17、R18、R19、R20|https://akizukidenshi.com/catalog/g/gR-11797/|
|13|チップ抵抗(2012)|1kΩ|1|R-11796 1|R10、R21|https://akizukidenshi.com/catalog/g/gR-11796/|
|14|チップ抵抗(2012)|100Ω|1|R-11795 1|R22、R23|https://akizukidenshi.com/catalog/g/gR-11795/|
|16|チップコンデンサ(2012)|0.1uF|1|P-14573 1|C8、C9、C10、C11、C13、C14|https://akizukidenshi.com/catalog/g/gP-14573/|
|18|チップタクトSW|TVAF06-A020B|1|P-14888 1|SW|https://akizukidenshi.com/catalog/g/gP-14888/|
|20-1|チップLED(赤色)|OSR50805C1C|1|I-06419 1|LED1|https://akizukidenshi.com/catalog/g/gI-06419/|
|21|L型ピンヘッダ3Pin|PH-1X3RG(2)|1|C-15510 1|CN1|https://akizukidenshi.com/catalog/g/gC-15510/|
|22|3.5mm小型ステレオミニジャック　基板取付用|ST-005-G|1|C-02460 1|CN2|https://akizukidenshi.com/catalog/g/gC-02460/|
|25|Ｇｒｏｖｅコネクタ　Ｌ型　スルーホール|Grove Female Header - DIP-4P-2.0mm-90D|1|C-12634 1|CN5、CN6、CN7|https://akizukidenshi.com/catalog/g/gC-12634/|
|26|ダブルピンソケット　（低メス）　２×１３　（２６Ｐ）|2214S-26SG-36|1|C-03139 1|CAM1用ソケット|https://akizukidenshi.com/catalog/g/gC-03139/|
|27|シングルピンソケット　（低メス）　１×２０　（２０Ｐ）|2212S-20SG-36|1|C-03138 1|U4用ソケット、U10用ソケット|https://akizukidenshi.com/catalog/g/gC-03138/|
|28|ピンヘッダ　１×６　（６Ｐ）|PH-1x6SG/RH|1|C-01669 1|U10用ピンヘッダ(SDカードI/F)|https://akizukidenshi.com/catalog/g/gC-01669/|
|29|プラスチックナット＋連結（６角ジョイント）スペーサー（１０ｍｍ）セット||1|P-01864 1|U10、CAM1取り付け用スペーサ、ナット|https://akizukidenshi.com/catalog/g/gP-01864/|
|30|３ｍｍプラネジ（５ｍｍ）（１００個入）||1|P-10358 1|U10、CAM1取り付け用ネジ|https://akizukidenshi.com/catalog/g/gP-10358/|

[↑ Back to Index](#S0)

---

### <a name="S4-2">4-2. Parts set B(手作りFULL)</a>

|No.|部品名|型番・値|個数|購入リスト|種類|オンライン販売URL|
|:-:|:---:|:------:|:-:|:--------:|:----|:---------------|
|1|ESP32-WROOM-32E(16MB)||1|M-15675 1|U1|https://akizukidenshi.com/catalog/g/gM-15675/|
|2|三端子レギュレータ|NJM2845DL1|1|I-11299 1|U2|https://akizukidenshi.com/catalog/g/gI-11299/|
|3|USBシリアルIC|FT231XS-R|1|I-06713 1|U3|https://akizukidenshi.com/catalog/g/gI-06713/|
|5|FRAM(2Mbit) MB85RS2MT|MB85RS2MT|2|-|U5、U6|https://www.chip1stop.com/view/dispDetail/DispDetail?partId=FJTU-0057134|
|6|I/Oエキスパンダー PCF8574N|PCF8674N|1|I-13522 1|U7|https://akizukidenshi.com/catalog/g/gI-13522/|
|7|Quad Bus Buffer|TC74VHC125F|1|-|U8|https://www.marutsu.co.jp/pc/i/14698/|
|8|Quad Bus Buffer|TC74VHC126F|1|-|U9|https://www.marutsu.co.jp/pc/i/14699/|
|9|2.2" ILI9341 SPI TFT LCDディスプレイ240x320 ILI9341 LCDスクリーン|2.2_TFT_LCD|1|-|U10|https://www.amazon.co.jp/dp/B08D7D14X9<br>https://www.amazon.co.jp/dp/B01DXBI3I8|
|10|エレクトレットコンデンサーマイク（ＥＣＭ）|C9767|1|P-01810 1|U11|https://akizukidenshi.com/catalog/g/gP-01810/|
|11|CMOS OV7670 640x480 カメラモジュール|OV7670|1|-|CAM1|https://www.amazon.co.jp/dp/B08B39JGDS|
|12|チップ抵抗(2012)|10kΩ|4|R-11797 4|R1、R2、R6、R7、R8、R9、R11、R12、R13、R14、R15、R16、R17、R18、R19、R20|https://akizukidenshi.com/catalog/g/gR-11797/|
|13|チップ抵抗(2012)|1kΩ|1|R-11796 1|R3、R4、R5、R10、R21|https://akizukidenshi.com/catalog/g/gR-11796/|
|14|チップ抵抗(2012)|100Ω|1|R-11795 1|R22、R23|https://akizukidenshi.com/catalog/g/gR-11795/|
|15|チップコンデンサ(3216)|22uF|1|P-06038 1|C1、C2|https://akizukidenshi.com/catalog/g/gP-06038/|
|16|チップコンデンサ(2012)|0.1uF|1|P-14573 1|C3、C5、C7、C8、C9、C10、C11、C12、C13、C14|https://akizukidenshi.com/catalog/g/gP-14573/|
|17|チップコンデンサ(1608)|0.01uF|1|P-13387 1|C4、C6|https://akizukidenshi.com/catalog/g/gP-13387/|
|18|チップタクトSW|TVAF06-A020B|1|P-14888 1|SW、EN、BOOT|https://akizukidenshi.com/catalog/g/gP-14888/|
|19|チップトランジスタ|2SC2712|1|I-00761 1|T1、T2|https://akizukidenshi.com/catalog/g/gI-00761/|
|20-1|チップLED(赤色)|OSR50805C1C|1|I-06419 1|PWR、TXD、RXD、LED1|https://akizukidenshi.com/catalog/g/gI-06419/|
|21|L型ピンヘッダ3Pin|PH-1X3RG(2)|1|C-15510 1|CN1|https://akizukidenshi.com/catalog/g/gC-15510/|
|22|3.5mm小型ステレオミニジャック　基板取付用|ST-005-G|1|C-02460 1|CN2|https://akizukidenshi.com/catalog/g/gC-02460/|
|23|USB Type-CコネクタDIP化キット|AE-USB2.0-TYPE-C-5077R|1|K-15426 1|CN3USB|https://akizukidenshi.com/catalog/g/gK-15426/|
|24|microUSBコネクタ|ZX62-B-5PA(33)|1|C-11183 1|CN4USB|https://akizukidenshi.com/catalog/g/gC-11183/|
|25|Ｇｒｏｖｅコネクタ　Ｌ型　スルーホール|Grove Female Header - DIP-4P-2.0mm-90D|1|C-12634 1|CN5、CN6、CN7|https://akizukidenshi.com/catalog/g/gC-12634/|
|26|ダブルピンソケット　（低メス）　２×１３　（２６Ｐ）|2214S-26SG-36|1|C-03139 1|CAM1用ソケット|https://akizukidenshi.com/catalog/g/gC-03139/|
|27|シングルピンソケット　（低メス）　１×２０　（２０Ｐ）|2212S-20SG-36|1|C-03138 1|U10用ソケット|https://akizukidenshi.com/catalog/g/gC-03138/|
|28|ピンヘッダ　１×６　（６Ｐ）|PH-1x6SG/RH|1|C-01669 1|U10用ピンヘッダ(SDカードI/F)|https://akizukidenshi.com/catalog/g/gC-01669/|
|29|プラスチックナット＋連結（６角ジョイント）スペーサー（１０ｍｍ）セット||1|P-01864 1|U10、CAM1取り付け用スペーサ、ナット|https://akizukidenshi.com/catalog/g/gP-01864/|
|30|３ｍｍプラネジ（５ｍｍ）（１００個入）||1|P-10358 1|U10、CAM1取り付け用ネジ|https://akizukidenshi.com/catalog/g/gP-10358/|

[↑ Back to Index](#S0)

---
