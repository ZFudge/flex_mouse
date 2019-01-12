const int X_FLEX_PIN = A0;
const int Y_FLEX_PIN = A1;
const float VCC = 4.98; // 5V power supply
const float R_DIV = 51000.0; // resistor ratings
const float STRAIGHT_RESISTANCE = 25000; // 37300.0; // resistance when straight
const float BEND_RESISTANCE = 60000.0; // resistance at 90 deg
const int activate_movement_touchstrip = A2; // capacitive touch copper strip
const int click_touchstrip = A3; // capacitive click

void setup() {
  Serial.begin(9600);
  pinMode(X_FLEX_PIN, INPUT);
  pinMode(Y_FLEX_PIN, INPUT);
  pinMode(click_touchstrip, INPUT);
}

void loop() {
  int activate_movement = analogRead(activate_movement_touchstrip);
  int click = analogRead(click_touchstrip);
  Serial.println("Activate Movement: " + String(activate_movement));
  Serial.println("Click: " + String(click));
  if (activate_movement < 150) {
    // X
    int x_flexADC = analogRead(X_FLEX_PIN);
    float x_flexV = x_flexADC* VCC / 1023.0;
    float x_flexR = R_DIV * (VCC / x_flexV - 1.0);
    float x_angle = map(x_flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
    int y_flexADC = analogRead(Y_FLEX_PIN);
    // Y
    float y_flexV = y_flexADC* VCC / 1023.0;
    float y_flexR = R_DIV * (VCC / y_flexV - 1.0);
    float y_angle = map(y_flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
    Serial.println("X_Resistance : " + String(x_flexR) + " ohms");
    Serial.println("X_Bend : " + String(x_angle) + " degrees");
    Serial.println("Y_Resistance: " + String(y_flexR) + " ohms");
    Serial.println("Y_Bend: " + String(y_angle) + " degrees");
  }
  Serial.println();
  delay(1000);
}

