#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <LiquidCrystal.h>

MPU6050 mpu;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int a = 0, d = 0, b = 0, c = 0, e = 0, f = 0;
int HIGH_M = 0, MIDDLE_M = 0, LOW_M = 0;
int HIGH_G = 0, MIDDLE_G = 0, LOW_G = 0;
int HIGH_S = 0, MIDDLE_S = 0, LOW_S = 0;
int HIGH_R = 0, MIDDLE_R = 0, LOW_R = 0;

// Define the analog pin for the soil moisture sensor
#define soilMoisturePin A0
// Define the analog pin for the rain sensor
#define rainSensorPin A1

// Define thresholds for accelerometer readings
const float lowThreshold = 1.05; // Low risk threshold for acceleration in g
const float middleThreshold = 2.4; // Middle risk threshold for acceleration in g

// Define thresholds for rain levels in volts
const int lowThreshold_r = 900;
const int middleThreshold_r = 350;

// Define the thresholds for moisture levels
const int lowThreshold_s = 700;
const int middleThreshold_s = 400;

void setup() {
  // Start serial communication at 115200 baud rate
  Serial.begin(115200);

  // Initialize MPU6050
  Wire.begin();
  mpu.initialize();

  // Check if MPU6050 is connected successfully
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  Serial.println("MPU6050 connection successful");

  // Initialize the rain sensor pin as an input
  pinMode(rainSensorPin, INPUT);
  // Initialize the soil moisture sensor pin as an input
  pinMode(soilMoisturePin, INPUT);

  // Initialize the LCD
  lcd.begin(16, 2);
}

void loop() {
  // Read accelerometer values
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Convert to g (assuming a full-scale range of ±2g)
  float accelX = ax / 16384.0;
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;

  // Calculate the magnitude of the acceleration vector
  float accelMagnitude = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ);

  // Print accelerometer values
  Serial.print("AccelX: "); Serial.print(accelX);
  Serial.print(" AccelY: "); Serial.print(accelY);
  Serial.print(" AccelZ: "); Serial.print(accelZ);
  Serial.print(" Magnitude: "); Serial.println(accelMagnitude);

  // Determine the risk level and print the corresponding message
  LOW_M = 0; MIDDLE_M = 0; HIGH_M = 0; // Reset values
  if (accelMagnitude <= lowThreshold) {
    LOW_M = 1;
    a = 1;
  } else if (accelMagnitude > lowThreshold && accelMagnitude <= middleThreshold) {
    MIDDLE_M = 1;
    a = 2;
  } else {
    HIGH_M = 1;
    a = 3;
  }

  // Wait for 1 second before taking another reading


  // Read gyroscope values
  int16_t gx, gy, gz;
  mpu.getRotation(&gx, &gy, &gz);

  // Convert to degrees per second (assuming a full-scale range of ±250 degrees per second)
  float gyroX = gx / 131.0;
  float gyroY = gy / 131.0;
  float gyroZ = gz / 131.0;

  // Print gyroscope values
  Serial.print("GyroX: "); Serial.print(gyroX);
  Serial.print(" GyroY: "); Serial.print(gyroY);
  Serial.print(" GyroZ: "); Serial.println(gyroZ);
  

  // Calculate the average of gyroscope values
  float avgGyro = (abs(gyroX) + abs(gyroY) + abs(gyroZ)) / 3.0;

  // Print the average gyroscope value
  Serial.print("Average Gyro: ");
  Serial.println(avgGyro);
 

  // Determine the risk level and print the corresponding message
  LOW_G = 0; MIDDLE_G = 0; HIGH_G = 0; // Reset values
  if (avgGyro <= lowThreshold) {
    LOW_G = 1;
    d = 1;
  } else if (avgGyro > lowThreshold && avgGyro <= middleThreshold) {
    MIDDLE_G = 1;
    d = 2;
  } else {
    HIGH_G = 1;
    d = 3;
  }

  // Wait for 1 second before taking another reading
 

  // Read the analog value from the rain sensor
  int rainSensorValue = analogRead(rainSensorPin);

  // Print the rain sensor value
  Serial.print("Rain Sensor Value: ");
  Serial.println(rainSensorValue);

  // Determine the rain level and print the corresponding message
  LOW_R = 0; MIDDLE_R = 0; HIGH_R = 0; // Reset values
  if (rainSensorValue > lowThreshold_r) {
    LOW_R = 1;
    b = 1;
  } else if (rainSensorValue > middleThreshold_r) {
    MIDDLE_R = 1;
    b = 2;
  } else {
    HIGH_R = 1;
    b = 3;
  }

  // Wait for 1 second before taking another reading
 

  // Read the analog value from the soil moisture sensor
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Print the soil moisture value
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilMoistureValue);

  // Determine the moisture level and print the corresponding message
  LOW_S = 0; MIDDLE_S = 0; HIGH_S = 0; // Reset values
  if (soilMoistureValue > lowThreshold_s) {
    LOW_S = 1;
    c = 1;
  } else if (soilMoistureValue > middleThreshold_s) {
    MIDDLE_S = 1;
    c = 2;
  } else {
    HIGH_S = 1;
    c = 3;
  }

  if (a == 1) {
    e = 1;
  } else if (a == 2) {
    e = 2;
  } else if (a == 3) {
    e = 3;
  }

  if ((b == 1 && c == 1) || (b == 1 && c == 2)) {
    f = 1;
  } else if ((b == 2 && c == 2) || (b == 2 && c == 3)) {
    f = 2;
  } else if ((b == 3 && c == 2) || (b == 3 && c == 3)) {
    f = 3;
  } else {
    f = 4;
  }

  // Wait for 1 second before displaying the message
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Landslide Risk");
  Serial.println("Landslide Risk");
  lcd.setCursor(0, 1);
  Serial.println(e);
  Serial.println(f);
  if ((e == 1 && (f == 1 || f == 2 || f == 3)) || (e == 2 && f == 1)) {
    lcd.print("LOW        ");
    Serial.println("LOW");
    delay(5000);
  } else if (e == 2 && (f == 2 ||f==1)) {
    lcd.print("MIDDLE     ");
    Serial.println("MIDDLE");
    delay(5000);
  } else if ((e == 3 && (f == 1 || f == 2 || f == 3)) || (e == 2 && f == 3)) {
    lcd.print("HIGH       ");
    Serial.println("HIGH");
    delay(5000);
  } else {
    lcd.print("Input Error");
    Serial.println("LOW        ");
    delay(5000);
  }
}
