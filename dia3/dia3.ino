int irPin = 2;
int lerIr;
float t;
float ot;
float dt;
float tp;
float otp;
float dtp;
int cont = 0;
float tempoNada[100];
float tempos[100];
int contPretas = 0;
String MostrarVetor = "";
void setup() {
  // put your setup code here, to run once:
  pinMode(irPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  //put your main code here, to run repeatedly:
  lerIr = digitalRead(irPin);
  //   Serial.println(lerIr);
  // delay(5);
  //   //t = millis();
  //    //Serial.println(t);
  //t=millis();
  if (lerIr == 0) {
    Serial.println("Objeto detectado");
    t = millis();
    while (lerIr == 0) {
      lerIr = digitalRead(irPin);

      delay(10); //necessario para que nao crash o codigo no loop
      ot = millis();
    }
    dt = (ot - t);
    //Serial.println(String(cont));
    Serial.println(String(dt) + " milisegundos");
    if (cont < 100) {
      tempos[cont] = dt;
      cont++;
    }
    /* else if(cont == 100){
       for(int i = 0;i<cont;i=i+1){
         MostrarVetor = "Linha "+String(i+1)+" "+String(tempos[i]);
         Serial.println(MostrarVetor);
         }

       }*/
  }
  if (lerIr == 1) {
    Serial.println("Nada");
    tp = millis();
    while (lerIr == 1) {
      lerIr = digitalRead(irPin);
      delay(10);
      otp = millis();
    }
    dtp = (otp - tp);
    if ((dtp < 350) && (contPretas < 100)) {
      tempoNada[contPretas] = dt;
      contPretas++;
      Serial.println(contPretas);
    }

    else if (contPretas == 100) {
      for (int i = 0; i < contPretas; i = i + 1) {
        MostrarVetor = "Pretas Linha " + String(i + 1) + " " + String(tempoNada[i]);
        Serial.println(MostrarVetor);
      }
    }

  }
}
