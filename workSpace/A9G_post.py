from machine import UART,Pin,I2C
import machine

import utime

uart = UART(2, baudrate=115200, rx=21, tx=22,timeout=10)

A9G_RESET_PIN = Pin(33, Pin.OUT) 
A9G_RESET_PIN.value(0)             

utime.sleep_ms(2000)
A9G_PWR_KEY = Pin(27, Pin.OUT) 
A9G_PWR_KEY.value(0)
utime.sleep_ms(2000)
A9G_PWR_KEY.value(1)
utime.sleep_ms(20000)


if True:
    
    uart.write('AT\r\n')#1: turn on GPS  0:Turn off GPS
    utime.sleep_ms(1000)
    uart.write('AT+CCID\r\n')
    utime.sleep_ms(1000)
    uart.write('AT+CREG?\r\n')
    utime.sleep_ms(1000)
    uart.write('AT+CGATT=1\r\n')
    utime.sleep_ms(1000)
    
    uart.write('AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n')
    utime.sleep_ms(1000)
    uart.write('AT+CGACT=1,1\r\n')
    utime.sleep_ms(1000)
    uart.write('AT+HTTPPOST=\"http://music.163.com/\",\"text/plain\",\"helloworld\"\r\n')
    utime.sleep_ms(1000)
    utime.sleep_ms(1000)
    while True:      
         if uart.any():
            
            bin_data = uart.readline()
            print(bin_data)
            
            utime.sleep_ms(1000)

