#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>

/**
 * 현재 온습도를 디스플레이하기
 * DHT22(AMS2302)로부터 데이터를 받아 LCD16x2 디스플레이에 표시
 */

// 온습도 센서 설정
#define DHTPIN 2          // 온습도 데이터 연결 핀 번호
#define DHTTYPE DHT22     // AMS2302

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

// LCD1602 설정
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // DHT 초기화
  Serial.begin(9600);
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // 온도센터 상세정보 표시
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("-------------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print(F("Sensor Type:  ")); Serial.println(sensor.name);
  Serial.print(F("Driver Ver:   ")); Serial.println(sensor.version);
  Serial.print(F("Unique ID:    ")); Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value     ")); Serial.print(sensor.max_value); Serial.println(F("℃"));
  Serial.print(F("Min Value     ")); Serial.print(sensor.min_value); Serial.println(F("℃"));
  Serial.print(F("Resolution:   ")); Serial.print(sensor.resolution); Serial.println(F("℃"));
  Serial.println(F("-------------------------------------------"));
  // 습도센서 상세정보 표시
  dht.humidity().getSensor(&sensor);
  Serial.println(F("-------------------------------------------"));
  Serial.println(F("Humidity Sensor"));
  Serial.print(F("Sensor Type:  ")); Serial.println(sensor.name);
  Serial.print(F("Driver Ver:   ")); Serial.println(sensor.version);
  Serial.print(F("Unique ID:    ")); Serial.println(sensor.sensor_id);
  Serial.print(F("Max Value     ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print(F("Min Value     ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print(F("Resolution:   ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("-------------------------------------------"));

  // 지연시간 설정
  delayMS = sensor.min_delay / 1000;

  // LCD 행과 열 설정
  lcd.begin(16, 2);
}

void loop() {
  // 지연시간 설정
  delay(delayMS);
  // 온도 이벤트 발생시 값을 출력
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  lcd.setCursor(0, 0);
  if (isnan(event.temperature)) {
    lcd.print("Error reading temperature!");
  } else {
    lcd.print("Temp. ");
    lcd.print(event.temperature);
    lcd.print(" C");
  }

  // 습도 이벤트 발생시 값을 출력
  dht.humidity().getEvent(&event);
  lcd.setCursor(0, 1);
  if (isnan(event.relative_humidity)) {
    lcd.print(F("Error reading humidity!"));
  } else {
    lcd.print("Humi. ");
    lcd.print(event.relative_humidity);
    lcd.print(" %");
  }
}
