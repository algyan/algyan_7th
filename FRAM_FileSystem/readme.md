# ALGYAN 7th IoT基板のFRAMでファイルシステムを使う

ALGYAN 7th IoT基板 (以下、ALGYAN基板) のFRAMにファイルシステムをのせて、SDカードと同じようにファイルの読み書きをする方法を説明します。

## ライブラリをインストールする

FRAMFSライブラリは下記のGitHubリポジトリで公開しています。[リリース](https://github.com/lipoyang/FRAMFS/releases)からZIPファイルをダウンロードして解凍したフォルダをArduinoのlibrariesフォルダに配置してください。または、Arduino IDEで「スケッチ」→「ファイルをインクルード」→「.ZIP形式のライブラリをインストール」でZIPファイルを指定してインストールしてください。

* [https://github.com/lipoyang/FRAMFS/](https://github.com/lipoyang/FRAMFS/)

※ このライブラリはESP32専用です。他のArduinoボードでは使えません。

## サンプルスケッチを動かしてみる
「ファイル」→「スケッチ例」→「FRAMFS」から2つのサンプルスケッチが利用できます。
| サンプルスケッチ | 説明 |
| ---- | ---- |
| FRAMFS_Test1 | 1個のFRAM(ALGYAN基板のU5)に対し、<br>ファイルの読み書きを行います。|
| FRAMFS_Test2 | 2個のFRAM(ALGYAN基板のU5とU6)に対し、<br>ファイルの読み書きを行います。 |

Serialにログ出力するので、シリアルターミナルで受信し、ソースと見比べて動作を確認してください。ボーレートは115200です。

## FRAMFSライブラリの使い方

FRAMFSライブラリはSDライブラリ(公式のSDカードライブラリ)とほとんど同じAPIを持っています。SDライブラリを使ったことがあれば、同じように使うことが出来ます。

主な独自のAPIのみここで説明します。SDライブラリと共通のAPIについては[SDライブラリのリファレンス](https://www.arduino.cc/reference/en/libraries/sd/)を参照してください。

### FRAMFS(size)
コンストラクタではFRAMのサイズをkB単位で指定します。ALGYAN基板のFRAMは256kB(2Mbit)なので、256を指定します。

### bigin(ssPin)
begin()ではSDライブラリと同様にSS(スレーブセレクト)のピンを指定します。省略すると4番ピンが設定されます。
また、第2引数以降に詳細設定を指定することもできます。詳しくは[FRAMFSライブラリのREADME](https://github.com/lipoyang/FRAMFS)を参照してください。

成功するとtrue、失敗するとfalseを返します。初回はFRAMが未フォーマットなので false を返します。

### isUnformatted()
bigin()がfalseを返した場合、isUnformatted()で未フォーマットかチェックできます。未フォーマットの場合はtrueを返します。

### format(ssPin)
FRAMを強制フォーマットします。引数の指定はbegin()と同じです。

### beginOrFormat(ssPin)
FRAMが未フォーマットならフォーマットします。引数の指定はbegin()と同じです。

### totalBytes()
FRAMのフォーマット容量のバイト数を返します。フォーマット容量はデバイスそのもののメモリ容量より小さくなります。

### usedBytes()
FRAMの使用領域のバイト数を返します。メモリ容量は1セクタ=512バイト単位で使用されます。


