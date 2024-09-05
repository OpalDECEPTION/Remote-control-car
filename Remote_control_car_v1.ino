int Foreward = 0;
int Backwards = 0;
#define B1IN 3
#define B2IN 4
#define A1IN 5
#define A2IN 6
void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(10, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Foreward = digitalRead(10);
  Backwards = digitalRead(11);
  if (Foreward == 1) {
    digitalWrite(B1IN, HIGH);
    digitalWrite(B2IN, LOW);
    digitalWrite(A1IN, HIGH);
    digitalWrite(A2IN, LOW);
  }  if (Backwards == 1) {
    digitalWrite(B1IN, LOW);
    digitalWrite(B2IN, HIGH);
    digitalWrite(A1IN, LOW);
    digitalWrite(A2IN, HIGH);
  }
  if  ((Backwards == 0) and (Foreward == 0)) {
    digitalWrite(B1IN, LOW);
    digitalWrite(B2IN, LOW);
    digitalWrite(A1IN, LOW);
    digitalWrite(A2IN, LOW);
  }
  Serial.print(Foreward);
    Serial.println(Backwards);

}
