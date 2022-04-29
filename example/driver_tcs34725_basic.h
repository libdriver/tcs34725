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
 * @file      driver_tcs34725_basic.h
 * @brief     driver tcs34725 basic header file
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

#ifndef DRIVER_TCS34725_BASIC_H
#define DRIVER_TCS34725_BASIC_H

#include "driver_tcs34725_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup tcs34725_example_driver tcs34725 example driver function
 * @brief    tcs34725 example driver modules
 * @ingroup  tcs34725_driver
 * @{
 */

/**
 * @brief tcs34725 basic example default definition
 */
#define TCS34725_BASIC_DEFAULT_RGBC_INTERRUPT                        TCS34725_BOOL_FALSE                                       /**< disable interrupt */
#define TCS34725_BASIC_DEFAULT_WAIT                                  TCS34725_BOOL_TRUE                                        /**< enable wait */
#define TCS34725_BASIC_DEFAULT_RGBC                                  TCS34725_BOOL_TRUE                                        /**< enable rgbc */
#define TCS34725_BASIC_DEFAULT_INTEGRATION_TIME                      TCS34725_INTEGRATION_TIME_50MS                            /**< 50 ms integration time */
#define TCS34725_BASIC_DEFAULT_WAIT_TIME                             TCS34725_WAIT_TIME_2P4MS                                  /**< 2.4 ms wait time */
#define TCS34725_BASIC_DEFAULT_CLEAR_LOW_INTERRUPT_THRESHOLD         0x0000U                                                   /**< 0x0000 low interrupt threshold */
#define TCS34725_BASIC_DEFAULT_CLEAR_HIGH_INTERRUPT_THRESHOLD        0xFFFFU                                                   /**< 0xFFFF high interrupt threshold */
#define TCS34725_BASIC_DEFAULT_GAIN                                  TCS34725_GAIN_16X                                         /**< 16x gain */
#define TCS34725_BASIC_DEFAULT_INTERRUPT_MODE                        TCS34725_INTERRUPT_MODE_1_CLEAR_CHANNEL_OUT_OF_THRESHOLD  /**< 1 clear out of threshold */
#define TCS34725_BASIC_DEFAULT_POWER_ON                              TCS34725_BOOL_TRUE                                        /**< enable power on */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t tcs34725_basic_init(void);

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
uint8_t tcs34725_basic_read(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tcs34725_basic_deinit(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
