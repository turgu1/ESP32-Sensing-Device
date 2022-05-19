
// ESP32 Sensing Device
// Test reading battery voltage
// Using external FTDI USB interface under Linux
//
// Using the Arduino IDE:
//
// - Tools > Board > "ESP32 Module Dev"
// - Tools > Port > "/dev/ttyUSB0"

#define BAT_ADC_PIN 36
#define BAT_LEVEL_ENABLE_PIN 17

void setup() {
  
  Serial.begin(115200);

  delay(100);

  analogSetPinAttenuation(BAT_ADC_PIN, ADC_6db);
  adcAttachPin(BAT_ADC_PIN);
  
  pinMode(BAT_LEVEL_ENABLE_PIN, OUTPUT);
  digitalWrite(BAT_LEVEL_ENABLE_PIN, LOW);

  delay(1000);
}

float voltage() {

  int value;
  
  digitalWrite(BAT_LEVEL_ENABLE_PIN, HIGH);

  value = analogReadMilliVolts(BAT_ADC_PIN);
  
  digitalWrite(BAT_LEVEL_ENABLE_PIN, LOW);

  // As the batteries may supply more than 3.3v, external resistors 
  // are dividing the voltage in half for ADC reading
  
  return (float(millvalueiVolts) * 0.000895788);
}

void loop() {

  Serial.printf("Input voltage: %5.2f\r\n", voltage());

  delay(10000); // Cycle every 10 seconds
}
