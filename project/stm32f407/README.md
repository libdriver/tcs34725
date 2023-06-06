### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

GPIO Pin: INT PB0.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. TCS34725

#### 3.1 Command Instruction

1. Show tcs34725 chip and driver information.

   ```shell
   tcs34725 (-i | --information)
   ```

2. Show tcs34725 help.

   ```shell
   tcs34725 (-h | --help)
   ```

3. Show tcs34725 pin connections of the current board.

   ```shell
   tcs34725 (-p | --port)
   ```

4. Run register test.

   ```shell
   tcs34725 (-t reg | --test=reg)
   ```

5. Run read test, num means test times.

   ```shell
   tcs34725 (-t read | --test=read) [--times=<num>]
   ```

6. Run interrupt test, num means test times, low means interrupt low threshold, high means interrupt high threshold.

   ```shell
   tcs34725 (-t int | --test=int) [--times=<num>] [--mode=<0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60>] [--low-threshold=<low>] [--high-threshold=<high>]
   ```

7. Run read function, num means read times.

   ```shell
   tcs34725 (-e read | --example=read) [--times=<num>]
   ```

8. Run interrupt function, num means read times, low means interrupt low threshold, high means interrupt high threshold.

   ```shell
   tcs34725 (-e int | --example=int) [--times=<num>] [--mode=<0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60>] [--low-threshold=<low>] [--high-threshold=<high>]
   ```

#### 3.2 Command Example

```shell
tcs34725 -i

tcs34725: chip is AMS TCS34725.
tcs34725: manufacturer is AMS.
tcs34725: interface is IIC.
tcs34725: driver version is 2.0.
tcs34725: min supply voltage is 2.7V.
tcs34725: max supply voltage is 3.6V.
tcs34725: max current is 20.00mA.
tcs34725: max temperature is 85.0C.
tcs34725: min temperature is -40.0C.
```

```shell
tcs34725 -p

tcs34725: SCL connected to GPIOB PIN8.
tcs34725: SDA connected to GPIOB PIN9.
tcs34725: INT connected to GPIOB PIN0.
```

```shell
tcs34725 -t reg

tcs34725: chip is AMS TCS34725.
tcs34725: manufacturer is AMS.
tcs34725: interface is IIC.
tcs34725: driver version is 2.0.
tcs34725: min supply voltage is 2.7V.
tcs34725: max supply voltage is 3.6V.
tcs34725: max current is 20.00mA.
tcs34725: max temperature is 85.0C.
tcs34725: min temperature is -40.0C.
tcs34725: start register test.
tcs34725: tcs34725_set_rgbc_interrupt/tcs34725_get_rgbc_interrupt test.
tcs34725: set rgbc interrupt enable.
tcs34725: check rgbc interrupt ok.
tcs34725: set rgbc interrupt disable.
tcs34725: check rgbc interrupt ok.
tcs34725: tcs34725_set_wait/tcs34725_get_wait test.
tcs34725: set wait enable.
tcs34725: check wait ok.
tcs34725: set wait disable.
tcs34725: check wait ok.
tcs34725: tcs34725_set_rgbc/tcs34725_get_rgbc test.
tcs34725: set rgbc enable.
tcs34725: check rgbc ok.
tcs34725: set rgbc disable.
tcs34725: check rgbc ok.
tcs34725: tcs34725_set_power_on/tcs34725_get_power_on test.
tcs34725: set power on enable.
tcs34725: check power on ok.
tcs34725: set power on disable.
tcs34725: check power on ok.
tcs34725: tcs34725_set_rgbc_integration_time/tcs34725_get_rgbc_integration_time test.
tcs34725: set rgbc integration time 2.4ms.
tcs34725: check rgbc integration time ok.
tcs34725: set rgbc integration time 24ms.
tcs34725: check rgbc integration time ok.
tcs34725: set rgbc integration time 50ms.
tcs34725: check rgbc integration time ok.
tcs34725: set rgbc integration time 101ms.
tcs34725: check rgbc integration time ok.
tcs34725: set rgbc integration time 154ms.
tcs34725: check rgbc integration time ok.
tcs34725: set rgbc integration time 700ms.
tcs34725: check rgbc integration time ok.
tcs34725: tcs34725_set_wait_time/tcs34725_get_wait_time test.
tcs34725: set wait time 2.4ms.
tcs34725: check wait time ok.
tcs34725: set wait time 204ms.
tcs34725: check wait time ok.
tcs34725: set wait time 614ms.
tcs34725: check wait time ok.
tcs34725: set wait time 29ms.
tcs34725: check wait time ok.
tcs34725: set wait time 2450ms.
tcs34725: check wait time ok.
tcs34725: set wait time 7400ms.
tcs34725: check wait time ok.
tcs34725: tcs34725_set_rgbc_clear_low_interrupt_threshold/tcs34725_get_rgbc_clear_low_interrupt_threshold test.
tcs34725: set rgbc clear low interrupt threshold 0xF6F7.
tcs34725: check rgbc clear low interrupt threshold ok.
tcs34725: tcs34725_set_rgbc_clear_high_interrupt_threshold/tcs34725_get_rgbc_clear_high_interrupt_threshold test.
tcs34725: set rgbc clear high interrupt threshold 0x934B.
tcs34725: check rgbc clear high interrupt threshold ok.
tcs34725: tcs34725_set_gain/tcs34725_get_gain test.
tcs34725: set gain 1x.
tcs34725: check gain ok.
tcs34725: set gain 4x.
tcs34725: check gain ok.
tcs34725: set gain 16x.
tcs34725: check gain ok.
tcs34725: set gain 60x.
tcs34725: check gain ok.
tcs34725: tcs34725_set_interrupt_mode/tcs34725_get_interrupt_mode test.
tcs34725: set interrupt mode every rgbc cycle.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 1 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 2 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 3 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 5 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 10 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 15 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 20 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 25 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 30 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 35 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 40 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 45 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 50 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 55 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: set interrupt mode 60 clear out of threshold.
tcs34725: check interrupt mode ok.
tcs34725: finish register test.
```

