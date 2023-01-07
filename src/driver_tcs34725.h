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
 * @file      driver_tcs34725.h
 * @brief     driver tcs34725 header file
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

#ifndef DRIVER_TCS34725_H
#define DRIVER_TCS34725_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup tcs34725_driver tcs34725 driver function
 * @brief    tcs34725 driver modules
 * @{
 */

/**
 * @addtogroup tcs34725_base_driver
 * @{
 */

/**
 * @brief tcs34725 bool enumeration definition
 */
typedef enum
{
    TCS34725_BOOL_FALSE = 0x00,        /**< disable function */
    TCS34725_BOOL_TRUE  = 0x01,        /**< enable function */
} tcs34725_bool_t;

/**
 * @brief tcs34725 integration time enumeration definition
 */
typedef enum
{
    TCS34725_INTEGRATION_TIME_2P4MS = 0xFF,        /**< integration time 2.4 ms */
    TCS34725_INTEGRATION_TIME_24MS  = 0xF6,        /**< integration time 24 ms */
    TCS34725_INTEGRATION_TIME_50MS  = 0xEB,        /**< integration time 50 ms */
    TCS34725_INTEGRATION_TIME_101MS = 0xD5,        /**< integration time 101 ms */
    TCS34725_INTEGRATION_TIME_154MS = 0xC0,        /**< integration time 154 ms */
    TCS34725_INTEGRATION_TIME_700MS = 0x00,        /**< integration time 700 ms */
} tcs34725_integration_time_t;

/**
 * @brief tcs34725 gain enumeration definition
 */
typedef enum
{
    TCS34725_GAIN_1X  = 0x00,        /**< 1x gain */
    TCS34725_GAIN_4X  = 0x01,        /**< 4x gain */
    TCS34725_GAIN_16X = 0x02,        /**< 16x gain */
    TCS34725_GAIN_60X = 0x03,        /**< 60x gain */
} tcs34725_gain_t;    

/**
 * @brief tcs34725 wait time enumeration definition
 */
typedef enum
{
    TCS34725_WAIT_TIME_2P4MS  = 0x0FF,        /**< 2.4 ms wait time */
    TCS34725_WAIT_TIME_204MS  = 0x0AB,        /**< 204 ms wait time */
    TCS34725_WAIT_TIME_614MS  = 0x000,        /**< 614 ms wait time */
    TCS34725_WAIT_TIME_29MS   = 0x1FF,        /**< 29 ms wait time */
    TCS34725_WAIT_TIME_2450MS = 0x1AB,        /**< 2450 ms wait time */
    TCS34725_WAIT_TIME_7400MS = 0x100,        /**< 7400 ms wait time */
} tcs34725_wait_time_t;

/**
 * @}
 */

/**
 * @addtogroup tcs34725_interrupt_driver
 * @{
 */

/**
 * @brief tcs34725 interrupt mode enumeration definition
 */
typedef enum  
{
    TCS34725_INTERRUPT_MODE_EVERY_RGBC_CYCLE                  = 0x00,        /**< every rgbc cycle interrupt */
    TCS34725_INTERRUPT_MODE_1_CLEAR_CHANNEL_OUT_OF_THRESHOLD  = 0x01,        /**< 1 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_2_CLEAR_CHANNEL_OUT_OF_THRESHOLD  = 0x02,        /**< 2 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_3_CLEAR_CHANNEL_OUT_OF_THRESHOLD  = 0x03,        /**< 3 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_5_CLEAR_CHANNEL_OUT_OF_THRESHOLD  = 0x04,        /**< 5 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_10_CLEAR_CHANNEL_OUT_OF_THRESHOLD = 0x05,        /**< 10 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_15_CLEAR_CHANNEL_OUT_OF_THRESHOLD = 0x06,        /**< 15 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_20_CLEAR_CHANNEL_OUT_OF_THRESHOLD = 0x07,        /**< 20 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_25_CLEAR_CHANNEL_OUT_OF_THRESHOLD = 0x08,        /**< 25 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_30_CLEAR_CHANNEL_OUT_OF_THRESHOLD = 0x09,        /**< 30 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_35_CLEAR_CHANNEL_OUT_OF_THRESHOLD = 0x0A,        /**< 35 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_40_CLEAR_CHANNEL_OUT_OF_THRESHOLD = 0x0B,        /**< 40 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_45_CLEAR_CHANNEL_OUT_OF_THRESHOLD = 0x0C,        /**< 45 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_50_CLEAR_CHANNEL_OUT_OF_THRESHOLD = 0x0D,        /**< 50 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_55_CLEAR_CHANNEL_OUT_OF_THRESHOLD = 0x0E,        /**< 55 cycle out of threshold interrupt */
    TCS34725_INTERRUPT_MODE_60_CLEAR_CHANNEL_OUT_OF_THRESHOLD = 0x0F,        /**< 60 cycle out of threshold interrupt */
} tcs34725_interrupt_mode_t;

/**
 * @}
 */

/**
 * @addtogroup tcs34725_base_driver
 * @{
 */

/**
 * @brief tcs34725 handle structure definition
 */
typedef struct tcs34725_handle_s
{
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t  inited;                                                                    /**< inited flag */
} tcs34725_handle_t;

/**
 * @brief tcs34725 information structure definition
 */
typedef struct tcs34725_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} tcs34725_info_t;

