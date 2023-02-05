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
 * @file      driver_tcs34725.c
 * @brief     driver tcs34725 source file
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

#include "driver_tcs34725.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "AMS TCS34725"        /**< chip name */
#define MANUFACTURER_NAME         "AMS"                 /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.7f                  /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                  /**< chip max supply voltage */
#define MAX_CURRENT               20.0f                 /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                 /**< chip max operating temperature */
#define DRIVER_VERSION            2000                  /**< driver version */

/**
 * @brief chip register definition
 */
#define TCS34725_REG_ENABLE         0x80        /**< enable register */
#define TCS34725_REG_ATIME          0x81        /**< atime register */
#define TCS34725_REG_WTIME          0x83        /**< wtime register */
#define TCS34725_REG_AILTL          0xA4        /**< ailtl register */
#define TCS34725_REG_AILTH          0xA5        /**< ailth register */
#define TCS34725_REG_AIHTL          0xA6        /**< aihtl register */
#define TCS34725_REG_AIHTH          0xA7        /**< aihtl register */
#define TCS34725_REG_PERS           0x8C        /**< pers register */
#define TCS34725_REG_CONFIG         0x8D        /**< config register */
#define TCS34725_REG_CONTROL        0x8F        /**< control register */
#define TCS34725_REG_ID             0x92        /**< id register */
#define TCS34725_REG_STATUS         0x93        /**< status register */
#define TCS34725_REG_CDATAL         0xB4        /**< cdatal register */
#define TCS34725_REG_CDATAH         0xB5        /**< cdatah register */
#define TCS34725_REG_RDATAL         0xB6        /**< rdatal register */
#define TCS34725_REG_RDATAH         0xB7        /**< rdatah register */
#define TCS34725_REG_GDATAL         0xB8        /**< gdatal register */
#define TCS34725_REG_GDATAH         0xB9        /**< gdatah register */
#define TCS34725_REG_BDATAL         0xBA        /**< bdatal register */
#define TCS34725_REG_BDATAH         0xBB        /**< bdatah register */
#define TCS34725_REG_CLEAR          0xE6        /**< clear register */

/**
 * @brief iic address definition
 */
