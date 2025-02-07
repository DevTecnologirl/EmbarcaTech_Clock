//Camilly Duarte
from machine import Pin

led = Pin(21, Pin.OUT)
pul = Pin(19, Pin.IN)

while True:
    if pul.value()==1:
        led.value(1)
        else:
            led.value(0)
