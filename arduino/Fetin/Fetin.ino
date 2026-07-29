#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

// ======================================
// WIFI CONFIGURATION
// ======================================

const char* WIFI_SSID = "Apt_105";
const char* WIFI_PASSWORD = "000222201";

// ======================================
// HARDWARE CONFIGURATION
// ======================================

const int VIBRATION_MOTOR_PIN = 33;

// ======================================
// MPU6050
// ======================================

Adafruit_MPU6050 mpu;

// ======================================
// TREMOR SETTINGS
// ======================================

float tremorThreshold = 1.5;

// ======================================
// FUNCTION DECLARATIONS
// ======================================

void initializeMPU();
void connectWiFi();

float calculateTremorIntensity();

void activateVibration();
void deactivateVibration();

void detectTremor();

// ======================================
// SETUP
// ======================================

void setup() {

  Serial.begin(115200);

  Wire.begin(25, 26);

  pinMode(VIBRATION_MOTOR_PIN, OUTPUT);
  digitalWrite(VIBRATION_MOTOR_PIN, LOW);

  initializeMPU();

  connectWiFi();

  Serial.println("\nSystem Ready!");
}

// ======================================
// LOOP
// ======================================

void loop() {

  detectTremor();

  delay(50);
}

// ======================================
// MPU INITIALIZATION
// ======================================

void initializeMPU() {

  Serial.println("Initializing MPU6050...");

  if (!mpu.begin()) {

    Serial.println("MPU6050 not found!");

    while (true) {
      delay(10);
    }
  }

  Serial.println("MPU6050 connected!");
}

// ======================================
// WIFI CONNECTION
// ======================================

void connectWiFi() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// ======================================
// TREMOR CALCULATION
// ======================================

float calculateTremorIntensity() {

  sensors_event_t a, g, temp;

  mpu.getEvent(&a, &g, &temp);

  float gyroX = abs(g.gyro.x);
  float gyroY = abs(g.gyro.y);
  float gyroZ = abs(g.gyro.z);

  float tremorIntensity = sqrt(
    gyroX * gyroX +
    gyroY * gyroY +
    gyroZ * gyroZ
  );

  Serial.print("Gyro X: ");
  Serial.print(gyroX);

  Serial.print(" | Gyro Y: ");
  Serial.print(gyroY);

  Serial.print(" | Gyro Z: ");
  Serial.print(gyroZ);

  Serial.print(" | Tremor: ");
  Serial.println(tremorIntensity);

  return tremorIntensity;
}

// ======================================
// VIBRATION CONTROL
// ======================================

void activateVibration() {

  digitalWrite(VIBRATION_MOTOR_PIN, HIGH);
}

void deactivateVibration() {

  digitalWrite(VIBRATION_MOTOR_PIN, LOW);
}

// ======================================
// TREMOR DETECTION
// ======================================

void detectTremor() {

  float tremorIntensity = calculateTremorIntensity();

  if (tremorIntensity > tremorThreshold * 2) {

    Serial.println(">>> STRONG TREMOR DETECTED");

    activateVibration();
  }
  else if (tremorIntensity > tremorThreshold) {

    Serial.println(">>> MODERATE TREMOR DETECTED");

    activateVibration();
  }
  else {

    Serial.println(">>> NORMAL MOVEMENT");

    deactivateVibration();
  }

  Serial.println("--------------------------------");
}