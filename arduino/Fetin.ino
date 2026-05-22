#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

const char* ssid = "Apt_105";
const char* password = "000222201";

Adafruit_MPU6050 mpu;

void setup() {

  Serial.begin(115200);

  // Configura I2C
  Wire.begin(25, 26);

  Serial.println("Iniciando MPU6050...");

  // Inicializa MPU6050
  if (!mpu.begin()) {

    Serial.println("MPU6050 nao encontrado!");

    while (1) {
      delay(10);
    }
  }

  Serial.println("MPU6050 conectado!");

  // Conecta WiFi
  WiFi.begin(ssid, password);

  Serial.print("Conectando WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("WiFi conectado!");

  Serial.print("IP da ESP32: ");

  Serial.println(WiFi.localIP());

  delay(1000);
}

void loop() {

  sensors_event_t a, g, temp;

  // Lê dados do MPU6050
  mpu.getEvent(&a, &g, &temp);

  float x = a.acceleration.x;
  float y = a.acceleration.y;
  float z = a.acceleration.z;

  // Mostra valores
  Serial.print("X: ");
  Serial.print(x);

  Serial.print(" | Y: ");
  Serial.print(y);

  Serial.print(" | Z: ");
  Serial.println(z);

  // Detecta movimentos

  if (x > 5) {

    Serial.println("DIREITA");

  }

  else if (x < -5) {

    Serial.println("ESQUERDA");

  }

  else if (y > 5) {

    Serial.println("CIMA");

  }

  else if (y < -5) {

    Serial.println("BAIXO");

  }

  else {

    Serial.println("PARADO");

  }

  Serial.println("-------------------");

  delay(500);
}