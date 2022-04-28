# STM32F401-PWM

PWM : https://en.wikipedia.org/wiki/Pulse-width_modulation


A very important concept in Pulse-width modulation is : The term duty

The term duty cycle describes the proportion of 'on' time to the regular interval or 'period' of time; 
a low duty cycle corresponds to low power, because the power is off for most of the time. 
Duty cycle is expressed in percent, 100% being fully on. 
When a digital signal is on half of the time and off the other half of the time, the digital signal has a duty cycle of 50% and resembles a "square" wave.
When a digital signal spends more time in the on state than the off state, it has a duty cycle of >50%.
When a digital signal spends more time in the off state than the on state, it has a duty cycle of <50%. 
Here is a pictorial that illustrates these three scenarios:
![image](https://user-images.githubusercontent.com/71445509/165858092-9b5a2b0c-0636-45f5-8827-97598d009f93.png)

This technology is very common in today's mobile phone OLED screens
We reduce the term duty to reduce the brightness, the effect is that the stroboscopic flicker is serious and harmful to the eyes
