// ACHEI BOM O APLICATIVO "BLUETOOTH SPP"

// Bleutooth
#include <IRremote.h>                       // Biblioteca IRemote
#include <SoftwareSerial.h>
#define RX 8
#define TX 9
int RELE = 5;
SoftwareSerial btSerial(RX, TX); // RX, TX

int key = 5;
char val = 0;

void bluet ();
void contr ();

//Controle

int RECV_PIN = 11;   // Arduino pino D11 conectado no Receptor IR
IRrecv irrecv(RECV_PIN);   // criando a instância

decode_results results;   // declarando os resultados
int rele = 5;
int vcc = 12;


void setup()
{
  //Bluetooth
  Serial.begin(9600);
  pinMode(key, OUTPUT); // Define o pino 5 como saída
  digitalWrite (key, LOW); // Inicia o RELE desligado
  btSerial.begin(9600); // Inicializa a serial via software (Onde está conectado o nosso módulo bluetooth)
  // pinMode(2, OUTPUT); // Defina a porta 2 como saída
  // digitalWrite(2, HIGH); // Deixa a porta 2 como nivel lógico alto para alimentar o RELE (5V)


  //Controle
  Serial.begin(9600);   // Monitor velocidade 9600 bps
  irrecv.enableIRIn();   // Inicializa a recepção de códigos
  pinMode(rele, OUTPUT);
  pinMode(vcc, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(vcc, HIGH);
  digitalWrite(rele, LOW);
  digitalWrite(4, LOW);
  digitalWrite(6, HIGH);
}

void loop() {

  bluet();
  contr();

}

void bluet () {

  static String btComando;
  static bool releStatus = LOW;

  while (btSerial.available()) {
    char comandoRec = btSerial.read();
    btComando += char( comandoRec );
    Serial.print(comandoRec);

    if (comandoRec == ';') {
      if (btComando == "B1;") {
        releStatus = !releStatus;
        digitalWrite(RELE, releStatus);
        delay(500);
        releStatus = !releStatus;
        digitalWrite(RELE, releStatus);

      }
      btComando = "";
    }
  }
}

void contr() {

  digitalWrite(rele, LOW);
  results.value = 0; // Se nenhum dado for recebido, continua em 0
  if (irrecv.decode(&results))   // se algum código for recebido
  {
    Serial.println(results.value, HEX);   // imprime o HEX Code
    irrecv.resume();   // reinicializa o receptor
    delay(10);   // atraso de 10 ms
  }
  if (results.value == 0xFF9867) {
    digitalWrite(rele, HIGH);
    delay(500);
    digitalWrite(rele, LOW);
  }

}

