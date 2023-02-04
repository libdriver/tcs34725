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
#include "gpio.h"
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
volatile uint8_t g_flag;            /**< interrupt flag */

/**
 * @brief     tcs34725 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t tcs34725(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"high-threshold", required_argument, NULL, 1},
        {"low-threshold", required_argument, NULL, 2},
        {"mode", required_argument, NULL, 3},
        {"times", required_argument, NULL, 4},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    tcs34725_interrupt_mode_t mode = TCS34725_INTERRUPT_MODE_EVERY_RGBC_CYCLE;
    uint16_t high_threshold = 100;
    uint16_t low_threshold = 10;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* high threshold */
            case 1 :
            {
                high_threshold = atoi(optarg);
                
                break;
            }
             
            /* low threshold */
            case 2 :
            {
                low_threshold = atoi(optarg);
                
                break;
            }
            
            /* mode */
            case 3 :
            {
                /* set the mode */
                if (strcmp("0", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_EVERY_RGBC_CYCLE;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_EVERY_RGBC_CYCLE.\n");
                }
                else if (strcmp("1", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_1_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_1_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("2", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_2_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_2_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("3", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_3_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_3_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("5", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_5_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_5_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("10", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_10_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_10_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("15", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_15_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_15_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("20", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_20_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_20_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("25", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_25_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_25_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("30", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_30_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_30_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("35", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_35_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_35_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("40", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_40_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_40_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("45", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_45_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_45_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("50", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_50_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_50_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("55", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_55_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_55_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else if (strcmp("60", optarg) == 0)
                {
                    mode = TCS34725_INTERRUPT_MODE_60_CLEAR_CHANNEL_OUT_OF_THRESHOLD;
                    tcs34725_interface_debug_print("tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_60_CLEAR_CHANNEL_OUT_OF_THRESHOLD.\n");
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* running times */
            case 4 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
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
    else if (strcmp("t_read", type) == 0)
    {
        if (tcs34725_read_test(times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_int", type) == 0)
    {
        uint8_t res;
        
        /* gpio init */
        res = gpio_interrupt_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* run interrupt test */
        res = tcs34725_interrupt_test(mode, low_threshold, high_threshold, times);
        if (res != 0)
        {
            (void)gpio_interrupt_deinit();
            
            return 1;
        }
        
        /* gpio deinit */
        (void)gpio_interrupt_deinit();
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        uint16_t red, green, blue, clear;
        
        /* basic init */
        res = tcs34725_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            tcs34725_interface_delay_ms(1000);
            
            /* read data */
            res = tcs34725_basic_read((uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear);
            if (res != 0)
            {
                (void)tcs34725_basic_deinit();
                
                return 1;
            }
            
            /* output */
            tcs34725_interface_debug_print("tcs34725: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            tcs34725_interface_debug_print("tcs34725: red is %d.\n", red);
            tcs34725_interface_debug_print("tcs34725: green is %d.\n", green);
            tcs34725_interface_debug_print("tcs34725: blue is %d.\n", blue);
            tcs34725_interface_debug_print("tcs34725: clear is %d.\n", clear);
        }
        
        /* basic deinit */
        (void)tcs34725_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_int", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        uint16_t red, green, blue, clear;
        
        /* interrupt init */
        res = tcs34725_interrupt_init(mode, low_threshold, high_threshold);
        if (res != 0)
        {
            return 1;
        }
        
        /* gpio init */
        res = gpio_interrupt_init();
        if (res != 0)
        {
            (void)tcs34725_interrupt_deinit();
            
            return 1;
        }
        
        /* loop */
        g_flag = 0;
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            tcs34725_interface_delay_ms(1000);
            
            /* read data */
            res = tcs34725_interrupt_read((uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear);
            if (res != 0)
            {
                tcs34725_interface_debug_print("tcs34725: read data failed.\n");
                (void)tcs34725_interrupt_deinit();
                (void)gpio_interrupt_deinit();
                
                return 1;
            }
            
            /* output */
            tcs34725_interface_debug_print("tcs34725: red is %d.\n", red);
            tcs34725_interface_debug_print("tcs34725: green is %d.\n", green);
            tcs34725_interface_debug_print("tcs34725: blue is %d.\n", blue);
            tcs34725_interface_debug_print("tcs34725: clear is %d.\n", clear);
            
            /* check the flag */
            if (g_flag != 0)
            {
                tcs34725_interface_debug_print("tcs34725: find interrupt.\n");
                
                break;
            }
        }
        
        /* deinit */
        (void)tcs34725_interrupt_deinit();
        (void)gpio_interrupt_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        tcs34725_interface_debug_print("Usage:\n");
        tcs34725_interface_debug_print("  tcs34725 (-i | --information)\n");
        tcs34725_interface_debug_print("  tcs34725 (-h | --help)\n");
        tcs34725_interface_debug_print("  tcs34725 (-p | --port)\n");
        tcs34725_interface_debug_print("  tcs34725 (-t reg | --test=reg)\n");
        tcs34725_interface_debug_print("  tcs34725 (-t read | --test=read) [--times=<num>]\n");
        tcs34725_interface_debug_print("  tcs34725 (-t int | --test=int) [--times=<num>]\n");
        tcs34725_interface_debug_print("           [--mode=<0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60>]\n");
        tcs34725_interface_debug_print("           [--low-threshold=<low>] [--high-threshold=<high>]\n");
        tcs34725_interface_debug_print("  tcs34725 (-e read | --example=read) [--times=<num>]\n");
        tcs34725_interface_debug_print("  tcs34725 (-e int | --example=int) [--times=<num>]\n");
        tcs34725_interface_debug_print("           [--mode=<0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60>]\n");
        tcs34725_interface_debug_print("           [--low-threshold=<low>] [--high-threshold=<high>]\n");
        tcs34725_interface_debug_print("\n");
        tcs34725_interface_debug_print("Options:\n");
        tcs34725_interface_debug_print("  -e <read | int>, --example=<read | int>\n");
        tcs34725_interface_debug_print("                                   Run the driver example.\n");
        tcs34725_interface_debug_print("  -h, --help                       Show the help.\n");
        tcs34725_interface_debug_print("      --high-threshold=<high>      Set the interrupt high threshold.([default: 100])\n");
        tcs34725_interface_debug_print("  -i, --information                Show the chip information.\n");
        tcs34725_interface_debug_print("      --low-threshold=<low>        Set the interrupt low threshold.([default: 10])\n");
        tcs34725_interface_debug_print("      --mode=<0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60> \n");
        tcs34725_interface_debug_print("                                   Set the interrupt mode.\n");
        tcs34725_interface_debug_print("  -p, --port                       Display the pin connections of the current board.\n");
        tcs34725_interface_debug_print("  -t <reg | read | int>, --test=<reg | read | int>\n");
        tcs34725_interface_debug_print("                                   Run the driver test.\n");
        tcs34725_interface_debug_print("      --times=<num>                Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        tcs34725_info_t info;
        
        /* print tcs34725 info */
        tcs34725_info(&info);
        tcs34725_interface_debug_print("tcs34725: chip is %s.\n", info.chip_name);
        tcs34725_interface_debug_print("tcs34725: manufacturer is %s.\n", info.manufacturer_name);
        tcs34725_interface_debug_print("tcs34725: interface is %s.\n", info.interface);
        tcs34725_interface_debug_print("tcs34725: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tcs34725_interface_debug_print("tcs34725: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tcs34725_interface_debug_print("tcs34725: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tcs34725_interface_debug_print("tcs34725: max current is %0.2fmA.\n", info.max_current_ma);
        tcs34725_interface_debug_print("tcs34725: max temperature is %0.1fC.\n", info.temperature_max);
        tcs34725_interface_debug_print("tcs34725: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        tcs34725_interface_debug_print("tcs34725: SCL connected to GPIO3(BCM).\n");
        tcs34725_interface_debug_print("tcs34725: SDA connected to GPIO2(BCM).\n");
        tcs34725_interface_debug_print("tcs34725: INT connected to GPIO17(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = tcs34725(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        tcs34725_interface_debug_print("tcs34725: run failed.\n");
    }
    else if (res == 5)
    {
        tcs34725_interface_debug_print("tcs34725: param is invalid.\n");
    }
    else
    {
        tcs34725_interface_debug_print("tcs34725: unknown status code.\n");
    }

    return 0;
}
