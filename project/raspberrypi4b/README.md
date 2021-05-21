### 1. chip

#### 1.1 chip info

chip name : Raspberry Pi 4B

iic pin: SCL/SDA GPIO3/GPIO2

gpio pin: INT GPIO17.

### 2. install

#### 2.1 install info

```shell
sudo apt-get install libgpiod-dev

make
```

### 3. tcs34725

#### 3.1 command Instruction

​          tcs34725 is a basic command which can test all tcs34725 driver function:

​           -i        show tcs34725 chip and driver information.

​           -h      show tcs34725 help.

​           -p      show tcs34725 pin connections of the current board.

​           -t (reg | read <times> | int <times> -m (0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60) -th <lowthreshold> <highthreshold>)

​           -t reg        run register test.

​           -t read <times>        run read test. times means test times.  

​           -t int <times> -m (0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60) -th <lowthreshold> <highthreshold>        run interrupt test. times means test times. lowthreshold means interrupt low threshold. highthreshold means interrupt high threshold.

​           -c (read <times> | int <times> -m (0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60) -th <lowthreshold> <highthreshold>)

​           -c read <times>        run read function. times means read times.  

​           -c int <times> -m (0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60) -th <lowthreshold> <highthreshold>        run interrupt function. times means read times. lowthreshold means interrupt low threshold. highthreshold means interrupt high threshold.

#### 3.2 command example

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
tcs34725: min temperature is -40.0C.
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
tcs34725: set rgbc clear low interrupt threshold 0x05EE.
tcs34725: check rgbc clear low interrupt threshold ok.
tcs34725: tcs34725_set_rgbc_clear_high_interrupt_threshold/tcs34725_get_rgbc_clear_high_interrupt_threshold test.
tcs34725: set rgbc clear high interrupt threshold 0xBDA7.
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
./tcs34725 -t read 3

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
tcs34725: red is 23.
tcs34725: green is 23.
tcs34725: blue is 18.
tcs34725: clear is 70.
tcs34725: red is 23.
tcs34725: green is 23.
tcs34725: blue is 18.
tcs34725: clear is 70.
tcs34725: red is 23.
tcs34725: green is 23.
tcs34725: blue is 18.
tcs34725: clear is 70.
tcs34725: set 4x gain.
tcs34725: red is 23.
tcs34725: green is 23.
tcs34725: blue is 19.
tcs34725: clear is 71.
tcs34725: red is 91.
tcs34725: green is 90.
tcs34725: blue is 73.
tcs34725: clear is 273.
tcs34725: red is 91.
tcs34725: green is 90.
tcs34725: blue is 73.
tcs34725: clear is 274.
tcs34725: set 16x gain.
tcs34725: red is 91.
tcs34725: green is 90.
tcs34725: blue is 73.
tcs34725: clear is 274.
tcs34725: red is 374.
tcs34725: green is 361.
tcs34725: blue is 293.
tcs34725: clear is 1114.
tcs34725: red is 375.
tcs34725: green is 363.
tcs34725: blue is 295.
tcs34725: clear is 1120.
tcs34725: set 60x gain.
tcs34725: red is 377.
tcs34725: green is 364.
tcs34725: blue is 296.
tcs34725: clear is 1124.
tcs34725: red is 1447.
tcs34725: green is 1399.
tcs34725: blue is 1136.
tcs34725: clear is 4296.
tcs34725: red is 1445.
tcs34725: green is 1396.
tcs34725: blue is 1135.
tcs34725: clear is 4289.
tcs34725: set rgbc integration time 2.4ms.
tcs34725: red is 18.
tcs34725: green is 18.
tcs34725: blue is 14.
tcs34725: clear is 55.
tcs34725: red is 19.
tcs34725: green is 18.
tcs34725: blue is 14.
tcs34725: clear is 56.
tcs34725: red is 18.
tcs34725: green is 17.
tcs34725: blue is 14.
tcs34725: clear is 53.
tcs34725: set rgbc integration time 24ms.
tcs34725: red is 180.
tcs34725: green is 176.
tcs34725: blue is 144.
tcs34725: clear is 542.
tcs34725: red is 182.
tcs34725: green is 177.
tcs34725: blue is 145.
tcs34725: clear is 546.
tcs34725: red is 181.
tcs34725: green is 176.
tcs34725: blue is 144.
tcs34725: clear is 544.
tcs34725: set rgbc integration time 50ms.
tcs34725: red is 380.
tcs34725: green is 371.
tcs34725: blue is 303.
tcs34725: clear is 1143.
tcs34725: red is 380.
tcs34725: green is 371.
tcs34725: blue is 303.
tcs34725: clear is 1142.
tcs34725: red is 373.
tcs34725: green is 360.
tcs34725: blue is 293.
tcs34725: clear is 1112.
tcs34725: set rgbc integration time 101ms.
tcs34725: red is 763.
tcs34725: green is 736.
tcs34725: blue is 598.
tcs34725: clear is 2272.
tcs34725: red is 767.
tcs34725: green is 741.
tcs34725: blue is 603.
tcs34725: clear is 2288.
tcs34725: red is 769.
tcs34725: green is 744.
tcs34725: blue is 606.
tcs34725: clear is 2297.
tcs34725: set rgbc integration time 154ms.
tcs34725: red is 1144.
tcs34725: green is 1106.
tcs34725: blue is 901.
tcs34725: clear is 3415.
tcs34725: red is 1128.
tcs34725: green is 1084.
tcs34725: blue is 882.
tcs34725: clear is 3351.
tcs34725: red is 1112.
tcs34725: green is 1093.
tcs34725: blue is 898.
tcs34725: clear is 3364.
tcs34725: set rgbc integration time 700ms.
tcs34725: red is 4440.
tcs34725: green is 4359.
tcs34725: blue is 3578.
tcs34725: clear is 13420.
tcs34725: red is 4437.
tcs34725: green is 4356.
tcs34725: blue is 3575.
tcs34725: clear is 13411.
tcs34725: red is 4434.
tcs34725: green is 4351.
tcs34725: blue is 3570.
tcs34725: clear is 13394.
tcs34725: finish read test.
```

```shell
./tcs34725 -t int 3 -m 1 -th 10 100

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
tcs34725: clear is 1315 and check high interrupt high threshold.
tcs34725: clear is 1315 and check low interrupt none.
tcs34725: clear is 1313 and check high interrupt high threshold.
tcs34725: clear is 1313 and check low interrupt none.
tcs34725: clear is 1319 and check high interrupt high threshold.
tcs34725: clear is 1319 and check low interrupt none.
tcs34725: finish interrupt test.
```

```shell
./tcs34725 -c read 3

