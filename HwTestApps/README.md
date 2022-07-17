ALGYAN7周年記念基板 テスト用スケッチ
----------------------------------

本スケッチはArduino初心者がライブラリのプログラム例、ネット上で公開されている情報をもとに作成したものであり、誤解、無理、無茶、無駄等が含まれているかもしれませんのでその旨ご了承ください。

## 使用ライブラリ

### ライブラリマネージャからインストールできるもの

* PCF8574 library: https://github.com/xreef/PCF8574_library
* Adafruit GFX Library: https://github.com/adafruit/Adafruit-GFX-Library
* Adafruit ILI9341: https://github.com/adafruit/Adafruit_ILI9341
* Adafruit FRAM SPI: https://github.com/adafruit/Adafruit_FRAM_SPI
* SdFat - Adafruit Fork: https://github.com/adafruit/SdFat
  * **SdFatConfig.h に `#define USE_STANDARD_SPI_LIBRARY 2` 設定が必要です**
* Adafruit ImageReader Library: https://github.com/adafruit/Adafruit_ImageReader

### 別途インストールが必要なもの

* OV7670-ESP32: https://github.com/kobatan/OV7670-ESP32

## 準備

* ドライブルート直下に320×240の`algyan_logo.bmp`のあるFAT16/FAT32フォーマットのSD(SD/SDHCでSDXCは使えません)
* SD を使いたい場合は基板上の `R20` を外す(後述)

## メモ

### 動作

* SWを押下するたびに以下を繰り返します
  * 初期化情報表示
  * Lチカ
  * FRAM読み書き
  * 埋め込み画像のLCD表示
  * カメラ映像のLCD表示
  * SD画像ファイルのLCD表示

### 初期化情報表示

* ライブラリの初期化が成功すればOK出力になりますが、各デバイスの正常動作を保証するものではありません

### SW押下待ち

* 各ステップにそれなりの時間がかかる前提かつとりあえず動作すればよいということでチャタリング除去やONエッジ判定をしていません

### FRAM読み書き

* FRAMの先頭1バイトの値を読み、FRAM1は1、FRAM2は2加算して書き込みます
  * FRAM1,2で動作が変わるように加算する値を変えています

### カメラ映像のLCD表示

* QVGAで1行づつ処理でもレスポンス的に問題なさそうですが、1画面全体をRAM上に持ちたいという場合 `#define CAM_MODE QCIF` にすると解像度が小さくなりますが一括取得、一括出力になります

### SD画像ファイルのLCD表示

* SD上の画像ファイルを表示したい、という目的が達せられればよいということで `SdFat - Adafruit Fork` を設定変更して使っていますが、標準(Arduino core for the ESP32)の `SD` ライブラリでアクセス可能なはずです(リスト表示はできてました)
  * 7周年記念基板ではSDはデフォルトのVSPIではなくHSPIに繋がっているため SdFatConfig.h に `#define USE_STANDARD_SPI_LIBRARY 2` 設定をして SPI オブジェクトを切り替えられる状態で使っています
    * 標準だとこんな感じのはず
```arduino
SPIClass spiSD( HSPI );
SD.begin( SD_CS, spiSD );
```

### 実装全般

* `algyan7th.h` にピン番号定義を置いてあります
* `PCF8574` ライブラリでも問題なく動くだろうと思いますが、通常のGPIOと同じ `pinMode()`,`digitalRead()`,`digitalWrite()` I/F があるので `PCF8574 library` を選択しました
* 配信であった「カメラ/SDの切り替えについて一度対象ピンを入力に切り替えてから」を　`SelectDevice()`　にて実装しています 
  * 繰り返し実行する際にグローバルな初期化だと途中で止まったりしてうまくいかなかったため(手抜きで)カメラについてはここで再初期化(`reset()`)、SD は毎回オブジェクトを生成する歪んだ形になっています
    * SD 関連はポインタにして `SelectDevice()` 中で再生成とかのほうが見通しはよい気がします

### その他

* 当方の環境でも https://twitter.com/pokibon/status/1530729566741729280 のご指摘通り `R20` 接続状態では SD に切り替わりませんでした
* また書き込み・起動時のフラッシュ関連のエラーについては https://twitter.com/pokibon/status/1535801217640591363 のご指摘どおりカメラの`D4`(`IO12`に接続)をプルダウンしていますが、それだけでは収まらなかったため、SDへの切り替えは必要最低限にしつつ `IO12` はプルダウン設定にしています