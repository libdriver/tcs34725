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
 * @file      driver_tcs34725_basic.c
 * @brief     driver tcs34725 basic source file
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

#include "driver_tcs34725_basic.h"

static tcs34725_handle_t gs_handle;        /**< tcs34725 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t tcs34725_basic_init(void)
{
    uint8_t res; 
    
    /* link interface function */
    DRIVER_TCS34725_LINK_INIT(&gs_handle, tcs34725_handle_t);
    DRIVER_TCS34725_LINK_IIC_INIT(&gs_handle, tcs34725_interface_iic_init);
    DRIVER_TCS34725_LINK_IIC_DEINIT(&gs_handle, tcs34725_interface_iic_deinit);
    DRIVER_TCS34725_LINK_IIC_READ(&gs_handle, tcs34725_interface_iic_read);
    DRIVER_TCS34725_LINK_IIC_WRITE(&gs_handle, tcs34725_interface_iic_write);
    DRIVER_TCS34725_LINK_DELAY_MS(&gs_handle, tcs34725_interface_delay_ms);
    DRIVER_TCS34725_LINK_DEBUG_PRINT(&gs_handle, tcs34725_interface_debug_print);
    
    /* tcs34725 init */
    res = tcs34725_init(&gs_handle);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: init failed.\n");
        
        return 1;
    }
    
    /* set rgbc interrupt */
    res = tcs34725_set_rgbc_interrupt(&gs_handle, TCS34725_BASIC_DEFAULT_RGBC_INTERRUPT);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc interrupt failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set wait */
    res = tcs34725_set_wait(&gs_handle, TCS34725_BASIC_DEFAULT_WAIT);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set wait failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rgbc */
    res = tcs34725_set_rgbc(&gs_handle, TCS34725_BASIC_DEFAULT_RGBC);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rgbc integration time */
    res = tcs34725_set_rgbc_integration_time(&gs_handle, TCS34725_BASIC_DEFAULT_INTEGRATION_TIME);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set wait time */
    res = tcs34725_set_wait_time(&gs_handle, TCS34725_BASIC_DEFAULT_WAIT_TIME);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rgbc clear low interrupt threshold */
    res = tcs34725_set_rgbc_clear_low_interrupt_threshold(&gs_handle, TCS34725_BASIC_DEFAULT_CLEAR_LOW_INTERRUPT_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc clear low interrupt threshold failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rgbc clear high interrupt threshold */
    res = tcs34725_set_rgbc_clear_high_interrupt_threshold(&gs_handle, TCS34725_BASIC_DEFAULT_CLEAR_HIGH_INTERRUPT_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc clear high interrupt threshold failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gain */
    res = tcs34725_set_gain(&gs_handle, TCS34725_BASIC_DEFAULT_GAIN);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set gain failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set interrupt mode */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_BASIC_DEFAULT_INTERRUPT_MODE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set power on */
    res = tcs34725_set_power_on(&gs_handle, TCS34725_BASIC_DEFAULT_POWER_ON);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set power on failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }  
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *red points to a red color buffer
 * @param[out] *green points to a green color buffer
 * @param[out] *blue points to a blue color buffer
 * @param[out] *clear points to a clear color buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t tcs34725_basic_read(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear)
{
    /* read data */
    if (tcs34725_read_rgbc(&gs_handle, red, green, blue, clear) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tcs34725_basic_deinit(void)
{
    /* tcs34725 deinit */
    if (tcs34725_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
