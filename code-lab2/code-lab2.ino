const int PIN = A0;
const float V_ref = 5.0;
const float V_zero = 2.500;       // V at 0 g (after potentiometer zeroing)
const float sensitivity = 0.001101; // V/g

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(PIN);
  float voltage = raw * V_ref / 1023.0;
  float mass_g  = (voltage - V_zero) / sensitivity;
  
  Serial.print("Voltage:");
  Serial.print(voltage);
  Serial.print(",mass:");
  Serial.println(mass_g);

  delay(100);
}