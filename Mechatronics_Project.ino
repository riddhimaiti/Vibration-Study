#include <Wire.h>
#include <MPU6050.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

MPU6050 mpu;
TinyGPSPlus gps;
SoftwareSerial gpsSerial(3,4);
Adafruit_ADXL345_Unified adxl = Adafruit_ADXL345_Unified();

unsigned long prevTime;
float prevGx = 0, prevGy = 0, prevGz = 0;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while(1);
  }
  if(!adxl.begin()) {
    Serial.println("ADXL345 not detected. Check wiring!");
    while(1);
  }

  Serial.println("Time(ms),Lat,Lon,Speed(kmph),Ax,Ay,Az,Gx,Gy,Gz,AlphaX,AlphaY,AlphaZ");
  prevTime = millis();
  adxl.setRange(ADXL345_RANGE_2_G);
}

void loop() {

//   Serial.print("Satellites: ");
// Serial.println(gps.satellites.value());

  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  float Ax = (mpu.getAccelerationX() / 16384.0) * 9.81;
  float Ay = (mpu.getAccelerationY() / 16384.0) * 9.81;
  float Az = (mpu.getAccelerationZ() / 16384.0) * 9.81;

  float Gx = mpu.getRotationX() / 131.0;
  float Gy = mpu.getRotationY() / 131.0;
  float Gz = mpu.getRotationZ() / 131.0;

  unsigned long currTime = millis();
  float dt = (currTime - prevTime) / 1000.0;

  float AlphaX = (Gx - prevGx) / dt;
  float AlphaY = (Gy - prevGy) / dt;
  float AlphaZ = (Gz - prevGz) / dt;

  Serial.print(currTime); Serial.print(",");

  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6); Serial.print(",");
    Serial.print(gps.location.lng(), 6); Serial.print(",");
  } else {
    Serial.print("0,0,");
  }

  if (gps.speed.isValid()) {
    Serial.print(gps.speed.kmph(), 2); Serial.print(",");
  } else {
    Serial.print("0,");
  }

  Serial.print(Ax); Serial.print(",");
  Serial.print(Ay); Serial.print(",");
  Serial.print(Az); Serial.print(",");
  Serial.print(Gx); Serial.print(",");
  Serial.print(Gy); Serial.print(",");
  Serial.print(Gz); Serial.print(",");
  Serial.print(AlphaX); Serial.print(",");
  Serial.print(AlphaY); Serial.print(",");
  Serial.print(AlphaZ);Serial.print(",");

  prevGx = Gx;
  prevGy = Gy;
  prevGz = Gz;
  prevTime = currTime;

  sensors_event_t event; 
  adxl.getEvent(&event);
  float Ax_ADXL = event.acceleration.x;
  float Ay_ADXL = event.acceleration.y;
  float Az_ADXL = event.acceleration.z;

  Serial.print("Ax from ADXL: "); Serial.print(Ax_ADXL, 3);
  Serial.print("Ay from ADXL: "); Serial.print(Ay_ADXL, 3);
  Serial.print("Az from ADXL: "); Serial.print(Az_ADXL, 3); Serial.println("");

  delay(10); // 100 Hz IMU logging 
}
