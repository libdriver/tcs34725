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
 * @file      driver_tcs34725_interrupt.h
 * @brief     driver tcs34725 interrupt header file
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

#ifndef DRIVER_TCS34725_INTERRUPT_H
#define DRIVER_TCS34725_INTERRUPT_H

#include "driver_tcs34725_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup tcs34725_example_driver
 * @{
 */

/**
 * @brief tcs34725 interrupt example default definition
 */
#define TCS34725_INTERRUPT_DEFAULT_WAIT                    TCS34725_BOOL_TRUE                    /**< enable wait */
#define TCS34725_INTERRUPT_DEFAULT_RGBC                    TCS34725_BOOL_TRUE                    /**< enable rgbc */
#define TCS34725_INTERRUPT_DEFAULT_INTEGRATION_TIME        TCS34725_INTEGRATION_TIME_50MS        /**< 50 ms integration time */
#define TCS34725_INTERRUPT_DEFAULT_WAIT_TIME               TCS34725_WAIT_TIME_2P4MS              /**< 2.4 ms wait time */
#define TCS34725_INTERRUPT_DEFAULT_GAIN                    TCS34725_GAIN_16X                     /**< 16x gain */
#define TCS34725_INTERRUPT_DEFAULT_POWER_ON                TCS34725_BOOL_TRUE                    /**< enable power on */

/**
 * @brief     interrupt example init
 * @param[in] mode is the interrupt mode
 * @param[in] low_threshold is the interrupt low threshold
 * @param[in] high_threshold is the interrupt high threshold
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t tcs34725_interrupt_init(tcs34725_interrupt_mode_t mode, uint16_t low_threshold, uint16_t high_threshold);

/**
 * @brief      interrupt example read
 * @param[out] *red points to a red color buffer
 * @param[out] *green points to a green color buffer
 * @param[out] *blue points to a blue color buffer
 * @param[out] *clear points to a clear color buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t tcs34725_interrupt_read(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear);

/**
 * @brief  interrupt example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tcs34725_interrupt_deinit(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
