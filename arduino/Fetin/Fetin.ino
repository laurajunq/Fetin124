#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

const char* ssid = "Apt_105";
const char* password = "000222201";

Adafruit_MPU6050 mpu;

const int vibracall = 33;

// Limite de tremor
float limiteTremor = 1.5;

void setup() {

  Serial.begin(115200);

  Wire.begin(25, 26);

  pinMode(vibracall, OUTPUT);
  digitalWrite(vibracall, LOW);

  Serial.println("Iniciando MPU6050...");

  if (!mpu.begin()) {

    Serial.println("MPU6050 nao encontrado!");

    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 conectado!");

  WiFi.begin(ssid, password);

  Serial.print("Conectando WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado!");
  Serial.println(WiFi.localIP());
}

void loop() {

  sensors_event_t a, g, temp;

  mpu.getEvent(&a, &g, &temp);

  float gx = abs(g.gyro.x);
  float gy = abs(g.gyro.y);
  float gz = abs(g.gyro.z);

  float intensidadeTremor = gx + gy + gz;

  Serial.print("Gyro X: ");
  Serial.print(gx);

  Serial.print(" | Y: ");
  Serial.print(gy);

  Serial.print(" | Z: ");
  Serial.print(gz);

  Serial.print(" | Tremor: ");
  Serial.println(intensidadeTremor);

  if (intensidadeTremor > limiteTremor) {

    Serial.println("TREMOR DETECTADO");

    digitalWrite(vibracall, HIGH);

  } else {

    digitalWrite(vibracall, LOW);

  }

  Serial.println("--------------------");

  delay(50);
}