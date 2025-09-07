#include <stdio.h>
#include <time.h>
#include "pump.h"

void turn_pump_on(void){
    pump_state = PUMP_ON;
    watering_start_time = time(NULL);
    printf("Pump ON.\n");
}

void turn_pump_off(void){
    pump_state = PUMP_OFF;
    printf("Pump OFF.\n");
}