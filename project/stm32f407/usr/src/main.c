/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-02-28
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/28  <td>1.0      <td>Shifeng Li  <td>format the code
 * </table>
 */

#include "driver_tcs34725_interrupt_test.h"
#include "driver_tcs34725_read_test.h"
#include "driver_tcs34725_register_test.h"
#include "driver_tcs34725_interrupt.h"
#include "driver_tcs34725_basic.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "gpio.h"
#include "uart.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
uint16_t g_len;            /**< uart buffer length */
uint8_t g_flag;            /**< interrupt flag */

/**
  * @func   EXTI0_IRQHandler(void)
  * @brief  EXTI0 
  * @note   none
  */
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/**
  * @func   HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
  * @brief  gpio callback 
  * @param  gpio pin
  * @note   none
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_0)
    {
        g_flag = 1;
    }
}

/**
 * @brief     tcs34725 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t tcs34725(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            tcs34725_info_t info;
            
            /* print tcs34725 info */
            tcs34725_info(&info);
            tcs34725_interface_debug_print("tcs34725: chip is %s.\n", info.chip_name);
            tcs34725_interface_debug_print("tcs34725: manufacturer is %s.\n", info.manufacturer_name);
            tcs34725_interface_debug_print("tcs34725: interface is %s.\n", info.interface);
            tcs34725_interface_debug_print("tcs34725: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            tcs34725_interface_debug_print("tcs34725: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            tcs34725_interface_debug_print("tcs34725: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            tcs34725_interface_debug_print("tcs34725: max current is %0.2fmA.\n", info.max_current_ma);
            tcs34725_interface_debug_print("tcs34725: max temperature is %0.1fC.\n", info.temperature_max);
            tcs34725_interface_debug_print("tcs34725: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            tcs34725_interface_debug_print("tcs34725: SCL connected to GPIOB PIN8.\n");
            tcs34725_interface_debug_print("tcs34725: SDA connected to GPIOB PIN9.\n");
            tcs34725_interface_debug_print("tcs34725: INT connected to GPIOB PIN0.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show tcs34725 help */
            
            help:
            
            tcs34725_interface_debug_print("tcs34725 -i\n\tshow tcs34725 chip and driver information.\n");
            tcs34725_interface_debug_print("tcs34725 -h\n\tshow tcs34725 help.\n");
            tcs34725_interface_debug_print("tcs34725 -p\n\tshow tcs34725 pin connections of the current board.\n");
            tcs34725_interface_debug_print("tcs34725 -t reg\n\trun register test.\n");
            tcs34725_interface_debug_print("tcs34725 -t read <times>\n\trun read test.times means test times.\n");
            tcs34725_interface_debug_print("tcs34725 -t int <times> -m (0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60) -th <lowthreshold> <highthreshold>\n\t");
            tcs34725_interface_debug_print("run interrupt test.times means test times.lowthreshold means interrupt low threshold.highthreshold means interrupt high threshold.\n");
            tcs34725_interface_debug_print("tcs34725 -c read <times>\n\trun read function.times means read times.\n");
            tcs34725_interface_debug_print("tcs34725 -c int <times> -m (0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60) -th <lowthreshold> <highthreshold>\n\t");
            tcs34725_interface_debug_print("run interrupt function.times means read times.lowthreshold means interrupt low threshold.highthreshold means interrupt high threshold.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 3)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                /* run reg test */
                if (tcs34725_register_test() != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                if (tcs34725_read_test(atoi(argv[3])) != 0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
             /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t i;
                uint32_t times;
                uint16_t red, green, blue, clear;

                res = tcs34725_basic_init();
                if (res != 0)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i = 0; i < times; i++)
                {
                    tcs34725_interface_delay_ms(1000);
                    res = tcs34725_basic_read((uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear);
                    if (res != 0)
                    {
                        (void)tcs34725_basic_deinit();
                        
                        return 1;
                    }
                    tcs34725_interface_debug_print("tcs34725: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    tcs34725_interface_debug_print("tcs34725: red is %d.\n", red);
                    tcs34725_interface_debug_print("tcs34725: green is %d.\n", green);
                    tcs34725_interface_debug_print("tcs34725: blue is %d.\n", blue);
                    tcs34725_interface_debug_print("tcs34725: clear is %d.\n", clear);
                }
                (void)tcs34725_basic_deinit();
                
                return 0;
            }

            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 9)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("int", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t times;
                tcs34725_interrupt_mode_t mode;
                
                /* check interrupt mode */
                if (strcmp("-m", argv[4]) != 0)
                {
                    return 5;
                }

                /* check threshold mode */
                if (strcmp("-th", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_EVERY_RGBC_CYCLE;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_EVERY_RGBC_CYCLE.\n");
                }
                else if (strcmp("1", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_1_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_1_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("2", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_2_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_2_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("3", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_3_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_3_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("5", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_5_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_5_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("10", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_10_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_10_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("15", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_15_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_15_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("20", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_20_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_20_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("25", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_25_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_25_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("30", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_30_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_30_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("35", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_35_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_35_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("40", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_40_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_40_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("45", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_45_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_45_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("50", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_50_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_50_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("55", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_55_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_55_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("60", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_60_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_60_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else
                {
                    return 5;
                }

                /* check threshold */
                if (strcmp("-th", argv[6]) != 0)
                {
                    return 5;
                }
                times = atoi(argv[3]);
                res = gpio_interrupt_init();
                if (res != 0)
                {
                    return 1;
                }
                res = tcs34725_interrupt_test(mode, (uint16_t)atoi(argv[7]), (uint16_t)atoi(argv[8]), times);
                if (res != 0)
                {
                    (void)gpio_interrupt_deinit();
                    
                    return 1;
                }
                (void)gpio_interrupt_deinit();
                
                return 0;
            }

            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
             /* read function */
            if (strcmp("int", argv[2]) == 0)
            {
                uint8_t res;
                uint32_t i;
                uint32_t times;
                uint16_t red, green, blue, clear;
                tcs34725_interrupt_mode_t mode;
                
                /* check interrupt mode */
                if (strcmp("-m", argv[4]) != 0)
                {
                    return 5;
                }

                /* check threshold mode */
                if (strcmp("-th", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_EVERY_RGBC_CYCLE;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_EVERY_RGBC_CYCLE.\n");
                }
                else if (strcmp("1", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_1_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_1_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("2", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_2_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_2_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("3", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_3_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_3_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("5", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_5_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_5_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("10", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_10_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_10_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("15", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_15_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_15_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("20", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_20_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_20_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("25", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_25_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_25_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("30", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_30_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_30_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("35", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_35_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_35_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("40", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_40_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_40_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("45", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_45_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_45_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("50", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_50_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_50_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("55", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_55_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_55_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("60", argv[5]) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_60_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_60_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else
                {
                    return 5;
                }

                /* check threshold */
                if (strcmp("-th", argv[6]) != 0)
                {
                    return 5;
                }
                times = atoi(argv[3]);
                res = tcs34725_interrupt_init(mode, (uint16_t)atoi(argv[7]), (uint16_t)atoi(argv[8]));
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
                g_flag = 0;
                for (i = 0; i < times; i++)
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
                }
                (void)tcs34725_interrupt_deinit();
                (void)gpio_interrupt_deinit();
                
                return 0;
            }

            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* param is invalid */
        else
        {
            return 5;
        }
    }

    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register tcs34725 fuction */
    shell_init();
    shell_register("tcs34725", tcs34725);
    uart1_print("tcs34725: welcome to libdriver tcs34725.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("tcs34725: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("tcs34725: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("tcs34725: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("tcs34725: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("tcs34725: param is invalid.\n");
            }
            else
            {
                uart1_print("tcs34725: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