/**
 * @}
 */

/**
 * @defgroup tcs34725_link_driver tcs34725 link driver function
 * @brief    tcs34725 link driver modules
 * @ingroup  tcs34725_driver
 * @{
 */

/**
 * @brief     initialize tcs34725_handle_t structure
 * @param[in] HANDLE points to a tcs34725 handle structure
 * @param[in] STRUCTURE is tcs34725_handle_t
 * @note      none
 */
#define DRIVER_TCS34725_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to a tcs34725 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_TCS34725_LINK_IIC_INIT(HANDLE, FUC)    (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to a tcs34725 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_TCS34725_LINK_IIC_DEINIT(HANDLE, FUC)  (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to a tcs34725 handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_TCS34725_LINK_IIC_READ(HANDLE, FUC)    (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to a tcs34725 handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_TCS34725_LINK_IIC_WRITE(HANDLE, FUC)   (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a tcs34725 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_TCS34725_LINK_DELAY_MS(HANDLE, FUC)    (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a tcs34725 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_TCS34725_LINK_DEBUG_PRINT(HANDLE, FUC) (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup tcs34725_base_driver tcs34725 base driver function
 * @brief    tcs34725 base driver modules
 * @ingroup  tcs34725_driver
 * @{
 */

/**
 * @brief      get chip information
 * @param[out] *info points to a tcs34725 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tcs34725_info(tcs34725_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a tcs34725 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t tcs34725_init(tcs34725_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a tcs34725 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tcs34725_deinit(tcs34725_handle_t *handle);

/**
 * @brief      read the rgbc data
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *red points to a red color buffer
 * @param[out] *green points to a green color buffer
 * @param[out] *blue points to a blue color buffer
 * @param[out] *clear points to a clear color buffer
 * @return     status code
 *             - 0 success
 *             - 1 read rgbc failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_read_rgbc(tcs34725_handle_t *handle, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear);

/**
 * @brief      read the rgb data
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *red points to a red color buffer
 * @param[out] *green points to a green color buffer
 * @param[out] *blue points to a blue color buffer
 * @return     status code
 *             - 0 success
 *             - 1 read rgb failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_read_rgb(tcs34725_handle_t *handle, uint16_t *red, uint16_t *green, uint16_t *blue);

/**
 * @brief      read the clear data
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *clear points to a clear color buffer
 * @return     status code
 *             - 0 success
 *             - 1 read clear failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_read_c(tcs34725_handle_t *handle, uint16_t *clear);

/**
 * @brief     enable or disable the wait time
 * @param[in] *handle points to a tcs34725 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set wait failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tcs34725_set_wait(tcs34725_handle_t *handle, tcs34725_bool_t enable);

/**
 * @brief      get the wait time
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get wait failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_get_wait(tcs34725_handle_t *handle, tcs34725_bool_t *enable);

/**
 * @brief     enable or disable the rgbc adc
 * @param[in] *handle points to a tcs34725 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set rgbc failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tcs34725_set_rgbc(tcs34725_handle_t *handle, tcs34725_bool_t enable);

/**
 * @brief      get the rgbc status
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rgbc failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_get_rgbc(tcs34725_handle_t *handle, tcs34725_bool_t *enable);

/**
 * @brief     enable or disable the power
 * @param[in] *handle points to a tcs34725 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set power on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tcs34725_set_power_on(tcs34725_handle_t *handle, tcs34725_bool_t enable);

/**
 * @brief      get the power status
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get power on failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_get_power_on(tcs34725_handle_t *handle, tcs34725_bool_t *enable);

/**
 * @brief     set the rgbc adc integration time
 * @param[in] *handle points to a tcs34725 handle structure
 * @param[in] t is the adc integration time
 * @return    status code
 *            - 0 success
 *            - 1 set rgbc integration time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tcs34725_set_rgbc_integration_time(tcs34725_handle_t *handle, tcs34725_integration_time_t t);

/**
 * @brief      get the rgbc adc integration time
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *t points to an integration time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rgbc integration time failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_get_rgbc_integration_time(tcs34725_handle_t *handle, tcs34725_integration_time_t *t);

/**
 * @brief     set the wait time
 * @param[in] *handle points to a tcs34725 handle structure
 * @param[in] t is the wait time
 * @return    status code
 *            - 0 success
 *            - 1 set wait time failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tcs34725_set_wait_time(tcs34725_handle_t *handle, tcs34725_wait_time_t t);

/**
 * @brief      get the wait time
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *t points to a wait time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get wait time failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_get_wait_time(tcs34725_handle_t *handle, tcs34725_wait_time_t *t);

/**
 * @brief     set the adc gain
 * @param[in] *handle points to a tcs34725 handle structure
 * @param[in] gain is the adc gain
 * @return    status code
 *            - 0 success
 *            - 1 set gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tcs34725_set_gain(tcs34725_handle_t *handle, tcs34725_gain_t gain);

/**
 * @brief      get the adc gain
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *gain points to an adc gain buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gain failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_get_gain(tcs34725_handle_t *handle, tcs34725_gain_t *gain);

/**
 * @}
 */

/**
 * @defgroup tcs34725_interrupt_driver tcs34725 interrupt driver function
 * @brief    tcs34725 interrupt driver modules
 * @ingroup  tcs34725_driver
 * @{
 */

/**
 * @brief     enable or disable the rgbc interrupt
 * @param[in] *handle points to a tcs34725 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set rgbc interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tcs34725_set_rgbc_interrupt(tcs34725_handle_t *handle, tcs34725_bool_t enable);

/**
 * @brief      get the rgbc interrupt
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rgbc interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_get_rgbc_interrupt(tcs34725_handle_t *handle, tcs34725_bool_t *enable);

/**
 * @brief     set the interrupt mode
 * @param[in] *handle points to a tcs34725 handle structure
 * @param[in] mode is the interrupt mode
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tcs34725_set_interrupt_mode(tcs34725_handle_t *handle, tcs34725_interrupt_mode_t mode);

/**
 * @brief      get the interrupt mode
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *mode points to an interrupt mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_get_interrupt_mode(tcs34725_handle_t *handle, tcs34725_interrupt_mode_t *mode);

/**
 * @brief     set the rgbc clear low interrupt threshold
 * @param[in] *handle points to a tcs34725 handle structure
 * @param[in] threshold is the low interrupt threshold
 * @return    status code
 *            - 0 success
 *            - 1 set rgbc clear low interrupt threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tcs34725_set_rgbc_clear_low_interrupt_threshold(tcs34725_handle_t *handle, uint16_t threshold);

/**
 * @brief      get the rgbc clear low interrupt threshold
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *threshold points to a low interrupt threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rgbc clear low interrupt threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_get_rgbc_clear_low_interrupt_threshold(tcs34725_handle_t *handle, uint16_t *threshold);

/**
 * @brief     set the rgbc clear high interrupt threshold
 * @param[in] *handle points to a tcs34725 handle structure
 * @param[in] threshold is the high interrupt threshold
 * @return    status code
 *            - 0 success
 *            - 1 set rgbc clear high interrupt threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tcs34725_set_rgbc_clear_high_interrupt_threshold(tcs34725_handle_t *handle, uint16_t threshold);

/**
 * @brief      get the rgbc clear high interrupt threshold
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[out] *threshold points to a high interrupt threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rgbc clear high interrupt threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_get_rgbc_clear_high_interrupt_threshold(tcs34725_handle_t *handle, uint16_t *threshold);

/**
 * @}
 */

/**
 * @defgroup tcs34725_extend_driver tcs34725 extend driver function
 * @brief    tcs34725 extend driver modules
 * @ingroup  tcs34725_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to a tcs34725 handle structure
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t tcs34725_set_reg(tcs34725_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a tcs34725 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t tcs34725_get_reg(tcs34725_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
