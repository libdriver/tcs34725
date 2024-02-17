[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TCS34725

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tcs34725/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TCS34725 장치는 적색, 녹색, 청색(RGB) 및 선명한 광 감지 값의 디지털 반환을 제공합니다. 온칩에 통합되고 색상 감지 포토다이오드에 국한된 IR 차단 필터는 들어오는 빛의 IR 스펙트럼 성분을 최소화하고 색상을 정확하게 측정할 수 있도록 합니다. TCS34725는 고감도, 넓은 동적 범위 및 IR 차단 필터를 통해 다양한 조명 조건 및 감쇠 재료를 통해 사용하기에 이상적인 컬러 센서 솔루션입니다. TCS34725 컬러 센서는 RGB LED 백라이트 제어, 솔리드 스테이트 조명, 건강/피트니스 제품, 산업 공정 제어 및 의료 진단 장비를 포함한 광범위한 애플리케이션을 가지고 있습니다. 또한 IR 차단 필터를 통해 TCS34725는 주변광 감지(ALS)를 수행할 수 있습니다. 주변광 감지는 휴대폰, 노트북 및 TV와 같은 디스플레이 기반 제품에 널리 사용되어 조명 환경을 감지하고 최적의 시청 및 절전을 위해 자동 디스플레이 밝기를 활성화합니다. TCS34725 자체는 광 감지 측정 사이에 저전력 대기 상태로 전환되어 평균 전력 소비를 더욱 줄일 수 있습니다.

LibDriver TCS34725는 LibDriver에서 출시한 TCS34725의 전체 기능 드라이버입니다. RGB 색상 판독, 밝기 판독, 밝기 인터럽트 감지 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver TCS34725의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver TCS34725용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver TCS34725드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver TCS34725프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver TCS34725오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 TCS34725데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인IIC 버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/tcs34725/index.html](https://www.libdriver.com/docs/tcs34725/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.