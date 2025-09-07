#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} SystemMode;

typedef enum {
    PUMP_OFF,
    PUMP_ON
} PumpState;

typedef enum {
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LedState;

typedef struct {
    int moisture;
    float temperature;
} SensorData;

typedef struct {
    int moisture_min;
    int moisture_max;
    int watering_max_sec;
    int sensor_interval;
    int manual_watering_sec;
    SystemMode mode;
} SPWSConfig;

extern SensorData sensor_data;
extern SPWSConfig config;
extern PumpState pump_state;
extern LedState led_state;
extern unsigned long watering_start_time;
extern unsigned long last_sensor_check_time;
extern int running;
#endif