```shell
tcs34725 -t read --times=3

tcs34725: chip is AMS TCS34725.
tcs34725: manufacturer is AMS.
tcs34725: interface is IIC.
tcs34725: driver version is 2.0.
tcs34725: min supply voltage is 2.7V.
tcs34725: max supply voltage is 3.6V.
tcs34725: max current is 20.00mA.
tcs34725: max temperature is 85.0C.
tcs34725: min temperature is -40.0C.
tcs34725: start read test.
tcs34725: set 1x gain.
tcs34725: red is 39.
tcs34725: green is 54.
tcs34725: blue is 47.
tcs34725: clear is 152.
tcs34725: red is 39.
tcs34725: green is 54.
tcs34725: blue is 47.
tcs34725: clear is 152.
tcs34725: red is 39.
tcs34725: green is 54.
tcs34725: blue is 47.
tcs34725: clear is 152.
tcs34725: set 4x gain.
tcs34725: red is 39.
tcs34725: green is 54.
tcs34725: blue is 47.
tcs34725: clear is 152.
tcs34725: red is 152.
tcs34725: green is 212.
tcs34725: blue is 186.
tcs34725: clear is 597.
tcs34725: red is 152.
tcs34725: green is 212.
tcs34725: blue is 186.
tcs34725: clear is 597.
tcs34725: set 16x gain.
tcs34725: red is 151.
tcs34725: green is 212.
tcs34725: blue is 186.
tcs34725: clear is 597.
tcs34725: red is 619.
tcs34725: green is 855.
tcs34725: blue is 758.
tcs34725: clear is 2426.
tcs34725: red is 619.
tcs34725: green is 856.
tcs34725: blue is 758.
tcs34725: clear is 2428.
tcs34725: set 60x gain.
tcs34725: red is 619.
tcs34725: green is 855.
tcs34725: blue is 758.
tcs34725: clear is 2427.
tcs34725: red is 2357.
tcs34725: green is 3262.
tcs34725: blue is 2874.
tcs34725: clear is 9151.
tcs34725: red is 2356.
tcs34725: green is 3263.
tcs34725: blue is 2872.
tcs34725: clear is 9148.
tcs34725: set rgbc integration time 2.4ms.
tcs34725: red is 29.
tcs34725: green is 41.
tcs34725: blue is 36.
tcs34725: clear is 116.
tcs34725: red is 29.
tcs34725: green is 41.
tcs34725: blue is 36.
tcs34725: clear is 115.
tcs34725: red is 29.
tcs34725: green is 41.
tcs34725: blue is 36.
tcs34725: clear is 116.
tcs34725: set rgbc integration time 24ms.
tcs34725: red is 295.
tcs34725: green is 407.
tcs34725: blue is 361.
tcs34725: clear is 1157.
tcs34725: red is 295.
tcs34725: green is 407.
tcs34725: blue is 361.
tcs34725: clear is 1156.
tcs34725: red is 295.
tcs34725: green is 408.
tcs34725: blue is 361.
tcs34725: clear is 1157.
tcs34725: set rgbc integration time 50ms.
tcs34725: red is 620.
tcs34725: green is 856.
tcs34725: blue is 759.
tcs34725: clear is 2430.
tcs34725: red is 620.
tcs34725: green is 856.
tcs34725: blue is 759.
tcs34725: clear is 2430.
tcs34725: red is 620.
tcs34725: green is 856.
tcs34725: blue is 759.
tcs34725: clear is 2430.
tcs34725: set rgbc integration time 101ms.
tcs34725: red is 1269.
tcs34725: green is 1754.
tcs34725: blue is 1554.
tcs34725: clear is 4977.
tcs34725: red is 1269.
tcs34725: green is 1754.
tcs34725: blue is 1554.
tcs34725: clear is 4977.
tcs34725: red is 1269.
tcs34725: green is 1754.
tcs34725: blue is 1554.
tcs34725: clear is 4977.
tcs34725: set rgbc integration time 154ms.
tcs34725: red is 1888.
tcs34725: green is 2608.
tcs34725: blue is 2310.
tcs34725: clear is 7401.
tcs34725: red is 1887.
tcs34725: green is 2608.
tcs34725: blue is 2310.
tcs34725: clear is 7401.
tcs34725: red is 1888.
tcs34725: green is 2608.
tcs34725: blue is 2310.
tcs34725: clear is 7401.
tcs34725: set rgbc integration time 700ms.
tcs34725: red is 7550.
tcs34725: green is 10431.
tcs34725: blue is 9242.
tcs34725: clear is 29605.
tcs34725: red is 7563.
tcs34725: green is 10457.
tcs34725: blue is 9256.
tcs34725: clear is 29685.
tcs34725: red is 7563.
tcs34725: green is 10457.
tcs34725: blue is 9256.
tcs34725: clear is 29688.
tcs34725: finish read test.
```

