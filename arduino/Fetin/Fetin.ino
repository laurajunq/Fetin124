#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

// ======================================
// WIFI CONFIGURATION
// ======================================

const char* WIFI_SSID = "Ana Beatriz";
const char* WIFI_PASSWORD = "ANABIA2710200627";

// ======================================
// HIVEMQ MQTT CONFIGURATION
// ======================================

const char* MQTT_SERVER = "ca7a0fa4df60498cb66ecefa6a0a048b.s1.eu.hivemq.cloud";
const int MQTT_PORT = 8883;

const char* MQTT_USER = "iotesp";
const char* MQTT_PASSWORD = "BIA2710.";

const char* TOPIC_PUBLISH = "hand/pulse";

// ======================================
// HARDWARE CONFIGURATION
// ======================================

const int VIBRATION_MOTOR_PIN = 33;

// ======================================
// MPU6050
// ======================================

Adafruit_MPU6050 mpu;

// ======================================
// MQTT
// ======================================

WiFiClientSecure espClient;
PubSubClient mqttClient(espClient);

// ======================================
// TREMOR SETTINGS
// ======================================

float tremorThreshold = 1.5;

unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 500;

// ======================================
// FUNCTION DECLARATIONS
// ======================================

void initializeMPU();
void connectWiFi();
void reconnectMQTT();

float calculateTremorIntensity(
  float &gyroX,
  float &gyroY,
  float &gyroZ
);

void publishMQTTData(
  float gyroX,
  float gyroY,
  float gyroZ,
  float intensity,
  String status
);

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

  // Configuração SSL/TLS para o HiveMQ
  espClient.setInsecure();

  mqttClient.setServer(
    MQTT_SERVER,
    MQTT_PORT
  );

  Serial.println();
  Serial.println("================================");
  Serial.println("       HANDPULSE READY");
  Serial.println("================================");
}

// ======================================
// LOOP
// ======================================

void loop() {

  // Mantém a conexão MQTT ativa
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }

  mqttClient.loop();

  // Detecta tremores
  detectTremor();

  delay(20);
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

  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );

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
// MQTT RECONNECT
// ======================================

void reconnectMQTT() {

  while (!mqttClient.connected()) {

    Serial.print(
      "Attempting MQTT connection to HiveMQ..."
    );

    // Cria um ID único para o ESP32
    String clientId = "ESP32-TremorSensor-";
    clientId += String(random(0xffff), HEX);

    if (
      mqttClient.connect(
        clientId.c_str(),
        MQTT_USER,
        MQTT_PASSWORD
      )
    ) {

      Serial.println(" Connected!");

    } else {

      Serial.print(" Failed, rc=");
      Serial.print(mqttClient.state());

      Serial.println(
        " Trying again in 5 seconds..."
      );

      delay(5000);
    }
  }
}

// ======================================
// TREMOR CALCULATION
// ======================================

float calculateTremorIntensity(
  float &gyroX,
  float &gyroY,
  float &gyroZ
) {

  sensors_event_t a;
  sensors_event_t g;
  sensors_event_t temp;

  mpu.getEvent(
    &a,
    &g,
    &temp
  );

  gyroX = abs(g.gyro.x);
  gyroY = abs(g.gyro.y);
  gyroZ = abs(g.gyro.z);

  float tremorIntensity = sqrt(
    gyroX * gyroX +
    gyroY * gyroY +
    gyroZ * gyroZ
  );

  return tremorIntensity;
}

// ======================================
// VIBRATION CONTROL
// ======================================

void activateVibration() {

  digitalWrite(
    VIBRATION_MOTOR_PIN,
    HIGH
  );
}

void deactivateVibration() {

  digitalWrite(
    VIBRATION_MOTOR_PIN,
    LOW
  );
}

// ======================================
// TREMOR DETECTION
// ======================================

void detectTremor() {

  float gyroX;
  float gyroY;
  float gyroZ;

  float tremorIntensity =
    calculateTremorIntensity(
      gyroX,
      gyroY,
      gyroZ
    );

  String statusMessage = "NORMAL";

  // ====================================
  // TREMOR CLASSIFICATION
  // ====================================

  if (
    tremorIntensity >
    tremorThreshold * 2
  ) {

    statusMessage = "STRONG";

    activateVibration();

  }

  else if (
    tremorIntensity >
    tremorThreshold
  ) {

    statusMessage = "MODERATE";

    activateVibration();

  }

  else {

    statusMessage = "NORMAL";

    deactivateVibration();
  }

  // ====================================
  // MQTT PUBLISH
  // ====================================

  unsigned long currentTime = millis();

  if (
    currentTime - lastPublishTime
    >= publishInterval
  ) {

    lastPublishTime = currentTime;

    // Serial debug
    Serial.print("Gyro X: ");
    Serial.print(gyroX);

    Serial.print(" | Gyro Y: ");
    Serial.print(gyroY);

    Serial.print(" | Gyro Z: ");
    Serial.print(gyroZ);

    Serial.print(" | Tremor: ");
    Serial.print(tremorIntensity);

    Serial.print(" | Status: ");
    Serial.println(statusMessage);

    publishMQTTData(
      gyroX,
      gyroY,
      gyroZ,
      tremorIntensity,
      statusMessage
    );
  }
}

// ======================================
// PUBLISH MQTT DATA
// ======================================

void publishMQTTData(
  float gyroX,
  float gyroY,
  float gyroZ,
  float intensity,
  String status
) {

  String payload = "{";

  payload += "\"gyro_x\":";
  payload += String(gyroX, 2);

  payload += ",\"gyro_y\":";
  payload += String(gyroY, 2);

  payload += ",\"gyro_z\":";
  payload += String(gyroZ, 2);

  payload += ",\"intensity\":";
  payload += String(intensity, 2);

  payload += ",\"status\":\"";
  payload += status;
  payload += "\"";

  payload += "}";

  bool success = mqttClient.publish(
    TOPIC_PUBLISH,
    payload.c_str()
  );

  if (success) {

    Serial.println(
      "MQTT -> Data published"
    );

  } else {

    Serial.println(
      "MQTT -> Publish failed"
    );
  }
}