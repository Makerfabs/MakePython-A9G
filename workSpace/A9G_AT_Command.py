from machine import UART,Pin,I2C
import machine

import utime

uart = UART(2, baudrate=115200, rx=21, tx=22,timeout=10)
uart1 = UART(1, baudrate=115200, rx=3, tx=1,timeout=10)

A9G_RESET_PIN = Pin(33, Pin.OUT) 
A9G_RESET_PIN.value(0)             

utime.sleep_ms(2000)
A9G_PWR_KEY = Pin(27, Pin.OUT) 
A9G_PWR_KEY.value(0)
utime.sleep_ms(2000)
A9G_PWR_KEY.value(1)
utime.sleep_ms(20000)


if True:
    
    uart1.write('AT\r\n')#1: turn on GPS  0:Turn off GPS
    uart1.write('Hello world!')#1: turn on GPS  0:Turn off GPS
    utime.sleep_ms(1000)
    while True:      
         if uart.any():
            
            bin_data = uart.readline()
            uart1.write(bin_data)         
         if uart1.any():
            
            bin_data = uart1.readline()
            uart.write(bin_data)         


