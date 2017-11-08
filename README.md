# Projeto_fisica
**Projeto com ESP para lab de fisica experimental**

# Primeiro dia:
## Como fazer um led acender via WIFI com ESP8266 NodeMcu
### Teste 1(primeiro código usando ESP para “piscar um led”)
![ESP8266](https://cdn.evbuc.com/eventlogos/228809435/esplayout.png "ESP826 NodeMcu")
No primeiro passo criamos um sketch na ide do arduino para fazer um led piscasse continuamente em um loop, entretanto antes de criar a parte lógica do processo foi necessário tornar a ide do arduino compatível com a placa do ESP8266.
Para isso, seguimos o seguinte caminho:([Tutorial que seguimos](https://www.filipeflop.com/blog/programar-nodemcu-com-ide-arduino/))
1. Clicamos em "Arquivo" na ide do arduino
2. Clicamos no campo "Preferencias"
3. Na nova tela copiamos a url:"http://arduino.esp8266.com/stable/package_esp8266com_index.json" no campo de texto "URLs Adicionais para Gerenciadores de Placas:"
4. Apertamos no botão "OK"
5. E seguida clicamos em "Ferramentas"
6. Colocamos o mouse sobre a opção "Placa:" o que exibiu um menu na lateral 
7. Clicamos em "Gerenciador de Placas"
8. Na nova tela procuramos a opção "esp8266 by ESP8266 Comunity"
9. Clicamos em "Instalar" na area da opção acima
10. Após a instalação clicamos em "Ferramentas"
11. Colocamos o mouse sobre a opção "Placa:"
12. Selecionamos opção de placa: "NodeMCU 1.0(ESP-12E Module)" 

Após essa instalação a ide do arduino já pode ser utilizada para programar o "ESP". Conectamos a placa na porta USB utilizando o cabo de um carregador de celular, O NodeMcu acendeu um led de cor azul na própria placa.Antes de programar, selecionamos a "Porta" onde a placa estava conectada seguindo o caminho:
1. Clicamos em "Ferramentas"
2. Posicionamos om mouse sobre a opção "Porta"
3. Clicamos sobre a porta "COM3"(o número após o "COM" varia a depender de qual porta "USB" a placa está conectada)

Caso a opção "Porta" esteja "desabilitada", significa que o computador não está reconhecendo a placa. Um dos motivos disso pode ser uma má conexão do "ESP" então pode-se tentar reconectar a placa, ou ainda, há a possibilidade do computador estar com um drive desatualizado ou em mal funcionamento. Nesse segundo caso, se faz necessário procurar o drive em mal funcionamento no gerenciador de dispositivos e em seguida procurar uma correção, ou atualização, dele na internet.
Após toda a adaptação da ide do arduino para programar o ESP8266, iniciamos a construção do código(.ino) para piscar um led.
```ino
    #include <dummy.h>
    void setup(){
    //Aqui definimos as "funções" do pinos do "ESP" 
    }
    
    void loop(){
    //Aqui definimos o que o programa irá excutar de forma contínua.
    }
```
Inicialmente definimos as funções "setup()" e "loop()" que são basicas para a construção de projetos utilizando a linguagem do arduino. O "#include <dummy.h>" serve apenas para silenciar os avisos de perigo que a ide do arduino.
```ino
    void setup(){
        pinMode(2,OUTPUT);
    }
```
Adicionamos o pinMode("x","y") dentro da função "setup()" para selecionar um dos pinos da placa "ESP" definimos ele como entrada ou saida, o "x" indica o numero do pino(o numero é referente ao numero do pino GPIO do ESP8266) e o "y" determina se o pino será de "Entrada" ou "Saida" de informações.
```ino
    void loop(){
        digitalWrite(2,HIGH);
        delay(1000);
        digitalWrite(2,LOW);
        delay(1000);
    }
```
Adicionamos digitalWrite("i","j") dentro da função "loop()" para definir o que o pino irá fazer, ou seja qual será o "estado" do pino no momento de execução da linha de código. o "i" representa o numero do pino digital que se deseja utilizar, e o "j" representa o "estado" que se deseja atribuir a ele, no caso do exemplo "HIGH" para criar uma diferença de potencial(ddp) e "LOW" para manter a saida sem uma ddp. Adicionamos delay("m") para determinar o tempo em milissegundos que o pino permanecerá naquele estado durante a execução do programa. o "m" se trata de quantos milissegundos se deseja manter o pino naquele estado.
Portanto o código final que utilizamos para fazer um led piscar com ESP8266 NodeMcu foi:
```ino
#include <dummy.h>

void setup() {
    pinMode(2,OUTPUT);
} 
void loop() {
    digitalWrite(2,HIGH);
    delay(2000);
    digitalWrite(2,LOW);
    delay(1000);
}
```
Na parte física, encaixamos a placa do ESP em uma _protoboard_,e conectamos um resistor de **330 Ohms** ao pino "GPIO2" em série com um led vermelho, e a outra extremidade do led conectamos ao pino "GND" do ESP8266 NodeMcu.
Para compilar o código, apertamos em "Verificar" na Ide do Arduino e em seguida carregamos o código no ESP clicando em "Carregar" na Ide do Arduino.Ao carregar o código, o circuito não deve estar fechado no "GND", caso contrário pode aparecer a mensagem de erro de carregamento "warning: espcomm_sync failedv...".Quando o código terminou de ser carregado para o NodeMcu, conectamos o "GND" novamente e o led ficou piscando continuamente, passando 2 segundos ligado e 1 segundo desligado.

###teste 2(Usar uma págima web para ligar o led via WI-FI)
```ino
#include <ESP8266WiFi.h>

const char* ssid = "Sua_Rede";
//Nessa variável definimos o nome da rede em que o ESP vai se conectar
const char* password = "A_Senha_Da_Rede";
//Nessa Variável informamos a senha da rede  
WiFiServer server(80);//Cria um servidor na porta 80

void setup() {
  Serial.begin(115200);//informa a velocidade do monitor serial
  delay(10);

  // inicializa o pino "GPIO2" definindo ele como saida
  pinMode(2, OUTPUT);
  //O estado inicial do pino é sem gerar uma tensão
  digitalWrite(2, 0);
  
  // Exibe na tela serial a conexão com a rede
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
//inicializa a conexão com a rede WI-FI
  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
/*este while fica verificando o status da conexão e fica iprimindo um "." na 
tela serial enquanto o ESP não estiver conectado,retornando qualitativamente o 
status da conexão enquanto carrega para que o usuario tenha algum feedback do
processo*/
  }
/*Quando o ESP conseguir se conectar à rede o monitor serial dá um feedack da conexão bem sucedida*/
  Serial.println("");
  Serial.println("Wi-Fi conectado");
    
  // Esse código inicializa o ESP como servidor
  server.begin();
  Serial.println("Servidor inicializado");
  Serial.println(WiFi.localIP());//Informa o ip do ESP na rede
}

void loop() {
  //verifica o status do servidor
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
//Verifica se há algum novo usuário
  Serial.println("Novo usuário");
  while(!client.available()){
    delay(1);
  }
//informa a requisição vindo do Browser
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
/*inicializa uma variável de texto que armazena a estrutura da página HTML que o servidor irá enviar ao Browser*/
  String buf = "";
/*Adiciona a página HTML acrescentando os elementos à variável "buf" por partes até que ela armazene toda a página*/
  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  buf += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  buf += "<title>ESP8266 Web Server</title>";
  buf += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:80%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;}";
  buf+="</style>";
  buf += "</head>";
  buf += "<h3>ESP8266 Web Server - System Logs</h3>";
/*Abaixo estão sendo adicionados dois botões à página, eles serão responsáveis pelo "Acender" e "Apagar" do led chamando um função externa "?function=led2_on" e "?function=led2_off" que não precisam estar definidas nesse código especificamente*/
  buf += "<p>GPIO2 
  <a href=\"?function=led2_on\"><button>Acender</button></a>&nbsp;
  <a href=\"?function=led2_off\"><button>Apagar</button></a></p>";

  buf += "</html>\n";
//Exibe a página para o usuário após ela ser carregada totalmente
  client.print(buf);
  client.flush();
/*verifica o retorno da funçôes e identifica a requisição para ligar ou desligar o led*/ 
  if (req.indexOf("led2_on") != -1)
    digitalWrite(2, 1);
  else if (req.indexOf("led2_off") != -1)
    digitalWrite(2, 0);
  else {//faz um tratamento de exceções a uma requisição inválida
    Serial.println("requisição inválida");
    client.stop();
  }
  Serial.println("Client disonnected");
}
```


