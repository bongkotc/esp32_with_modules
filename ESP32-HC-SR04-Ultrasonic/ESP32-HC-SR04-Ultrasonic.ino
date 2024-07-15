#define TRIG_PIN 5  //กำหนดขาที่จะส่งสัญญาณออก
#define ECHO_PIN 18 //กำหนดขาที่จะรับสัญญาณเข้า

void setup() {
  Serial.begin(115200);//ตั้งค่าการสื่อสาร Serail
  pinMode(TRIG_PIN, OUTPUT);//ตั้งค่า TRIG_PIN เป็น Output
  pinMode(ECHO_PIN, INPUT); //ตั้งค่า ECHO_PIN เป็น Input
}

void loop() {
  
  digitalWrite(TRIG_PIN, LOW);//ตั้งค่าเริ่มต้นให้ TRIG_PIN เป็น Low
  delayMicroseconds(2);//หน่วงเวลา 2 microseconds
  
  //High TRIG_PIN เป็นเวลา 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);//ตั้งค่าให้ TRIG_PIN เป็น High
  delayMicroseconds(10);//หน่วงเวลา 10 microseconds ในการ Trigger
  digitalWrite(TRIG_PIN, LOW);//ตั้งค่าให้ TRIG_PIN เป็น Low
  
  //อ่านค่าจาก ECHO_PIN, ข้อมูลที่รับเข้ามามีหน่วยเป็น microsecond 
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  //การคำนวณระยะทาง
  float distance = duration * 0.034 / 2;//0.034 คือ ความเร็วที่เสียงใช้เดินทาง เซ็นติเมตร/ไมโครวินาที
  
  // Print ข้อมูลระยะทาง หน่วงเป็น cm
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(1000); // หน่วงเวลา 1 วินาที ก่อนทำรอบใหม่
}