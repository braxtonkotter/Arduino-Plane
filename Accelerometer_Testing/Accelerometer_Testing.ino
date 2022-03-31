#define X_PORT 0
#define Y_PORT 1

int x_value, x_default;
int y_value, y_default;

void setup() {
  // put your setup code here, to run once:
  x_default = analogRead(X_PORT);
  y_default = analogRead(Y_PORT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  x_value = analogRead(X_PORT) - x_default;
  y_value = analogRead(Y_PORT) - y_default;
  Serial.println(String(x_value) + ", " + String(y_value));
}
