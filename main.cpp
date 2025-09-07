#include <Arduino.h>
//1. khai báo trạng thái led
typedef enum
{
    LED_NORMAL,
    LED_WATERING,
    LED_ERORR
} LedStatus;

//2. khai báo trạng Pum
typedef enum
{
    PUM_OFF,
    PUM_ON
} PumStatus;

//3. khai báo system mode
typedef enum
{
    MODE_AUTO,
    MODE_MANUAL,
} SystemMode;

//4. cấu trúc dữ liệu cảm biến
typedef struct
{
    float TEMPERATURE;
    float MOISTRUCT;
} SensorData;

//5. cấu trúc hệ thống
typedef struct 
{
    int THRESHOLD_MIN;
    int THRESHOLD_MAX;
    int TIME_WATERING_MAX;
    int SENSOR_INTERVAL;
    int TIME_MANAUAL_WATERING;
    SystemMode mode;
} SPWSConfig;

//6. hàm đọc cảm biến
//7. hàm điều khiển Pum
void Turn_pum_on()
{
    digitalWrite(PumPin, 1);
    pum_state = PUM_ON;
    watering_start_time = millis();
    Serial.println("Pum On");
}

void Turn_pum_off()
{
    digitalWrite(PumPin, 0);
    pum_state = PUM_OFF;
    Serial.println("Pum Off");
}

//8. hàm điều khiển Led
void update_led(LedStatus state)
{
    led_state = state;
    digitalWrite(ledNormalPin, state == LED_NORMAL);
    digitalWrite(ledWateringPin, state == LED_WATERING);
    digitalWrite(ledErorrPin, state == LED_ERORR);
}

//9. hàm logic tưới cây

//10. xứ lý nút nhấn
//11. khởi động hệ thống

// Biến toàn cục
PumStatus pum_state;
LedStatus led_state;



unsigned long watering_start_time = 0;

// KẾT NỐI PHẦN CỨNG
const int buttonModePin = 2;
const int buttonManualPin = 3;

const int PumPin = 5;
const int ledNormalPin = 6;
const int ledWateringPin = 7;
const int ledErorrPin = 8;
const int SensorDHT11 = A0;

void setup() 
{
  
}

void loop() 
{
 
}