tcs34725: 1/3.
tcs34725: red is 393.
tcs34725: green is 401.
tcs34725: blue is 352.
tcs34725: clear is 1237.
tcs34725: 2/3.
tcs34725: red is 393.
tcs34725: green is 401.
tcs34725: blue is 351.
tcs34725: clear is 1238.
tcs34725: 3/3.
tcs34725: red is 393.
tcs34725: green is 401.
tcs34725: blue is 351.
tcs34725: clear is 1235.
```

```shell
./tcs34725 -c int 3 -m 3 -th 10 100

tcs34725: set interrupt mode TCS34725_INTERRUPT_MODE_45_CLEAR_CHANNEL_OUT_OF_THRESHOLD.
tcs34725: red is 377.
tcs34725: green is 415.
tcs34725: blue is 318.
tcs34725: clear is 1244.
tcs34725: red is 377.
tcs34725: green is 415.
tcs34725: blue is 318.
tcs34725: clear is 1244.
tcs34725: red is 376.
tcs34725: green is 414.
tcs34725: blue is 318.
tcs34725: clear is 1240.
tcs34725: find break.
```

```shell
./tcs34725 -h

tcs34725 -i
	show tcs34725 chip and driver information.
tcs34725 -h
	show tcs34725 help.
tcs34725 -p
	show tcs34725 pin connections of the current board.
tcs34725 -t reg
	run register test.
tcs34725 -t read <times>
	run read test.times means test times.
tcs34725 -t int <times> -m (0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60) -th <lowthreshold> <highthreshold>
	run interrupt test.times means test times.lowthreshold means interrupt low threshold.highthreshold means interrupt high threshold.
tcs34725 -c read <times>
	run read function.times means read times.
tcs34725 -c int <times> -m (0 | 1 | 2 | 3 | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60) -th <lowthreshold> <highthreshold>
	run interrupt function.times means read times.lowthreshold means interrupt low threshold.highthreshold means interrupt high threshold.
```

