int soilMoisturePin = 34;  // กำหนด Input Pin ที่จะต่อ Sensor

// Calibration values (to be determined through calibration)
int dryValue = 4095;  // กำหนดค่าความชื้นที่น้อยที่สุด 0% moisture (แห้ง)
int wetValue = 0;     // กำหนดค่าความชื้นที่มากที่สุด  100% moisture (ชื้น)

void setup() {
  Serial.begin(115200);   //ตั้งค่าเริ่มต้นให้ Serial Port
}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin);  //อ่านค่าจาก Sensor
  int moisturePercentage = map(soilMoistureValue, dryValue, wetValue, 0, 100);

  // Print ข้อมูล Sensor วัดความชื้นในดินเป็น percentage
  Serial.print("Soil Moisture Value: ");
  Serial.print(soilMoistureValue);
  Serial.print(" - Moisture Percentage: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  // อ่านค่า Sensor ทุกๆ 1 วินาที
  delay(1000);
}