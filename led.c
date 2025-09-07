#include <stdio.h>
#include "led.h"

void update_led(LedState state){
    //led_state = state;
    switch (state)
    {
    case LED_NORMAL: printf("LED: NORMAL\n"); break;
    case LED_WATERING: printf("LED: WATERING\n"); break;
    case LED_LOW_MOISTURE_ALERT: printf("LED: LOW MOISTURE ALERT\n"); break;
    case LED_ERROR: printf("LED: ERROR\n"); break;
    default:
        break;
    }
}