#define TCS34725_ADDRESS        (0x29 << 1)        /**< iic address */

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
uint8_t tcs34725_set_rgbc_interrupt(tcs34725_handle_t *handle, tcs34725_bool_t enable)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);          /* read enable config */
    if (res != 0)                                                                                /* check the result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                                /* read register failed */
        
        return 1;                                                                                /* return error */
    }
    prev &= ~(1 << 4);                                                                           /* clear interrupt */
    prev |= enable << 4;                                                                         /* set enable */
    res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);         /* write config */
    if (res != 0)                                                                                /* check the result */
    {
        handle->debug_print("tcs34725: write register failed.\n");                               /* write register failed */
        
        return 1;                                                                                /* return error */
    }
    
    return 0;                                                                                    /* success return 0 */
}

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
uint8_t tcs34725_get_rgbc_interrupt(tcs34725_handle_t *handle, tcs34725_bool_t *enable)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);        /* read enable config */
    if (res != 0)                                                                              /* check the result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                              /* read register failed */
        
        return 1;                                                                              /* return error */
    }
    prev &= 1 << 4;                                                                            /* get interrupt */
    *enable = (tcs34725_bool_t)((prev >> 4) & 0x01);                                           /* set interrupt */
    
    return 0;                                                                                  /* success return 0 */
}

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
uint8_t tcs34725_set_wait(tcs34725_handle_t *handle, tcs34725_bool_t enable)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);          /* read enable config */
    if (res != 0)                                                                                /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                                /* read register failed */
        
        return 1;                                                                                /* return error */
    }
    prev &= ~(1 << 3);                                                                           /* clear enable bit */
    prev |= enable << 3;                                                                         /* set enable */
    res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);         /* write config */
    if (res != 0)                                                                                /* check the result */
    {
        handle->debug_print("tcs34725: write register failed.\n");                               /* write register failed */
        
        return 1;                                                                                /* return error */
    }
    
    return 0;                                                                                    /* success return 0 */
}

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
uint8_t tcs34725_get_wait(tcs34725_handle_t *handle, tcs34725_bool_t *enable)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);        /* read config */
    if (res != 0)                                                                              /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                              /* read register failed */
        
        return 1;                                                                              /* return error */
    }
    prev &= 1 << 3;                                                                            /* get wait bit */
    *enable = (tcs34725_bool_t)((prev >> 3) & 0x01);                                           /* get wait */
    
    return 0;                                                                                  /* success return 0 */
}

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
uint8_t tcs34725_set_rgbc(tcs34725_handle_t *handle, tcs34725_bool_t enable)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);          /* read config */
    if (res != 0)                                                                                /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                                /* read register failed */
        
        return 1;                                                                                /* return error */
    }
    prev &= ~(1 << 1);                                                                           /* clear enable bit */
    prev |= enable << 1;                                                                         /* set enable */
    res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);         /* write config */
    if (res != 0)                                                                                /* check the result */
    {
        handle->debug_print("tcs34725: write register failed.\n");                               /* write register failed */
        
        return 1;                                                                                /* return error */
    }
    
    return 0;                                                                                    /* success return 0 */
}

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
uint8_t tcs34725_get_rgbc(tcs34725_handle_t *handle, tcs34725_bool_t *enable)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);        /* read enable config */
    if (res != 0)                                                                              /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                              /* read register failed */
        
        return 1;                                                                              /* return error */
    }
    prev &= 1 << 1;                                                                            /* get rgbc bit */ 
    *enable = (tcs34725_bool_t)((prev >> 1) & 0x01);                                           /* get enable */
    
    return 0;                                                                                  /* success return 0 */
}

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
uint8_t tcs34725_set_power_on(tcs34725_handle_t *handle, tcs34725_bool_t enable)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);          /* read config */
    if (res != 0)                                                                                /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                                /* read register failed */
        
        return 1;                                                                                /* return error */
    }
    prev &= ~(1 << 0);                                                                           /* clear enable bit */
    prev |= enable << 0;                                                                         /* set enable */
    res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);         /* write config */
    if (res != 0)                                                                                /* check the result */
    {
        handle->debug_print("tcs34725: write register failed.\n");                               /* write register failed */
        
        return 1;                                                                                /* return error */
    }
    
    return 0;                                                                                    /* success return 0 */
}

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
uint8_t tcs34725_get_power_on(tcs34725_handle_t *handle, tcs34725_bool_t *enable)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);        /* read enable config */
    if (res != 0)                                                                              /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                              /* read register failed */
        
        return 1;                                                                              /* return error */
    }
    prev &= 1 << 0;                                                                            /* get enable bit */
    *enable = (tcs34725_bool_t)((prev >> 0) & 0x01);                                           /* get enable */
    
    return 0;                                                                                  /* success return 0 */
}

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
uint8_t tcs34725_set_rgbc_integration_time(tcs34725_handle_t *handle, tcs34725_integration_time_t t)
{
    uint8_t res;
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_ATIME, (uint8_t *)&t, 1);           /* write config */
    if (res != 0)                                                                              /* check the result */
    {
        handle->debug_print("tcs34725: write register failed.\n");                             /* write register failed */
        
        return 1;                                                                              /* return error */
    }
    
    return 0;                                                                                  /* success return 0 */
}

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
uint8_t tcs34725_get_rgbc_integration_time(tcs34725_handle_t *handle, tcs34725_integration_time_t *t)
{
    uint8_t res;
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_ATIME, (uint8_t *)t, 1);           /* read config */
    if (res != 0)                                                                            /* check the result */
    {
        handle->debug_print("tcs34725: write register failed.\n");                           /* write register failed */
        
        return 1;                                                                            /* return error */
    }
    
    return 0;                                                                                /* success return 0 */
}

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
uint8_t tcs34725_set_wait_time(tcs34725_handle_t *handle, tcs34725_wait_time_t t)
{
    uint8_t res, prev, bit;
    
    if (handle == NULL)                                                                         /* check handle */
    {
        return 2;                                                                               /* return error */
    }
    if (handle->inited != 1)                                                                    /* check handle initialization */
    {
        return 3;                                                                               /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_CONFIG, (uint8_t *)&prev, 1);         /* read config */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                               /* read register failed */
        
        return 1;                                                                               /* return error */
    }
    bit = (t & 0x100) >> 8;                                                                     /* get bit */
    prev &= ~(1 << 1);                                                                          /* clear wait time bit */
    prev |= bit << 1;                                                                           /* set bit */
    res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_CONFIG, (uint8_t *)&prev, 1);        /* write config */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("tcs34725: write register failed.\n");                              /* write register failed */
        
        return 1;                                                                               /* return error */
    }
    prev = t & 0xFF;                                                                            /* get time */
    res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_WTIME, (uint8_t *)&prev, 1);         /* write config */
    if (res != 0)                                                                               /* check the result */
    {
        handle->debug_print("tcs34725: write register failed.\n");                              /* write register failed */
        
        return 1;                                                                               /* return error */
    }
    
    return 0;                                                                                   /* success return 0 */
}

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
uint8_t tcs34725_get_wait_time(tcs34725_handle_t *handle, tcs34725_wait_time_t *t)
{
    uint8_t res, prev, bit;
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_CONFIG, (uint8_t *)&prev, 1);        /* read config */
    if (res != 0)                                                                              /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                              /* read failed */
        
        return 1;                                                                              /* return error */
    }
    prev &= 1 << 1;                                                                            /* get wait time bit */
    bit = (prev >> 1) & 0x01;                                                                  /* get wait time */
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_WTIME, (uint8_t *)&prev, 1);         /* read config */
    if (res != 0)                                                                              /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                              /* read register failed */
        
        return 1;                                                                              /* return error */
    }
    *t = (tcs34725_wait_time_t)((bit << 8) | prev);                                            /* get time */

    return 0;                                                                                  /* success return 0 */
}

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
uint8_t tcs34725_set_rgbc_clear_low_interrupt_threshold(tcs34725_handle_t *handle, uint16_t threshold)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    buf[0] = threshold & 0xFF;                                                               /* get threshold LSB */
    buf[1] = (threshold >> 8) & 0xFF;                                                        /* get threshold MSB */
    res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_AILTL, (uint8_t *)buf, 2);        /* write config */
    if (res != 0)                                                                            /* check the result */
    {
        handle->debug_print("tcs34725: write register failed.\n");                           /* write register failed */
        
        return 1;                                                                            /* return error */
    }
    
    return 0;                                                                                /* success return 0 */
}

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
uint8_t tcs34725_get_rgbc_clear_low_interrupt_threshold(tcs34725_handle_t *handle, uint16_t *threshold)
{
    uint8_t res, buf[2];
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    memset(buf, 0, sizeof(uint8_t) * 2);                                                    /* clear the buffer */
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_AILTL, (uint8_t *)buf, 2);        /* read ailtl */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                           /* read register failed */
        
        return 1;                                                                           /* return error */
    }
    *threshold = ((uint16_t)buf[1] << 8) | buf[0];                                          /* get threshold */
    
    return 0;                                                                               /* success return 0 */
}

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
uint8_t tcs34725_set_rgbc_clear_high_interrupt_threshold(tcs34725_handle_t *handle, uint16_t threshold)
{
    uint8_t res;
    uint8_t buf[2];
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    buf[0] = threshold & 0xFF;                                                               /* get threshold LSB */
    buf[1] = (threshold >> 8) & 0xFF;                                                        /* get threshold MSB */
    res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_AIHTL, (uint8_t *)buf, 2);        /* write config */
    if (res != 0)                                                                            /* check the result */
    {
        handle->debug_print("tcs34725: write register failed.\n");                           /* write register failed */
        
        return 1;                                                                            /* return error */
    }
    
    return 0;                                                                                /* success return 0 */
}

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
uint8_t tcs34725_get_rgbc_clear_high_interrupt_threshold(tcs34725_handle_t *handle, uint16_t *threshold)
{
    uint8_t res, buf[2];
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    memset(buf, 0, sizeof(uint8_t) * 2);                                                    /* clear the buffer */
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_AIHTL, (uint8_t *)buf, 2);        /* read aihtl */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                           /* read register failed */
        
        return 1;                                                                           /* return error */
    }
    *threshold = ((uint16_t)buf[1] << 8) | buf[0];                                          /* get threshold */
    
    return 0;                                                                               /* success return 0 */
}

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
uint8_t tcs34725_set_interrupt_mode(tcs34725_handle_t *handle, tcs34725_interrupt_mode_t mode)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                        /* check handle */
    {
        return 2;                                                                              /* return error */
    }
    if (handle->inited != 1)                                                                   /* check handle initialization */
    {
        return 3;                                                                              /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_PERS, (uint8_t *)&prev, 1);          /* read pers */
    if (res != 0)                                                                              /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                              /* read register failed */
        
        return 1;                                                                              /* return error */
    }
    prev &= ~0x0F;                                                                             /* clear mode bit */
    prev |= mode;                                                                              /* set mode */
    res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_PERS, (uint8_t *)&prev, 1);         /* write config */
    if (res != 0)                                                                              /* check result */
    {
        handle->debug_print("tcs34725: write register failed.\n");                             /* write register failed */
        
        return 1;                                                                              /* return error */
    }

    return 0;                                                                                  /* success return 0 */
}

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
uint8_t tcs34725_get_interrupt_mode(tcs34725_handle_t *handle, tcs34725_interrupt_mode_t *mode)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_PERS, (uint8_t *)&prev, 1);        /* read pers */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                            /* read register failed */
        
        return 1;                                                                            /* return error */
    }
    prev &= 0x0F;                                                                            /* get interrupt mode bits */
    *mode = (tcs34725_interrupt_mode_t)(prev & 0x0F);                                        /* get interrupt mode */
    
    return 0;                                                                                /* success return 0 */
}

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
uint8_t tcs34725_set_gain(tcs34725_handle_t *handle, tcs34725_gain_t gain)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_CONTROL, (uint8_t *)&prev, 1);          /* read control */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                                 /* read register failed */
        
        return 1;                                                                                 /* return error */
    }
    prev &= ~0x03;                                                                                /* get gain bits */
    prev |= gain;                                                                                 /* set gain */
    res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_CONTROL, (uint8_t *)&prev, 1);         /* write config */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("tcs34725: write register failed.\n");                                /* write register failed */
        
        return 1;                                                                                 /* return error */
    }

    return 0;                                                                                     /* success return 0 */
}

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
uint8_t tcs34725_get_gain(tcs34725_handle_t *handle, tcs34725_gain_t *gain)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                         /* check handle */
    {
        return 2;                                                                               /* return error */
    }
    if (handle->inited != 1)                                                                    /* check handle initialization */
    {
        return 3;                                                                               /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_CONTROL, (uint8_t *)&prev, 1);        /* read config */
    if (res != 0)                                                                               /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                               /* read register failed */
        
        return 1;                                                                               /* return error */
    }
    prev &= 0x03;                                                                               /* get gain bits */
    *gain = (tcs34725_gain_t)(prev & 0x03);                                                     /* get gain */
    
    return 0;                                                                                   /* success return 0 */
}

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
uint8_t tcs34725_read_rgbc(tcs34725_handle_t *handle, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear)
{
    uint8_t res, prev;
    uint8_t buf[8];
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_STATUS, (uint8_t *)&prev, 1);          /* read status */
    if (res != 0)                                                                                /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                                /* read register failed */
        
        return 1;                                                                                /* return error */
    }
    if ((prev & (1 << 4)) != 0)                                                                  /* find interrupt */
    {
        res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_CLEAR, NULL, 0);                  /* clear interrupt */
        if (res != 0)                                                                            /* check result */
        {
            handle->debug_print("tcs34725: clear interrupt failed.\n");                          /* clear interrupt failed */
            
            return 1;                                                                            /* return error */
        }
    }
    if ((prev & 0x01) != 0)                                                                      /* if data ready */
    {
        res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_CDATAL, (uint8_t *)buf, 8);        /* read data */
        if (res != 0)                                                                            /* check result */
        {
            handle->debug_print("tcs34725: read failed.\n");                                     /* read failed */
            
            return 1;                                                                            /* return error */
        }
        *clear = ((uint16_t)buf[1] << 8) | buf[0];                                               /* get clear */
        *red   = ((uint16_t)buf[3] << 8) | buf[2];                                               /* get red */
        *green = ((uint16_t)buf[5] << 8) | buf[4];                                               /* get green */
        *blue  = ((uint16_t)buf[7] << 8) | buf[6];                                               /* get blue */
   
        return 0;                                                                                /* success return 0 */
    }
    else
    {
        handle->debug_print("tcs34725: data not ready.\n");                                      /* data not ready */
            
        return 1;                                                                                /* return error */
    }
}

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
uint8_t tcs34725_read_rgb(tcs34725_handle_t *handle, uint16_t *red, uint16_t *green, uint16_t *blue)
{
    uint8_t res, prev;
    uint8_t buf[8];
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_STATUS, (uint8_t *)&prev, 1);          /* read config */
    if (res != 0)                                                                                /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                                /* read register failed */
        
        return 1;                                                                                /* return error */
    }
    if ((prev & (1 << 4)) != 0)                                                                  /* find interrupt */
    {
        res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_CLEAR, NULL, 0);                  /* clear interrupt */
        if (res != 0)                                                                            /* check result */
        {
            handle->debug_print("tcs34725: clear interrupt failed.\n");                          /* clear interrupt failed */
            
            return 1;                                                                            /* return error */
        }
    }
    if ((prev & 0x01) != 0)                                                                      /* if data ready */
    {
        res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_CDATAL, (uint8_t *)buf, 8);        /* read data */
        if (res != 0)                                                                            /* check result */
        {
            handle->debug_print("tcs34725: read failed.\n");                                     /* read data failed */
            
            return 1;                                                                            /* return error */
        }
        *red   = ((uint16_t)buf[3] << 8) | buf[2];                                               /* get red */
        *green = ((uint16_t)buf[5] << 8) | buf[4];                                               /* get green */
        *blue  = ((uint16_t)buf[7] << 8) | buf[6];                                               /* get blue */
   
         return 0;                                                                               /* success return 0 */
    }
    else
    {
        handle->debug_print("tcs34725: data not ready.\n");                                      /* data not ready */
            
        return 1;                                                                                /* return error */
    }
}

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
uint8_t tcs34725_read_c(tcs34725_handle_t *handle, uint16_t *clear)
{
    uint8_t res, prev;
    uint8_t buf[8];
    
    if (handle == NULL)                                                                          /* check handle */
    {
        return 2;                                                                                /* return error */
    }
    if (handle->inited != 1)                                                                     /* check handle initialization */
    {
        return 3;                                                                                /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_STATUS, (uint8_t *)&prev, 1);          /* read status */
    if (res != 0)                                                                                /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                                /* read register failed */
        
        return 1;                                                                                /* return error */
    }
    if ((prev & (1 << 4)) != 0)                                                                  /* find interrupt */
    {
        res = handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_CLEAR, NULL, 0);                  /* clear interrupt */
        if (res != 0)                                                                            /* check result */
        {
            handle->debug_print("tcs34725: clear interrupt failed.\n");                          /* clear interrupt failed */
            
            return 1;                                                                            /* return error */
        }
    }
    if ((prev & 0x01) != 0)                                                                      /* if data ready */
    {
        res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_CDATAL, (uint8_t *)buf, 8);        /* read data */
        if (res != 0)                                                                            /* check result */
        {
            handle->debug_print("tcs34725: read failed.\n");                                     /* read failed */
            
            return 1;                                                                            /* return error */
        }
        *clear = ((uint16_t)buf[1] << 8) | buf[0];                                               /* get clear */
   
         return 0;                                                                               /* success return 0 */
    }
    else
    {
        handle->debug_print("tcs34725: data not ready.\n");                                      /* data not ready */
            
        return 1;                                                                                /* return error */
    }
}

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
uint8_t tcs34725_init(tcs34725_handle_t *handle)
{
    uint8_t res, id;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->debug_print == NULL)                                                     /* check debug_print */
    {
        return 3;                                                                        /* return error */
    }
    if (handle->iic_init == NULL)                                                        /* check iic_init */
    {
        handle->debug_print("tcs34725: iic_init is null.\n");                            /* iic_init is null */
        
        return 3;                                                                        /* return error */
    }
    if (handle->iic_deinit == NULL)                                                      /* check iic_init */
    {
        handle->debug_print("tcs34725: iic_deinit is null.\n");                          /* iic_deinit is null */
        
        return 3;                                                                        /* return error */
    }
    if (handle->iic_read == NULL)                                                        /* check iic_read */
    {
        handle->debug_print("tcs34725: iic_read is null.\n");                            /* iic_read is null */
        
        return 3;                                                                        /* return error */
    }
    if (handle->iic_write == NULL)                                                       /* check iic_write */
    {
        handle->debug_print("tcs34725: iic_write is null.\n");                           /* iic_write is null */
        
        return 3;                                                                        /* return error */
    }
    if (handle->delay_ms == NULL)                                                        /* check delay_ms */
    {
        handle->debug_print("tcs34725: delay_ms is null.\n");                            /* delay_ms is null */
        
        return 3;                                                                        /* return error */
    }
    
    if (handle->iic_init() != 0)                                                         /* iic init */
    {
        handle->debug_print("tcs34725: iic init failed.\n");                             /* iic init failed */
        
        return 1;                                                                        /* return error */
    }
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_ID, (uint8_t *)&id, 1);        /* read id */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("tcs34725: read id failed.\n");                              /* read id failed */
        (void)handle->iic_deinit();                                                      /* iic deinit */
        
        return 1;                                                                        /* return error */
    }
    if ((id != 0x44) && (id != 0x4D))                                                    /* check id */
    {
        handle->debug_print("tcs34725: id is error.\n");                                 /* id is error */
        (void)handle->iic_deinit();                                                      /* iic deinit */
        
        return 1;                                                                        /* return error */
    }
    handle->inited = 1;                                                                  /* flag finish initialization */

    return 0;                                                                            /* success return 0 */
}

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
uint8_t tcs34725_deinit(tcs34725_handle_t *handle)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                       /* check handle */
    {
        return 2;                                                                             /* return error */
    }
    if (handle->inited != 1)                                                                  /* check handle initialization */
    {
        return 3;                                                                             /* return error */
    }
 
    res = handle->iic_read(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1);       /* read enable */
    if (res != 0)                                                                             /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");                             /* read register failed */
        
        return 1;                                                                             /* return error */
    }
    prev &= ~(1 << 0);                                                                        /* disable */
    if (handle->iic_write(TCS34725_ADDRESS, TCS34725_REG_ENABLE, (uint8_t *)&prev, 1) != 0)   /* write enable */
    {
         handle->debug_print("tcs34725: write register failed.\n");                           /* write register failed */
        
        return 1;                                                                             /* return error */
    }
    if (handle->iic_deinit() != 0)                                                            /* iic deinit */
    {
        handle->debug_print("tcs34725: iic deinit failed.\n");                                /* iic deinit failed */
        
        return 1;                                                                             /* return error */
    }   
    handle->inited = 0;                                                                       /* flag close */
    
    return 0;                                                                                 /* success return 0 */
}

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
uint8_t tcs34725_set_reg(tcs34725_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = handle->iic_write(TCS34725_ADDRESS, reg, buf, len);             /* write data */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("tcs34725: write register failed.\n");        /* write register failed */
        
        return 1;                                                         /* return error */
    }

    return 0;                                                             /* success return 0 */
}

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
uint8_t tcs34725_get_reg(tcs34725_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint8_t res;
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    res = handle->iic_read(TCS34725_ADDRESS, reg, buf, len);             /* read data */
    if (res != 0)                                                        /* check result */
    {
        handle->debug_print("tcs34725: read register failed.\n");        /* read register failed */
        
        return 1;                                                        /* return error */
    }

    return 0;                                                            /* success return 0 */
}

/**
 * @brief      get chip information
 * @param[out] *info points to a tcs34725 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t tcs34725_info(tcs34725_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(tcs34725_info_t));                       /* initialize tcs34725 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
