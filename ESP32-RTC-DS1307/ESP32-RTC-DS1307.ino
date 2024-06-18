//ส่วนของการเรียกใช้ Library
#include <Wire.h>
#include <RTClib.h>

#define LED_BUILTIN 2 //LED on board

//สร้าง Object RTC
RTC_DS1307 rtc;
//ตัวแปรเก็บสถานะของ RTC
bool isRtcOk = false;

//ตั้งตค่าวันที่และเวลา
void setDate(int year, int month, int day);
void setTime(int hour, int minute, int second);
void setDateAndTime(int year, int month, int day, int hour, int minute, int second);
//Parser ข้อความที่รับเข้ามาทาง Comport
void processCommand(String command);
//อ่านค่า RTC ปัจจุบัน
void readRtc();

void setup() {
  Serial.begin(115200);
  //LED แสดงสถานะของการรับข้อมูลการตั้งค่าวันที่และเวลาผ่าน Comport
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Wire.begin();

  if (!rtc.begin()) {
    Serial.println("ไม่พบ RTC โมดูล");
  } else {
    isRtcOk = true;
    if (!rtc.isrunning()) {
      Serial.println("RTC ไม่ทำงาน ต้องตั้งค่าวันที่เวลาก่อน");
      //ตั้งค่าโดยใช้เวลาของเครื่องคอมพิวเตอร์เมื่อเวลา compiled
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      //ตั้งค่าโดยกำหนดค่าด้วยตนเอง
      // rtc.adjust(DateTime(2024, 6, 15, 10, 11, 12)); // ปี, เดือน, วัน, ชั่งโมง, นาที, วินาที
    }
  }
}

void loop() {
  //อ่านข้อมูล การตั้งค่าวันที่และเวลาผ่าน Comport
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove any extra whitespace
    processCommand(input);
  }

  //อ่านค่าเวลา ณ ปัจจุบัน
  readRtc();
}

//รูปแบบการรับข้อมูล
//D 2024-06-15  วันที่
//T 14:30:00    เวลา
//DT 2024-06-15 14:30:00  วันที่และเวลา
void processCommand(String command) {
  int year, month, day, hour, minute, second;
  String buffer;
  if (command.startsWith("D ")) {
    buffer = command.substring(2);
    sscanf(buffer.c_str(), "%d-%d-%d", &year, &month, &day);
    setDate(year,month,day);
  } else if (command.startsWith("T ")) {
    buffer = command.substring(2);
    sscanf(buffer.c_str(), "%d:%d:%d", &hour, &minute, &second);
    setTime(hour,minute,second);
  } else if (command.startsWith("DT ")) {
    buffer = command.substring(3);
    sscanf(buffer.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    setDateAndTime(year,month,day,hour,minute,second);
  } else {
    Serial.println("คำสั่ง ไม่ถูกต้อง");
  }
}

void readRtc() {
  if (!isRtcOk) return;
  // อ่านค่าเวลาทุก ๆ 1 วินาที
  static unsigned long lastMsg = 0;
  unsigned long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;

    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('-');
    Serial.print(now.month(), DEC);
    Serial.print('-');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  }
}

void setDate(int year, int month, int day) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);

  //ดึงค่าเวลาปัจจุบัน
  DateTime now = rtc.now();
  //ตั้งค่าใหม่เฉพาะวันที่
  rtc.adjust(DateTime(year, month, day, now.hour(), now.minute(), now.second()));
  Serial.println("ตั้งค่าวันที่");
}

void setTime(int hour, int minute, int second) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);

  //ดึงค่าเวลาปัจจุบัน
  DateTime now = rtc.now();
  //ตั้งค่าใหม่เฉพาะวันที่
  rtc.adjust(DateTime(now.year(), now.month(), now.day(), hour, minute, second));
  Serial.println("ตั้งค่าเวลา");
}

void setDateAndTime(int year, int month, int day, int hour, int minute, int second) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);

  //ตั้งค่าใหม่ทั้งวันที่และเวลา
  rtc.adjust(DateTime(year, month, day, hour, minute, second));
  Serial.println("ตั้งค่าวันที่และเวลา");
}

