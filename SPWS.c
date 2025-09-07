#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/select.h>

#include "system_config.h"
#include "led.h"
#include "pump.h"

// --- Khai báo hàm ---
void read_sensors(SensorData *data);
void system_init(void);
void turn_pump_on(void);
void turn_pump_off(void);
void update_led(LedState state);
void auto_watering_logic(void);
void button_toggle_mode(void);
void button_manual_water(void);
void check_keyboard_input(void);


// --- MAIN ---
int main(void) {
    srand(time(NULL)); // seed random
    system_init();

    while (running) {
        unsigned long now = time(NULL);

        // Đọc cảm biến theo chu kỳ
        if (now - last_sensor_check_time >= config.sensor_interval) {
            read_sensors(&sensor_data);
            last_sensor_check_time = now;
        }

        // Logic tưới tự động
        auto_watering_logic();

        // Kiểm tra phím nhấn
        check_keyboard_input();

        sleep(1);
    }
    return 0;
}

// --- CODE ---
void system_init(void) {

    config.moisture_min = 30;
    config.moisture_max = 70;
    config.watering_max_sec = 10;
    config.sensor_interval = 5;
    config.manual_watering_sec = 5;
    config.mode = MODE_AUTO;

    pump_state = PUMP_OFF;
    led_state = LED_NORMAL;

    printf("Hệ thống bắt đầu (AUTO mode).\n");
    printf("Phím m: đổi chế độ, w: tưới thủ công, q: thoát\n");
}

void read_sensors(SensorData *data) {
    data->moisture = rand() % 101; // 0 - 100%
    data->temperature = 20.0 + (rand() % 150) / 10.0; // 20.0 - 34.9 °C

    printf("[SENSOR] Đọc xong: moisture=%d%%, temp=%.1fC\n", 
           data->moisture, data->temperature);
}

void auto_watering_logic(void) {
    if (config.mode != MODE_AUTO) return;

    if (sensor_data.moisture < config.moisture_min && pump_state == PUMP_OFF) {
        turn_pump_on();
        update_led(LED_WATERING);
    }

    if (pump_state == PUMP_ON) {
        if (sensor_data.moisture >= config.moisture_max ||
            (time(NULL) - watering_start_time) >= config.watering_max_sec) {
            turn_pump_off();
            update_led(LED_NORMAL);
        }
    }
}

void button_toggle_mode(void) {
    if (config.mode == MODE_AUTO) {
        config.mode = MODE_MANUAL;
        turn_pump_off();
        printf("Switched to MANUAL mode.\n");
    } else {
        config.mode = MODE_AUTO;
        printf("Switched to AUTO mode.\n");
    }
}

void button_manual_water(void) {
    if (config.mode == MODE_MANUAL) {
        turn_pump_on();
        update_led(LED_WATERING);
        sleep(config.manual_watering_sec);
        turn_pump_off();
        update_led(LED_NORMAL);
    } else {
        printf("Không thể tưới thủ công khi ở AUTO mode.\n");
    }
}

// --- Hàm đọc phím ---
void check_keyboard_input(void) {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);

    if (select(1, &fds, NULL, NULL, &tv) > 0) {
        char c = getchar();
        if (c == 'm') button_toggle_mode();
        else if (c == 'w') button_manual_water();
        else if (c == 'q') {
            running = 0;
            printf("Thoát chương trình.\n");
        }
    }
}
