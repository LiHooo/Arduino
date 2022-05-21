# WS2812ForESP8266(Arduino)
## ESP8266驱动WS2812时，即使使用FastLED库，也是有问题的，我发现在驱动WS2812时，个别LED回随机的闪烁， 
### 0.驱动WS2812每bit时间为1.25us(0.4us+0.85us) 

### 1.使用寄存器操作GPIO可以输出高达6M的频率 
```C
GPOS=(1<<pin); //set HIGH 
GPOC=(1<<pin); //set LOW 
```
虽然可以成功点亮，但是和FastLED库的现象一样，用逻辑分析仪抓取波形发现波形被打断了，所以怀疑是看门狗的问题 
### 2.关闭看门狗 
ESP.wdtDisable(); 还是一样
### 3.使用串口模拟CODE0和CODE1 
UART是带缓冲的，而且由硬件发送，所以不会被WiFi协议栈打断
