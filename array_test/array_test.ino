int array[20];
int bS = 0;

void setup() {
  Serial.begin(9600);

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
}

void loop() {
  _signal();
  _forward();
  _print();
  delay(1000);
}

void _signal() {
  if (digitalRead(4) == LOW && bS == 0) {
    bS = 1;
    array[10] = 1;
    array[11] = 1;
    array[12] = 1;
    array[13] = 1;
    array[14] = 1;
  } else if (digitalRead(4) == HIGH && bS == 1) {
    bS = 0;
  }
}

void _print() {
  int i;
  for (i = 0; i < 19; i++) {
    Serial.print(array[i]);
  }
  Serial.println(array[19]);
}

void _forward() {
  int i;
  for (i = 0; i < 19; i++) {
    array[i] = array[i + 1];
  }
  array[19] = 0;
}
