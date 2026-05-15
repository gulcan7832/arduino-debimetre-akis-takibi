volatile int pulseCount = 0;
float flowRate_mLmin = 0.0;
float totalMilliLitres = 0.0;
unsigned long oldTime = 0;
float calibrationFactor = 450.0;

void pulseCounter() {
  pulseCount++;
}

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), pulseCounter, FALLING);
  Serial.println("Debi(ml/dk),Toplam(ml)");
}

void loop() {
  if (millis() - oldTime >= 1000) {
    detachInterrupt(digitalPinToInterrupt(2));
    flowRate_mLmin = (pulseCount * 60.0 * 1000.0) / calibrationFactor;  
    totalMilliLitres += flowRate_mLmin / 60.0;  
    Serial.print(flowRate_mLmin, 2); 
    Serial.print(","); 
    Serial.println(totalMilliLitres, 2);  
    pulseCount = 0;  
    oldTime = millis();  
    attachInterrupt(digitalPinToInterrupt(2), pulseCounter, FALLING);
  }
}
