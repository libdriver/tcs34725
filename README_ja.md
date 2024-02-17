[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TCS34725

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tcs34725/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TCS34725デバイスは、赤、緑、青（RGB）、およびクリアな光検知値のデジタルリターンを提供します。オンチップに統合され、カラーセンシングフォトダイオードにローカライズされたIRブロッキングフィルターは、入射光のIRスペクトル成分を最小限に抑え、カラー測定を正確に行うことができます。高感度、広いダイナミックレンジ、およびIRブロッキングフィルターにより、TCS34725は、さまざまな照明条件の下で、減衰材料を介して使用するための理想的なカラーセンサーソリューションになります。 TCS34725カラーセンサーには、RGB LEDバックライト制御、ソリッドステート照明、健康/フィットネス製品、産業プロセス制御、医療診断機器など、幅広いアプリケーションがあります。さらに、IRブロッキングフィルターにより、TCS34725は周囲光検知（ALS）を実行できます。周囲光検知は、携帯電話、ノートブック、TVなどのディスプレイベースの製品で広く使用されており、照明環境を検知し、自動ディスプレイ輝度を有効にして、最適な表示と省電力を実現します。 TCS34725自体は、光検知測定の間に低電力待機状態に入り、平均消費電力をさらに削減できます。

LibDriver TCS34725は、LibDriverによって起動されたTCS34725の全機能ドライバーであり、RGBカラー読み取り、輝度読み取り、輝度割り込み検出などの機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver TCS34725のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver TCS34725用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver TCS34725ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver TCS34725プログラミング例が含まれています。

/ docディレクトリには、LibDriver TCS34725オフラインドキュメントが含まれています。

/ datasheetディレクトリには、TCS34725データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

```C
#include "driver_tcs34725_basic.h"

uint8_t res;
uint8_t i;
uint16_t red, green, blue, clear;

res = tcs34725_basic_init();
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    tcs34725_interface_delay_ms(1000);
    res = tcs34725_basic_read((uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear);
    if (res != 0)
    {
        (void)tcs34725_basic_deinit();

        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: red is %d.\n", red);
    tcs34725_interface_debug_print("tcs34725: green is %d.\n", green);
    tcs34725_interface_debug_print("tcs34725: blue is %d.\n", blue);
    tcs34725_interface_debug_print("tcs34725: clear is %d.\n", clear);
    
    ...
    
}

...

(void)tcs34725_basic_deinit();

return 0;
```

#### example interrupt

```c
#include "driver_tcs34725_interrupt.h"

uint8_t res;
uint8_t i;
uint16_t red, green, blue, clear;
uint8_t g_flag;

void gpio_irq(void)
{
    g_flag = 1;
}

res = tcs34725_interrupt_init(TCS34725_INTERRUPT_MODE_EVERY_RGBC_CYCLE, 10, 100);
if (res != 0)
{
    return 1;
}
res = gpio_interrupt_init();
if (res != 0)
{
    (void)tcs34725_interrupt_deinit();

    return 1;
}

...

g_flag = 0;
for (i = 0; i < 3; i++)
{
    tcs34725_interface_delay_ms(1000);
    res = tcs34725_interrupt_read((uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: read data failed.\n");
        (void)tcs34725_interrupt_deinit();
        (void)gpio_interrupt_deinit();

        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: red is %d.\n", red);
    tcs34725_interface_debug_print("tcs34725: green is %d.\n", green);
    tcs34725_interface_debug_print("tcs34725: blue is %d.\n", blue);
    tcs34725_interface_debug_print("tcs34725: clear is %d.\n", clear);
    if (g_flag != 0)
    {
        tcs34725_interface_debug_print("tcs34725: find interrupt.\n");

        break;
    }
    
    ...
    
}

...

(void)tcs34725_interrupt_deinit();
(void)gpio_interrupt_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/tcs34725/index.html](https://www.libdriver.com/docs/tcs34725/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。