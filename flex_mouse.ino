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
    float x_angle = getAngle(X_FLEX_PIN, "X");
    float y_angle = getAngle(Y_FLEX_PIN, "Y");
  }
  Serial.println();
  delay(1000);
}

int getAngle(int PIN, String axis) {
  int flexADC = analogRead(PIN);
  float flexV = flexADC* VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
  Serial.println(String(axis) + "_RESISTANCE : " + String(flexR) + " ohms");
  Serial.println(String(axis) + "_Bend : " + String(angle) + " degrees");
  return angle;
}

