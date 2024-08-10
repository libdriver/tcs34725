[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TCS34725

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tcs34725/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The TCS34725 device provides a digital return of red, green, blue (RGB), and clear light sensing values. An IR blocking filter, integrated on-chip and localized to the color sensing photodiodes, minimizes the IR spectral component of the incoming light and allows color measurements to be made accurately. The high sensitivity, wide dynamic range, and IR blocking filter make the TCS34725 an ideal color sensor solution for use under varying lighting conditions and through attenuating materials. The TCS34725 color sensor has a wide range of applications including RGB LED backlight control, solid-state lighting, health/fitness products, industrial process controls and medical diagnostic equipment. In addition, the IR blocking filter enables the TCS34725 to perform ambient light sensing (ALS). Ambient light sensing is widely used in display-based products such as cell phones, notebooks, and TVs to sense the lighting environment and enable automatic display brightness for optimal viewing and power savings. The TCS34725, itself, can enter a lower-power wait state between light sensing measurements to further reduce the average power consumption.

LibDriver TCS34725 is a full function driver of TCS34725 launched by LibDriver.It provides RGB color reading, brightness reading, brightness interrupt detection and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver TCS34725 source files.

/interface includes LibDriver TCS34725 IIC platform independent template.

/test includes LibDriver TCS34725 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver TCS34725 sample code.

/doc includes LibDriver TCS34725 offline document.

/datasheet includes TCS34725 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

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

```C
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

### Document

Online documents: [https://www.libdriver.com/docs/tcs34725/index.html](https://www.libdriver.com/docs/tcs34725/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved 



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.