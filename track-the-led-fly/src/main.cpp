#include <Arduino.h>
#define EI_ARDUINO_INTERRUPTED_PIN
#include <EnableInterrupt.h>
#include <TimerOne.h>

#define LED_RED 10
#define LED_START 6
#define LED_END 9
#define BTN_START 2
#define T_MIN 1
#define K 4
/*
I led e i bottoni sono memorizzati tramite una struttura circolare doppiamente linkata
*/
typedef struct led
{
  unsigned char ledPin;
  unsigned char btnPin;
  unsigned char number;
  struct led* next;
  struct led* prev;
} LED;

LED* head;
LED* current;

bool gameStarted = false;
int prevts = 0;
/*servono per il fading del led rosso*/
int fadeAmount;
int currIntensity;
int tMin=T_MIN;

void btnPressed(){
  long ts = micros();
  if (ts - prevts > 200000){
    if(gameStarted==false){
      gameStarted=true;
      digitalWrite(LED_RED, LOW);
      Serial.println("Go!");
      /*scelgo un led random da dove partire*/
      int ledStart = random(0,4);
      LED* tmp = head;
      for (int i = 0; i <= ledStart; i++)
      {
        tmp=tmp->next;
      }
      digitalWrite(tmp->ledPin, HIGH);
      Timer1.initialize(1000000);
    }
    prevts = ts;
  }
}

void setup() {
  Serial.begin(9600);
  LED* tmp=NULL;
  /*Creazione della struttura*/
  for (int i = LED_START; i <= LED_END; i++)
  {
    LED* newLed = (LED*) malloc(sizeof(LED));
    newLed->next=NULL;
    newLed->prev=NULL;
    if (head==NULL)
    {
      head = newLed;
    }else
    {
      tmp = head;
      while (tmp->next!=NULL)
      {
        tmp=tmp->next;
      }
      tmp->next=newLed;
      newLed->prev=tmp;
    }
  }

  tmp->next->next=head;
  head->prev=tmp->next;
  /*Definizione dei pin dei led e dei bottoni*/
  tmp = head;
  for (int i = LED_START; i <= LED_END; i++)
  {
    tmp->ledPin=i;
    tmp->number=i-LED_START;
    tmp->btnPin=BTN_START+tmp->number;
    tmp=tmp->next;
  }

  tmp = head;
  for (int i = LED_START; i <= LED_END; i++)
  {
    pinMode(tmp->ledPin, OUTPUT);
    enableInterrupt(tmp->btnPin, btnPressed,RISING);
    tmp=tmp->next;
  }
  
  /*Inizializzione del led rosso*/
  pinMode(LED_RED, OUTPUT);

  fadeAmount=5;
  currIntensity=0;

  randomSeed(analogRead(1));
  Serial.println("Welcome to the Track to Led Fly Game. Press Key T1 to Start");
}

void loop() {
  /*Se il gioco non è iniziato il led rosso pulsa.*/
  if(gameStarted==false){
    analogWrite(LED_RED,currIntensity);
    currIntensity+=fadeAmount;
    if(currIntensity==0 || currIntensity==255){
      fadeAmount=-fadeAmount;
    }
    delay(20);
  } else {
    
  }
  
}
