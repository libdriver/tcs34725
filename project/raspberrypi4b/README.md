### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

GPIO Pin: INT GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(tcs34725 REQUIRED)
```

#### 2.4 INT Pin

INT pin need a 4.3KΩ resistor connect to 5V.

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
./tcs34725 -i

tcs34725: chip is AMS TCS34725.
tcs34725: manufacturer is AMS.
tcs34725: interface is IIC.
tcs34725: driver version is 2.0.
tcs34725: min supply voltage is 2.7V.
tcs34725: max supply voltage is 3.6V.
tcs34725: max current is 20.00mA.
tcs34725: max temperature is 85.0C.
```

```shell
./tcs34725 -p

tcs34725: SCL connected to GPIO3(BCM).
tcs34725: SDA connected to GPIO2(BCM).
tcs34725: INT connected to GPIO17(BCM).
```

```shell
./tcs34725 -t reg

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
./tcs34725 -t read --times=3

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
tcs34725: red is 123.
tcs34725: green is 124.
tcs34725: blue is 106.
tcs34725: clear is 341.
tcs34725: red is 123.
tcs34725: green is 124.
tcs34725: blue is 106.
tcs34725: clear is 341.
tcs34725: red is 123.
tcs34725: green is 124.
tcs34725: blue is 106.
tcs34725: clear is 342.
tcs34725: set 4x gain.
tcs34725: red is 124.
tcs34725: green is 125.
tcs34725: blue is 106.
tcs34725: clear is 342.
tcs34725: red is 484.
tcs34725: green is 491.
tcs34725: blue is 416.
tcs34725: clear is 1342.
tcs34725: red is 484.
tcs34725: green is 491.
tcs34725: blue is 416.
tcs34725: clear is 1342.
tcs34725: set 16x gain.
tcs34725: red is 484.
tcs34725: green is 490.
tcs34725: blue is 415.
tcs34725: clear is 1339.
tcs34725: red is 1975.
tcs34725: green is 1982.
tcs34725: blue is 1699.
tcs34725: clear is 5452.
tcs34725: red is 1974.
tcs34725: green is 1982.
tcs34725: blue is 1698.
tcs34725: clear is 5450.
tcs34725: set 60x gain.
tcs34725: red is 1976.
tcs34725: green is 1983.
tcs34725: blue is 1700.
tcs34725: clear is 5453.
tcs34725: red is 7552.
tcs34725: green is 7599.
tcs34725: blue is 6457.
tcs34725: clear is 20580.
tcs34725: red is 7563.
tcs34725: green is 7609.
tcs34725: blue is 6464.
tcs34725: clear is 20608.
tcs34725: set rgbc integration time 2.4ms.
tcs34725: red is 94.
tcs34725: green is 94.
tcs34725: blue is 81.
tcs34725: clear is 259.
tcs34725: red is 94.
tcs34725: green is 94.
tcs34725: blue is 81.
tcs34725: clear is 259.
tcs34725: red is 94.
tcs34725: green is 94.
tcs34725: blue is 81.
tcs34725: clear is 259.
tcs34725: set rgbc integration time 24ms.
tcs34725: red is 940.
tcs34725: green is 943.
tcs34725: blue is 808.
tcs34725: clear is 2595.
tcs34725: red is 940.
tcs34725: green is 944.
tcs34725: blue is 809.
tcs34725: clear is 2595.
tcs34725: red is 941.
tcs34725: green is 944.
tcs34725: blue is 809.
tcs34725: clear is 2597.
tcs34725: set rgbc integration time 50ms.
tcs34725: red is 1974.
tcs34725: green is 1981.
tcs34725: blue is 1698.
tcs34725: clear is 5449.
tcs34725: red is 1974.
tcs34725: green is 1982.
tcs34725: blue is 1698.
tcs34725: clear is 5450.
tcs34725: red is 1973.
tcs34725: green is 1980.
tcs34725: blue is 1697.
tcs34725: clear is 5446.
tcs34725: set rgbc integration time 101ms.
tcs34725: red is 4040.
tcs34725: green is 4055.
tcs34725: blue is 3475.
tcs34725: clear is 11155.
tcs34725: red is 4043.
tcs34725: green is 4058.
tcs34725: blue is 3477.
tcs34725: clear is 11158.
tcs34725: red is 4041.
tcs34725: green is 4057.
tcs34725: blue is 3476.
tcs34725: clear is 11155.
tcs34725: set rgbc integration time 154ms.
tcs34725: red is 6021.
tcs34725: green is 6043.
tcs34725: blue is 5178.
tcs34725: clear is 16616.
tcs34725: red is 6014.
tcs34725: green is 6036.
tcs34725: blue is 5173.
tcs34725: clear is 16600.
tcs34725: red is 6017.
tcs34725: green is 6039.
tcs34725: blue is 5175.
tcs34725: clear is 16607.
tcs34725: set rgbc integration time 700ms.
tcs34725: red is 24074.
tcs34725: green is 24157.
tcs34725: blue is 20702.
tcs34725: clear is 65535.
tcs34725: red is 24071.
tcs34725: green is 24155.
tcs34725: blue is 20699.
tcs34725: clear is 65535.
tcs34725: red is 24070.
tcs34725: green is 24154.
tcs34725: blue is 20698.
tcs34725: clear is 65535.
tcs34725: finish read test.
```

```shell
./tcs34725 -t int --times=3 --mode=1 --low-threshold=10 --high-threshold=100

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
tcs34725: clear is 5470 and check high interrupt high threshold.
tcs34725: clear is 5470 and check low interrupt none.
tcs34725: clear is 5475 and check high interrupt high threshold.
tcs34725: clear is 5475 and check low interrupt none.
tcs34725: clear is 5464 and check high interrupt high threshold.
tcs34725: clear is 5464 and check low interrupt none.
tcs34725: finish interrupt test.
```

```shell
./tcs34725 -e read --times=3

tcs34725: 1/3.
tcs34725: red is 1964.
tcs34725: green is 1966.
tcs34725: blue is 1682.
tcs34725: clear is 5414.
tcs34725: 2/3.
tcs34725: red is 1967.
tcs34725: green is 1969.
tcs34725: blue is 1685.
tcs34725: clear is 5421.
tcs34725: 3/3.
tcs34725: red is 1960.
tcs34725: green is 1968.
tcs34725: blue is 1685.
tcs34725: clear is 5414.
```

```shell
./tcs34725 -e int --times=3 --mode=3 --low-threshold=10 --high-threshold=100

tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_3_CLEAR_CHANNEL_OUT_OF_THRESHOLD.
tcs34725: red is 1157.
tcs34725: green is 1237.
tcs34725: blue is 1111.
tcs34725: clear is 3426.
tcs34725: find interrupt.
```

```shell
./tcs34725 -h

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
