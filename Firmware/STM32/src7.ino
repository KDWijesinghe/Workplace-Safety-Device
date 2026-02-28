#include <Wire.h>
#include <SoftwareSerial.h>

/* ------------------------- Constraints ---------------------------*/
const int LED = PA3;        // Active HIGH
const int BUZZ = PA7;       // Active HIGH
const int BTN = PA5;        // Active HIGH
const int HEATER_ACT = PB15;// Active HIGH
const int GAS_SENSOR = PA4;
const int GAS_THRESHOLD = 500;
const int WAIT_TIME_BTN_PRESS = 3; // in seconds
const uint8_t MPU6050_ADDR = 0x68;
const int IMU_SCL = PB6;
const int IMU_SDA = PB7;

#define A9G Serial1  // Use hardware UART
HardwareSerial Serial1(PA10, PA9);



const String PHONE_NUMBER = "+94785846619";
/* -----------------------------------------------------------------*/

// Function declarations
void user_init();
void eventloop();
int detect_gas();
void alarm_off();
void alarm_on();
int16_t readWord(uint8_t reg);
int detect_fall();
int detect_button_press(int time);
String getGPSInfo();
void sendSMS(String phone, String message);
void sendCommand(String command);

void setup(){
  user_init();
}

void loop(){
  eventloop();
}

void eventloop(){
  static int GAS_DETECTED = 0;
  alarm_off();

  // -------- FALL ----------- //
  if (detect_fall()) {
    alarm_on();
    int BTN_PRESS = detect_button_press(WAIT_TIME_BTN_PRESS);
    if (BTN_PRESS) {
      alarm_off();
      return;
    } else {
      //digitalWrite(HEATER_ACT, LOW);
      // send message here (if needed in future)
      sendSMS(PHONE_NUMBER, "FALL DETECTED");
    }
  }

  // --------- GAS ----------- //
  if (detect_gas()) {
    if (!GAS_DETECTED) {
      alarm_on();
      // send message here (if needed in future)
      sendSMS(PHONE_NUMBER, "GAS LEAK");
      delay(5000);
      GAS_DETECTED = 1;
    }
  } else {
    GAS_DETECTED = 0;
  }
}

void user_init(){
  // ------ UI ------ //
  pinMode(LED, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(BTN, INPUT);

  // ------ Gas sensor ------ //
  pinMode(HEATER_ACT, OUTPUT);
  digitalWrite(HEATER_ACT, HIGH);
  pinMode(GAS_SENSOR, INPUT);

  // ------ IMU ------ //
  Wire.setSCL(IMU_SCL);
  Wire.setSDA(IMU_SDA);
  Wire.begin();
  // Wake up MPU6050
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B); // Power management register
  Wire.write(0);    // Wake up device
  Wire.endTransmission();

  // ------ A9G ------ //
  A9G.begin(9600);
  delay(5000); // wait for the module to boot-up
  sendCommand("AT");
  delay(1000);
  sendCommand("AT+CMGF=1"); // Set SMS text mode
  delay(1000);
  sendCommand("AT+CGPS=1,1"); // Turn on GPS
  delay(2000);
}
int detect_gas(){
  return analogRead(GAS_SENSOR) > GAS_THRESHOLD;
}
int16_t readWord(uint8_t reg) {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 2);
  return (Wire.read() << 8) | Wire.read();
}
int detect_fall(){
  int16_t accX = readWord(0x3B);
  int16_t accY = readWord(0x3D);
  int16_t accZ = readWord(0x3F);
  return abs(accX) > 31576 || abs(accY) > 31576 || abs(accZ) > 31576;
}
int detect_button_press(int time) {
  unsigned long start = millis();
  unsigned long duration = time * 1000;
  while (millis() - start < duration) {
    if (digitalRead(BTN)) {
      return 1;
    }
    delay(10);
  }
  return 0;
}
void alarm_on(){
  digitalWrite(LED, HIGH);
  digitalWrite(BUZZ, HIGH);
}
void alarm_off(){
  digitalWrite(LED, LOW);
  digitalWrite(BUZZ, LOW);
}
void sendCommand(String command) {
  A9G.println(command);
  delay(500);
}
void sendSMS(String phone, String message) {
  A9G.println("AT+CMGF=1"); // Text mode
  delay(1000);

  A9G.print("AT+CMGS=\"");
  A9G.print(phone);
  A9G.println("\"");
  delay(1000);

  A9G.print(message);
  delay(500);

  A9G.write(26); // Ctrl+Z to send
  Serial.println("SMS sent.");
  delay(1000); // Wait to ensure message sent
}
String getGPSInfo() {
  A9G.println("AT+CGPSINFO");
  delay(2000);

  String response = "";
  while (A9G.available()) {
    char c = A9G.read();
    response += c;
  }

  // Clean response (optional parsing)
  if (response.indexOf("+CGPSINFO:") != -1) {
    int startIndex = response.indexOf("+CGPSINFO:") + 11;
    int endIndex = response.indexOf("\r\n", startIndex);
    String gpsInfo = response.substring(startIndex, endIndex);
    gpsInfo.trim();

    if (gpsInfo.length() < 5) {
      return "GPS not fixed yet.";
    } else {
      return "Location: " + gpsInfo;
    }
  } else {
    return "No GPS data.";
  }
}