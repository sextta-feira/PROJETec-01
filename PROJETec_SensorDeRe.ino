#include <LiquidCrystal_I2C.h> //biblioteca do display

#define trigPin 7 // Declara constante trigPin
#define echoPin 8 // Declara constante como echoPin
#define Buzzer 13 // Inicializa buzzer no pino 13

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Define os pinos que serão utilizados para ligar o display

float distancia = 0;
int bip = 0;

void setup() 
{
  Serial.begin(9600);
 
  //Configurações do buzzer
  pinMode(Buzzer, OUTPUT);  //Pino do buzzer comom saida
  pinMode(trigPin, OUTPUT); //Pino do gatilho/disparo do som  como saida
  pinMode(echoPin, INPUT);   //Pino do retorno do som como entrada
  
  //Configurações do LCD
  lcd.begin(16, 2);  //Informa as colunas e linhas do lcd
  lcd.init();        //Inicia o lcd
  lcd.clear();      //Limpa o Led lcd
  lcd.setCursor(0,0);   //Seleciona a linha 05 da primeira coluna do LED
  lcd.print("---- RAITEC ----");  //Escreve o nome RAITec no lcd
}

void loop() {

  //Configurar o sensor para receber a distância 
  digitalWrite(Buzzer, LOW);
  digitalWrite(trigPin, HIGH);  //Dispara um pulso sonoro
  delayMicroseconds(10);      //Continua a disparar por 10 microsegundos
  digitalWrite(trigPin,LOW);   //Para o pulso
  distancia = pulseIn (echoPin, HIGH); //Recebe o tempo que o tempo de retorno do som   

  //Calcularemos a distância real do obstâculo
  distancia = distancia / 58;   
  //Calculo do DATASHEET levando em consideração a velocidade do som, o tempo de ida e volta e a conversão para CM
  
  //Configuração do SERIAL do Arduino para Debug
  Serial.print("Distancia: ");
  Serial.print(distancia);  //Escreve a distancia no serial do arduino
  Serial.println("cm");   

  //Configuração para printar a distância no LCD
  if (distancia < 1000){
    lcd.setCursor(0,1);
    lcd.print("Dist: ");
    lcd.setCursor(7,1);
    lcd.print(distancia); //Escreve o que está em 'distancia' no LCD
    lcd.print(" cm");
  }

  //Configura a saída do BUZZER quanto mais perto ficar da parede 
  if(distancia<100 && distancia>10){
    digitalWrite(Buzzer, HIGH); //Liga o Buzzer
    bip = distancia*10;   //Formula para calcular a frequência que o buzzer apita
    delay(200);
    digitalWrite(Buzzer, LOW);  //Desliga o Buzzer
    delay(bip);
  }
  else if(distancia<10){
    digitalWrite(Buzzer, HIGH);
    delay(100);
  }
}