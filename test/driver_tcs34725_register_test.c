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
 * @file      driver_tcs34725_register_test.c
 * @brief     driver tcs34725 register test source file
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
 
#include "driver_tcs34725_register_test.h"
#include <stdlib.h>

static tcs34725_handle_t gs_handle;        /**< tcs34725 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t tcs34725_register_test(void)
{
    uint8_t res;
    uint16_t reg_in, reg_out;
    tcs34725_info_t info;  
    tcs34725_bool_t enable;
    tcs34725_integration_time_t t;
    tcs34725_wait_time_t wait_time;
    tcs34725_gain_t gain;
    tcs34725_interrupt_mode_t mode;
    
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
    
    /* start register */
    tcs34725_interface_debug_print("tcs34725: start register test.\n");
    
    /* tcs34725_set_rgbc_interrupt/tcs34725_get_rgbc_interrupt test */
    tcs34725_interface_debug_print("tcs34725: tcs34725_set_rgbc_interrupt/tcs34725_get_rgbc_interrupt test.\n");
    
    /* enable interrupt */
    res = tcs34725_set_rgbc_interrupt(&gs_handle, TCS34725_BOOL_TRUE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc interrupt failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set rgbc interrupt enable.\n");
    res = tcs34725_get_rgbc_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get rgbc interrupt failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check rgbc interrupt %s.\n", enable==TCS34725_BOOL_TRUE?"ok":"error");       
    
    /* disable interrupt */
    res = tcs34725_set_rgbc_interrupt(&gs_handle, TCS34725_BOOL_FALSE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc interrupt failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set rgbc interrupt disable.\n");
    res = tcs34725_get_rgbc_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get rgbc interrupt failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check rgbc interrupt %s.\n", enable==TCS34725_BOOL_FALSE?"ok":"error");       
    
    /* tcs34725_set_wait/tcs34725_get_wait test */
    tcs34725_interface_debug_print("tcs34725: tcs34725_set_wait/tcs34725_get_wait test.\n");
    
    /* enable wait */
    res = tcs34725_set_wait(&gs_handle, TCS34725_BOOL_TRUE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set wait failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set wait enable.\n");
    res = tcs34725_get_wait(&gs_handle, &enable);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get wait failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check wait %s.\n", enable==TCS34725_BOOL_TRUE?"ok":"error");   
    
    /* disable wait */
    res = tcs34725_set_wait(&gs_handle, TCS34725_BOOL_FALSE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set wait failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set wait disable.\n");
    res = tcs34725_get_wait(&gs_handle, &enable);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get wait failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check wait %s.\n", enable==TCS34725_BOOL_FALSE?"ok":"error");   
    
    /* tcs34725_set_rgbc/tcs34725_get_rgbc test */
    tcs34725_interface_debug_print("tcs34725: tcs34725_set_rgbc/tcs34725_get_rgbc test.\n");
    
    /* enable rgbc */
    res = tcs34725_set_rgbc(&gs_handle, TCS34725_BOOL_TRUE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set rgbc enable.\n");
    res = tcs34725_get_rgbc(&gs_handle, &enable);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get rgbc failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check rgbc %s.\n", enable==TCS34725_BOOL_TRUE?"ok":"error");       
    
    /* disable rgbc */
    res = tcs34725_set_rgbc(&gs_handle, TCS34725_BOOL_FALSE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set rgbc disable.\n");
    res = tcs34725_get_rgbc(&gs_handle, &enable);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get rgbc failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check rgbc %s.\n", enable==TCS34725_BOOL_FALSE?"ok":"error");          
    
    /* tcs34725_set_power_on/tcs34725_get_power_on test */
    tcs34725_interface_debug_print("tcs34725: tcs34725_set_power_on/tcs34725_get_power_on test.\n");
    
    /* enable power on */
    res = tcs34725_set_power_on(&gs_handle, TCS34725_BOOL_TRUE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set power on failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set power on enable.\n");
    res = tcs34725_get_power_on(&gs_handle, &enable);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get power on failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check power on %s.\n", enable==TCS34725_BOOL_TRUE?"ok":"error");           
    
    /* disable power on */
    res = tcs34725_set_power_on(&gs_handle, TCS34725_BOOL_FALSE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set power on failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set power on disable.\n");
    res = tcs34725_get_power_on(&gs_handle, &enable);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get power on failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check power on %s.\n", enable==TCS34725_BOOL_FALSE?"ok":"error"); 
    
    /* tcs34725_set_rgbc_integration_time/tcs34725_get_rgbc_integration_time test */
    tcs34725_interface_debug_print("tcs34725: tcs34725_set_rgbc_integration_time/tcs34725_get_rgbc_integration_time test.\n");
    
    /* set integration time 2.4ms */
    res = tcs34725_set_rgbc_integration_time(&gs_handle, TCS34725_INTEGRATION_TIME_2P4MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set rgbc integration time 2.4ms.\n");
    res = tcs34725_get_rgbc_integration_time(&gs_handle, &t);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check rgbc integration time %s.\n", t==TCS34725_INTEGRATION_TIME_2P4MS?"ok":"error"); 
    
    /* set integration time 24ms */
    res = tcs34725_set_rgbc_integration_time(&gs_handle, TCS34725_INTEGRATION_TIME_24MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set integration time 24ms */
    tcs34725_interface_debug_print("tcs34725: set rgbc integration time 24ms.\n");
    res = tcs34725_get_rgbc_integration_time(&gs_handle, &t);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check rgbc integration time %s.\n", t==TCS34725_INTEGRATION_TIME_24MS?"ok":"error"); 
    
    /* set integration time 50ms */
    res = tcs34725_set_rgbc_integration_time(&gs_handle, TCS34725_INTEGRATION_TIME_50MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set rgbc integration time 50ms.\n");
    res = tcs34725_get_rgbc_integration_time(&gs_handle, &t);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check rgbc integration time %s.\n", t==TCS34725_INTEGRATION_TIME_50MS?"ok":"error");     
    
    /* set integration time 101ms */
    res = tcs34725_set_rgbc_integration_time(&gs_handle, TCS34725_INTEGRATION_TIME_101MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set rgbc integration time 101ms.\n");
    res = tcs34725_get_rgbc_integration_time(&gs_handle, &t);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check rgbc integration time %s.\n", t==TCS34725_INTEGRATION_TIME_101MS?"ok":"error");       
    
    /* set integration time 154ms */
    res = tcs34725_set_rgbc_integration_time(&gs_handle, TCS34725_INTEGRATION_TIME_154MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set rgbc integration time 154ms.\n");
    res = tcs34725_get_rgbc_integration_time(&gs_handle, &t);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check rgbc integration time %s.\n", t==TCS34725_INTEGRATION_TIME_154MS?"ok":"error");      
    
    /* set integration time 700ms */
    res = tcs34725_set_rgbc_integration_time(&gs_handle, TCS34725_INTEGRATION_TIME_700MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set rgbc integration time 700ms.\n");
    res = tcs34725_get_rgbc_integration_time(&gs_handle, &t);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get rgbc integration time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check rgbc integration time %s.\n", t==TCS34725_INTEGRATION_TIME_700MS?"ok":"error");           
    
    /* tcs34725_set_wait_time/tcs34725_get_wait_time test */
    tcs34725_interface_debug_print("tcs34725: tcs34725_set_wait_time/tcs34725_get_wait_time test.\n");
    
    /* set wait time 2.4ms */
    res = tcs34725_set_wait_time(&gs_handle, TCS34725_WAIT_TIME_2P4MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set wait time 2.4ms.\n");
    res = tcs34725_get_wait_time(&gs_handle, &wait_time);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check wait time %s.\n", wait_time==TCS34725_WAIT_TIME_2P4MS?"ok":"error"); 
    
    /* set wait time 204ms */
    res = tcs34725_set_wait_time(&gs_handle, TCS34725_WAIT_TIME_204MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set wait time 204ms.\n");
    res = tcs34725_get_wait_time(&gs_handle, &wait_time);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check wait time %s.\n", wait_time==TCS34725_WAIT_TIME_204MS?"ok":"error");
    
    /* set wait time 614ms */
    res = tcs34725_set_wait_time(&gs_handle, TCS34725_WAIT_TIME_614MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set wait time 614ms.\n");
    res = tcs34725_get_wait_time(&gs_handle, &wait_time);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check wait time %s.\n", wait_time==TCS34725_WAIT_TIME_614MS?"ok":"error");       
    
    /* set wait time 29ms */
    res = tcs34725_set_wait_time(&gs_handle, TCS34725_WAIT_TIME_29MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set wait time 29ms.\n");
    res = tcs34725_get_wait_time(&gs_handle, &wait_time);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check wait time %s.\n", wait_time==TCS34725_WAIT_TIME_29MS?"ok":"error");       
    
    /* set wait time 2450ms */
    res = tcs34725_set_wait_time(&gs_handle, TCS34725_WAIT_TIME_2450MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set wait time 2450ms.\n");
    res = tcs34725_get_wait_time(&gs_handle, &wait_time);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check wait time %s.\n", wait_time==TCS34725_WAIT_TIME_2450MS?"ok":"error");   
    
    /* set wait time 7400ms */
    res = tcs34725_set_wait_time(&gs_handle, TCS34725_WAIT_TIME_7400MS);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set wait time 7400ms.\n");
    res = tcs34725_get_wait_time(&gs_handle, &wait_time);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get wait time failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check wait time %s.\n", wait_time==TCS34725_WAIT_TIME_7400MS?"ok":"error");
    
    /* tcs34725_set_rgbc_clear_low_interrupt_threshold/tcs34725_get_rgbc_clear_low_interrupt_threshold test */
    tcs34725_interface_debug_print("tcs34725: tcs34725_set_rgbc_clear_low_interrupt_threshold/tcs34725_get_rgbc_clear_low_interrupt_threshold test.\n");
    reg_in = rand()%65535;
    res = tcs34725_set_rgbc_clear_low_interrupt_threshold(&gs_handle, reg_in);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc clear low interrupt threshold failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set rgbc clear low interrupt threshold 0x%04X.\n", reg_in);
    res = tcs34725_get_rgbc_clear_low_interrupt_threshold(&gs_handle, (uint16_t *)&reg_out);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get rgbc clear low interrupt threshold  failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check rgbc clear low interrupt threshold %s.\n", reg_in==reg_out?"ok":"error");  
    
    /* tcs34725_set_rgbc_clear_high_interrupt_threshold/tcs34725_get_rgbc_clear_high_interrupt_threshold test */
    tcs34725_interface_debug_print("tcs34725: tcs34725_set_rgbc_clear_high_interrupt_threshold/tcs34725_get_rgbc_clear_high_interrupt_threshold test.\n");
    reg_in = rand()%65535;
    res = tcs34725_set_rgbc_clear_high_interrupt_threshold(&gs_handle, reg_in);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set rgbc clear high interrupt threshold failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set rgbc clear high interrupt threshold 0x%04X.\n", reg_in);
    res = tcs34725_get_rgbc_clear_high_interrupt_threshold(&gs_handle, (uint16_t *)&reg_out);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get rgbc clear high interrupt threshold  failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check rgbc clear high interrupt threshold %s.\n", reg_in==reg_out?"ok":"error");   
    
    /* tcs34725_set_gain/tcs34725_get_gain test */
    tcs34725_interface_debug_print("tcs34725: tcs34725_set_gain/tcs34725_get_gain test.\n");
    
    /* set gain 1x */
    res = tcs34725_set_gain(&gs_handle, TCS34725_GAIN_1X);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set gain failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set gain 1x.\n");
    res = tcs34725_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get gain failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check gain %s.\n", gain==TCS34725_GAIN_1X?"ok":"error");     
    
    /* set gain 4x */
    res = tcs34725_set_gain(&gs_handle, TCS34725_GAIN_4X);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set gain failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set gain 4x.\n");
    res = tcs34725_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get gain failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check gain %s.\n", gain==TCS34725_GAIN_4X?"ok":"error");      
    
    /* set gain 16x */
    res = tcs34725_set_gain(&gs_handle, TCS34725_GAIN_16X);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set gain failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set gain 16x.\n");
    res = tcs34725_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get gain failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check gain %s.\n", gain==TCS34725_GAIN_16X?"ok":"error");     
    
    /* set gain 60x */
    res = tcs34725_set_gain(&gs_handle, TCS34725_GAIN_60X);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set gain failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set gain 60x.\n");
    res = tcs34725_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get gain failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check gain %s.\n", gain==TCS34725_GAIN_60X?"ok":"error");  
    
    /* tcs34725_set_interrupt_mode/tcs34725_get_interrupt_mode test */
    tcs34725_interface_debug_print("tcs34725: tcs34725_set_interrupt_mode/tcs34725_get_interrupt_mode test.\n");
    
    /* set interrupt mode every rgbc cycle */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_EVERY_RGBC_CYCLE);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode every rgbc cycle.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_EVERY_RGBC_CYCLE?"ok":"error"); 
    
    /* set interrupt mode 1 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_1_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 1 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_1_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");     
    
    /* set interrupt mode 2 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_2_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 2 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_2_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");         
    
    /* set interrupt mode 3 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_3_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 3 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_3_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");     
    
    /* set interrupt mode 5 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_5_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 5 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_5_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");      
    
    /* set interrupt mode 10 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_10_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 10 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_10_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");    
    
    /* set interrupt mode 15 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_15_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 15 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_15_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");        
    
    /* set interrupt mode 20 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_20_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 20 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_20_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");        
    
    /* set interrupt mode 25 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_25_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 25 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_25_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");         
    
    /* set interrupt mode 30 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_30_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 30 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_30_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");       
    
    /* set interrupt mode 35 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_35_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 35 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_35_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");
    
    /* set interrupt mode 40 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_40_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 40 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_40_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");
    
    /* set interrupt mode 45 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_45_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 45 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_45_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");
    
    /* set interrupt mode 50 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_50_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 50 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_50_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");
    
    /* set interrupt mode 55 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_55_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 55 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_55_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");
    
    /* set interrupt mode 60 clear out of threshold */
    res = tcs34725_set_interrupt_mode(&gs_handle, TCS34725_INTERRUPT_MODE_60_CLEAR_CHANNEL_OUT_OF_THRESHOLD);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: set interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: set interrupt mode 60 clear out of threshold.\n");
    res = tcs34725_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tcs34725_interface_debug_print("tcs34725: get interrupt mode failed.\n");
        (void)tcs34725_deinit(&gs_handle);
        
        return 1;
    }
    tcs34725_interface_debug_print("tcs34725: check interrupt mode %s.\n", mode==TCS34725_INTERRUPT_MODE_60_CLEAR_CHANNEL_OUT_OF_THRESHOLD?"ok":"error");
    
    /* finish register test */
    tcs34725_interface_debug_print("tcs34725: finish register test.\n");
    (void)tcs34725_deinit(&gs_handle);
    
    return 0;
}
