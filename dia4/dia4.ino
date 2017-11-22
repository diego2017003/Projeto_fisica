int irPin = 2;//pino gpio conectado ao leitor
int lerIr;//armazena o valor da entrada
float Tt = 1;
//int situacao = 0;
float Tp = 0;
float Tb = 0;
float vel = 0;
float dist = 115;
float t;//tempo captado quando o leitor identifica linha branca
float ot;//tempo subsequente à leitura do primeiro tempo na saida da linha branca
float dt;//diferenca de tempo entre a entrada na linha
float tp;//tempo captado quando inicia uma linha preta
float otp;//tempo captado quando sai da linha preta
float dtp;//diferencial entre a entrada e a saida da linha preta
int cont = 0;//contador de linhas brancas
//float tempoNada[100];//vetor que armazena tempos em linhas pretas
float tempos[100];//vetor que armazena as linhas
int contPretas = 0;//contador de linhas pretas
String MostrarVetor = "";//texto para exibir os tempos
void setup() {
  // put your setup code here, to run o2nce:
  pinMode(irPin, INPUT);//set do pino 2 como entrada de informacoes
  Serial.begin(9600);
}

void loop() {
  //put your main code here, to run repeatedly:
  lerIr = digitalRead(irPin);//identificar os dados de tempo
  //   Serial.println(lerIr);
  // delay(5);
  //   //t = millis();
  //    //Serial.println(t);
  //t=millis();
  if (lerIr == 0) {//identifica linha branca
    Serial.println("Objeto detectado");//informa que chegou uma linha branac
    t = millis();//recebe o tempo de execucao do codigo em que o objeto foi identificado
    while (lerIr == 0) {
      lerIr = digitalRead(irPin);//atualiza o status de leitura do pino

      delay(1); //necessario para que nao crash o codigo no loop
      ot = millis();//recebe o valor de tempo final que antes donleitor sair da linha branca
      dt = (ot - t);
      /*if(dt>5000){
        //situacao = 2;
        }*/
    }
    dt = (ot - t); //recebe a diferenca entre o momento em que entrou na linha branca e o momento que saiu
    //Serial.println(String(cont));
    Serial.println(String(dt) + " milisegundos");
    if (dt > 5000) {
      Tt = Tp + Tb;
      vel = dist / Tt;
      Serial.println(String(vel) + " m/s");
    }
   
    else if (cont < 100) {
      //tempos[cont] = dt;
      Tb = Tb + dt;
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
      //tempoNada[contPretas] = dt;
      Tp = Tp + dtp;
      contPretas++;
      //Serial.println(contPretas);
    }

    /*else if (contPretas == 100) {
      /*for (int i = 0; i < contPretas; i = i + 1) {
        MostrarVetor = "Pretas Linha " + String(i + 1) + " " + String(tempoNada[i]);
        Serial.println(MostrarVetor);//imprime no serial a colecao de tempos em linhas pretas
      }*/
  }

}

