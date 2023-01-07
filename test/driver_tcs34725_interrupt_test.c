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
 * @file      driver_tcs34725_interrupt_test.c
 * @brief     driver tcs34725 interrupt test source file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-02-28
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/28  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/10/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_tcs34725_interrupt_test.h"

static tcs34725_handle_t gs_handle;        /**< tcs34725 handle */

/**
 * @brief     interrupt test
 * @param[in] mode is the interrupt mode
 * @param[in] clear_low_threshold is the clear channel low threshold
 * @param[in] clear_high_threshold is the clear channel high threshold
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t tcs34725_interrupt_test(tcs34725_interrupt_mode_t mode, uint16_t clear_low_threshold, uint16_t clear_high_threshold, uint32_t times)
{
    uint8_t res;
    tcs34725_info_t info;  
    
     /* link interface function */
    DRIVER_TCS34725_LINK_INIT(&gs_handle, tcs34725_handle_t);
    DRIVER_TCS34725_LINK_IIC_INIT(&gs_handle, tcs34725_interface_iic_init);
    DRIVER_TCS34725_LINK_IIC_DEINIT(&gs_handle, tcs34725_interface_iic_deinit);
    DRIVER_TCS34725_LINK_IIC_READ(&gs_handle, tcs34725_interface_iic_read);
    DRIVER_TCS34725_LINK_IIC_WRITE(&gs_handle, tcs34725_interface_iic_write);
    DRIVER_TCS34725_LINK_DELAY_MS(&gs_handle, tcs34725_interface_delay_ms);
    DRIVER_TCS34725_LINK_DEBUG_PRINT(&gs_handle, tcs34725_interface_debug_print);
    
    /* get chip information */
    res = tcs34725_info(&info);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        tcs34725_interface_debug_print("tcs34725: chip is %s.\n", info.chip_name);
        tcs34725_interface_debug_print("tcs34725: manufacturer is %s.\n", info.manufacturer_name);
        tcs34725_interface_debug_print("tcs34725: interface is %s.\n", info.interface);
        tcs34725_interface_debug_print("tcs34725: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tcs34725_interface_debug_print("tcs34725: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tcs34725_interface_debug_print("tcs34725: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tcs34725_interface_debug_print("tcs34725: max current is %0.2fmA.\n", info.max_current_ma);
        tcs34725_interface_debug_print("tcs34725: max temperature is %0.1fC.\n", info.temperature_max);
        tcs34725_interface_debug_print("tcs34725: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* tcs34725 init */
    res = tcs34725_init(&gs_handle);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: init failed.\n");
       
        return 1;
    }
    
    /* start interrupt test */
    tcs34725_interface_debug_print("tcs34725: start interrupt test.\n");   
    
    /* enable rgbc interrupt */
    res = tcs34725_set_rgbc_interrupt(&gs_handle, TCS34725_BOOL_TRUE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc interrupt failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable wait */
    res = tcs34725_set_wait(&gs_handle, TCS34725_BOOL_TRUE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set wait failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable rgbc */
    res = tcs34725_set_rgbc(&gs_handle, TCS34725_BOOL_TRUE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rgbc integration time 50 ms */
    res = tcs34725_set_rgbc_integration_time(&gs_handle, TCS34725_INTEGRATION_TIME_50MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set wait time 2.4 ms */
    res = tcs34725_set_wait_time(&gs_handle, TCS34725_WAIT_TIME_2P4MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set clear low interrupt threshold */
    res = tcs34725_set_rgbc_clear_low_interrupt_threshold(&gs_handle, clear_low_threshold);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc clear low interrupt threshold failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set clear high interrupt threshold */
    res = tcs34725_set_rgbc_clear_high_interrupt_threshold(&gs_handle, clear_high_threshold);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc clear high interrupt threshold failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gain 16x */
    res = tcs34725_set_gain(&gs_handle, TCS34725_GAIN_16X);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set gain failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set interrupt mode */
    res = tcs34725_set_interrupt_mode(&gs_handle, mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable power on */
    res = tcs34725_set_power_on(&gs_handle, TCS34725_BOOL_TRUE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set power on failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 1000 ms */
    tcs34725_interface_delay_ms(1000);
    while (times != 0)
    {
        uint16_t red, green, blue, clear;
        
        /* read rgbc data */
        if (tcs34725_read_rgbc(&gs_handle, (uint16_t *)&red, (uint16_t *)&green, (uint16_t *)&blue, (uint16_t *)&clear) != 0)
        {
            tcs34725_interface_debug_print("tcs34725: read rgbc failed.\n");
            (void)tcs34725_deinit(&gs_handle);
            
            return 1;
        }
        tcs34725_interface_debug_print("tcs34725: clear is %d and check high interrupt %s.\n", clear, clear>clear_high_threshold?"high threshold":"none");
        tcs34725_interface_debug_print("tcs34725: clear is %d and check low interrupt %s.\n", clear, clear<clear_low_threshold?"low threshold":"none");
        times--;
        tcs34725_interface_delay_ms(1000);
    }
    
    /* finish interrupt test */
    tcs34725_interface_debug_print("tcs34725: finish interrupt test.\n");
    (void)tcs34725_deinit(&gs_handle);
    
    return 0;
}