```shell
tcs34725 -t int --times=3 --mode=1 --low-threshold=10 --high-threshold=100

tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_1_CLEAR_CHANNEL_OUT_OF_THRESHOLD.
tcs34725: chip is AMS TCS34725.
tcs34725: manufacturer is AMS.
tcs34725: interface is IIC.
tcs34725: driver version is 2.0.
tcs34725: min supply voltage is 2.7V.
tcs34725: max supply voltage is 3.6V.
tcs34725: max current is 20.00mA.
tcs34725: max temperature is 85.0C.
tcs34725: min temperature is -40.0C.
tcs34725: start interrupt test.
tcs34725: clear is 2477 and check high interrupt high threshold.
tcs34725: clear is 2477 and check low interrupt none.
tcs34725: clear is 2477 and check high interrupt high threshold.
tcs34725: clear is 2477 and check low interrupt none.
tcs34725: clear is 2478 and check high interrupt high threshold.
tcs34725: clear is 2478 and check low interrupt none.
tcs34725: finish interrupt test.
```

```shell
tcs34725 -e read --times=3

tcs34725: 1/3.
tcs34725: red is 628.
tcs34725: green is 872.
tcs34725: blue is 770.
tcs34725: clear is 2479.
tcs34725: 2/3.
tcs34725: red is 628.
tcs34725: green is 872.
tcs34725: blue is 770.
tcs34725: clear is 2478.
tcs34725: 3/3.
tcs34725: red is 628.
tcs34725: green is 872.
tcs34725: blue is 769.
tcs34725: clear is 2477.
```

```shell
tcs34725 -e int --times=3 --mode=3 --low-threshold=10 --high-threshold=100

tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_3_CLEAR_CHANNEL_OUT_OF_THRESHOLD.
tcs34725: red is 629.
tcs34725: green is 872.
tcs34725: blue is 770.
tcs34725: clear is 2479.
tcs34725: find interrupt.
```

```shell
tcs34725 -h

Usage:
  tcs34725 (-i | --information)
  tcs34725 (-h | --help)
  tcs34725 (-p | --port)
  tcs34725 (-t reg | --test=reg)
  tcs34725 (-t read | --test=read) [--times=<num>]
  tcs34725 (-t int | --test=int) [--times=<num>]
           [--mode=<0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60>]
           [--low-threshold=<low>] [--high-threshold=<high>]
  tcs34725 (-e read | --example=read) [--times=<num>]
  tcs34725 (-e int | --example=int) [--times=<num>]
           [--mode=<0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60>]
           [--low-threshold=<low>] [--high-threshold=<high>]

Options:
  -e <read | int>, --example=<read | int>
                                   Run the driver example.
  -h, --help                       Show the help.
      --high-threshold=<high>      Set the interrupt high threshold.([default: 100])
  -i, --information                Show the chip information.
      --low-threshold=<low>        Set the interrupt low threshold.([default: 10])
      --mode=<0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60> 
                                   Set the interrupt mode.
  -p, --port                       Display the pin connections of the current board.
  -t <reg | read | int>, --test=<reg | read | int>
                                   Run the driver test.
      --times=<num>                Set the running times.([default: 3])
```

