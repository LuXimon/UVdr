//-- MOTEUR A --
int ENA = 9; //Connecté à Arduino pin 9(sortie PWM)
int IN1 = 4; //Connecté à Arduino pin 4
int IN2 = 5; //Connecté à Arduino pin 5
//-- MOTEUR B --
int ENB = 10; //Connecté à Arduino pin 10(Sortie PWM)
int IN3 = 6; //Connecté à Arduino pin 6
int IN4 = 7; //Connecté à Arduino pin 7
#include <Adafruit_NeoPixel.h>
//#include <Servo.h>
#include <NewPing.h>

int trig=15;
int echo=8;
int lecture_echo=0;

// Parameter 32 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
int X = 31;
//Servo myServo;
byte servoPin = 14;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(X, 11, NEO_GRB + NEO_KHZ800);

#include<SoftwareSerial.h>
#define RX 12
#define TX 3
SoftwareSerial Blue(RX,TX);
char Data;
int PWM = 128;

void setup() {
  NewPing sonar(trig,echo);
  Serial.begin(9600);
  delay(500);
  Serial.println("Bonjour-Pret pour les commandes AT");
  Blue.begin(9600);
  delay(500);
  pinMode(ENA, OUTPUT); // Configurer
  pinMode(ENB, OUTPUT); // les broches
  pinMode(IN1, OUTPUT); // comme sortie
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(10, INPUT);
  //pinMode(11, OUTPUT);
  //pinMode(3,INPUT);
  digitalWrite(ENA, LOW); // Moteur A - Ne pas tourner
  digitalWrite(ENB, LOW); // Moteur B - Ne pas tourner
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  myServo.attach(servoPin);
  myServo.writeMicroseconds(360);
  myServo.write(100);
  strip.begin();
//  pinMode(9, OUTPUT);
//  pinMode(11, OUTPUT);


  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  


  strip.show(); // Initialise toute les led à 'off'
  // PARAGRAPHE ALLUMAGE DES LED EN ROUGE POUR PREVENIR DE L'ARRIVEE DES UV
  for (int i = 0; i < X; i++ ) {
    strip.setPixelColor(i, 255, 0, 0);
    delay(200);
    strip.show();
  }
  Blue.begin(9600);
}

void loop() {

  // PARAGRAPHE ALLUMAGE DES LED EN VIOLET
  for (int i = 0; i < X; i++ ) { // On fait une boucle pour définir la couleur de chaque led
    //setPixelColor(n° de led, Rouge, Vert, Bleu)
    strip.setPixelColor(i, 128, 0, 128);
  }
  strip.show(); // on affiche
  myServo.attach(servoPin);
  myServo.writeMicroseconds(360);
  myServo.write(100);
  if (Blue.available()){
    Data=Blue.read();
    delay(20);
    Serial.println(Data);
    if(Data='A'){
      analogWrite(ENB ,255);
    }
    if(Data='a'){
      analogWrite(ENB ,0);
    }}

  /*if (sonar.ping_cm()<10){
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  delay(60);
  digitalWrite(IN2, LOW);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
  delay(60);
  analogWrite(ENA,255);
  analogWrite(ENB,255);
  delay(500);
   digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA,255);
  analogWrite(ENB,0);
  delay(500);
  }
  if (sonar.ping_cm()>10){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA,255);
  analogWrite(ENB,255);
  
  } 
if (Blue.available()){
    Data=Blue.read();
    if(Data='A'){
      PWM=Blue.parseInt();
      Serial.println(PWM);
      analogWrite(ENA,PWM);
    }
    }*/
  }
 
