
int irPin = 2;
int lerIr;
float t;
float ot;
float dt;
void setup() {
  // put your setup code here, to run once:
  pinMode(irPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  //put your main code here, to run repeatedly:
  lerIr = digitalRead(irPin);
  //   Serial.println(lerIr);
  delay(150);
  //   //t = millis();
  //    //Serial.println(t);
  //t=millis();
  if (lerIr == 0) {
    Serial.println("Objeto detectado");
    t = millis();
    while (lerIr == 0) {
      lerIr = digitalRead(irPin);

      delay(50); //necessario para que nao crash o codigo no loop
      ot = millis();
    }
    dt = ((ot - t) / 1000);
    Serial.println(String(dt)+" segundos");
  }

  if (lerIr == 1) {
    Serial.println("Nada");
    //dt = 0;
  }
}
