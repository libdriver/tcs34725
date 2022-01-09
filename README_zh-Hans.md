[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md)

<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver TCS34725

[![API](https://img.shields.io/badge/api-reference-blue)](https://www.libdriver.com/docs/tcs34725/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TCS34725设备提供红色、绿色、蓝色（RGB）和亮度的光感应值。一个红外屏蔽过滤器和本地化的颜色传感光电二极管集成在芯片上，允许进行精确的颜色测量。高灵敏度，宽动态范围，红外光谱阻塞滤波器使TCS34725成为理想的颜色传感器解决方案。TCS34725颜色传感器有广泛的应用包括RGB LED背光控制，固态照明，健康/健身产品、工业过程控制和医疗诊断设备。此外，红外阻塞滤波器可以使TCS34725执行环境光感应（ALS）。环境光感应广泛应用于基于显示的产品，如用手机、笔记本和电视来感知光线环境并启用最佳观看效果和省电方案。TCS34725可以进行低功耗光感测量，进一步降低平均功耗。

LibDriver TCS34725是LibDriver推出的TCS34725全功能驱动，该驱动提供RGB颜色读取、亮度读取、亮度中断检测等功能。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver TCS34725的源文件。

/interface目录包含了LibDriver TCS34725与平台无关的IIC总线模板。

/test目录包含了LibDriver TCS34725驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver TCS34725编程范例。

/doc目录包含了LibDriver TCS34725离线文档。

/datasheet目录包含了TCS34725数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，/interface目录和/example目录加入工程。

### 使用

#### example basic

```C
uint8_t res;
uint8_t i;
uint16_t red, green, blue, clear;

res = tcs34725_basic_init();
if (res)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    tcs34725_interface_delay_ms(1000);
    res = tcs34725_basic_read((uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear);
    if (res)
    {
        tcs34725_basic_deinit();

        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: red is %d.\n", red);
    tcs34725_interface_debug_print("tcs34725: green is %d.\n", green);
    tcs34725_interface_debug_print("tcs34725: blue is %d.\n", blue);
    tcs34725_interface_debug_print("tcs34725: clear is %d.\n", clear);
    
    ...
    
}

...

tcs34725_basic_deinit();

return 0;
```

#### example interrupt

```C
uint8_t res;
uint8_t i;
uint16_t red, green, blue, clear;
uint8_t g_flag;

void gpio_irq(void)
{
    g_flag = 1;
}

res = tcs34725_interrupt_init(TCS34725_INTERRUPT_MODE_EVERY_RGBC_CYCLE, 10, 100);
if (res)
{
    return 1;
}
res = gpio_interrupt_init();
if (res)
{
    tcs34725_interrupt_deinit();

    return 1;
}

...

g_flag = 0;
for (i = 0; i < 3; i++)
{
    tcs34725_interface_delay_ms(1000);
    res = tcs34725_interrupt_read((uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear);
    if (res)
    {
        tcs34725_interface_debug_print("tcs34725: read data failed.\n");
        tcs34725_interrupt_deinit();
        gpio_interrupt_deinit();

        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: red is %d.\n", red);
    tcs34725_interface_debug_print("tcs34725: green is %d.\n", green);
    tcs34725_interface_debug_print("tcs34725: blue is %d.\n", blue);
    tcs34725_interface_debug_print("tcs34725: clear is %d.\n", clear);
    if (g_flag)
    {
        tcs34725_interface_debug_print("tcs34725: find interrupt.\n");

        break;
    }
    
    ...
    
}

...

tcs34725_interrupt_deinit();
gpio_interrupt_deinit();

return 0;
```

### 文档

在线文档: https://www.libdriver.com/docs/tcs34725/index.html

离线文档: /doc/html/index.html

### 贡献

请联系lishifenging@outlook.com

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com