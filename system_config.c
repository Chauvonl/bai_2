#include "system_config.h"

SensorData sensor_data;
SPWSConfig config;
PumpState pump_state;
LedState led_state;
unsigned long watering_start_time = 0;
unsigned long last_sensor_check_time = 0;
int running = 1;
