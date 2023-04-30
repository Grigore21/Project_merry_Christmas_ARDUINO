#include "pitches.h"
#include <Wire.h>
//#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

int button_pin = 7;
int stand_by;
int wait_at_start = 50;
unsigned long last_time_wait = 0;
int last_signal = LOW;
int repeat = 6;
int buzzerPin = 11;
int songs [6][50]={{
  // Jingle Bells
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
},{
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
},{
  // We wish you a merry Christmas
  NOTE_B3, 
  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_E4,
  NOTE_F4
},{
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
},{
  // Santa Claus is coming to town
  NOTE_G4,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
  NOTE_D4, NOTE_F4, NOTE_B3,
  NOTE_C4
},{
  8,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 2,
  4, 4, 4, 4,
  4, 2, 4,
  1
}};


LiquidCrystal_I2C lcd(0x27,16,2); // 0x27 - adresa

String mesaje[] = { //afiseaza 5 mesaje consecuitv pe pozitia 0,0 la LCD, delay de 150 ms
  "     FACIEE     ",
  "     Ureaza     ",
  "    Sarbatori   ",
  "    Fericite    ",
  "  Studentilor ! "
};

int numeroNote = 26;
#define trigPin 13
#define echoPin 12
int led[] = {2,3,4,5};
int signal = LOW;
 
Servo myservo;
 
int pos = 0;
int w = 0;

// the setup routine runs once when you press reset:
void setup() { 
  pinMode(button_pin, INPUT);
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("     FACIEE     ");
  lcd.setCursor(0, 1);
  lcd.print(" Apasa pe buton ");
  myservo.attach(8);
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for(int x = 0; x<4; x++){
  pinMode(led[x], OUTPUT);   
  } 
}

// the loop routine runs over and over again forever:
void loop() {
    while(signal == LOW){
     signal = digitalRead(button_pin);
     if(signal == HIGH){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Proiect Craciun");
    lcd.setCursor(0, 1);
    lcd.print(" Grigore Eduard ");
     delay(2000);
     }
    }
   
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 10) {  
    lights();
    sound();
  }
  else {
   digitalWrite(led[0], HIGH);
  }
  if (distance >= 400 || distance <= 0){    
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm"); //in centimeters
  }
  stand_by = digitalRead(button_pin);
  
  if(stand_by == HIGH){
     signal = LOW;
     digitalWrite(led[0],LOW);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("   Ai revenit   ");
     lcd.setCursor(0, 1);
     lcd.print("Apasa iar buton");
     delay(2000);
  }
  
  
}

void lights(){                     
  digitalWrite(led[0], LOW);    // turn LED off by making voltage LOW
  digitalWrite(led[1], HIGH);    // turn LED on (HIGH is voltage level)
  delay(150);                      // wait  150 ms
  
  digitalWrite(led[1], LOW);     
  digitalWrite(led[2], HIGH);     
  delay(150);                     
  
  digitalWrite(led[2], LOW);     
  digitalWrite(led[3], HIGH);    
  delay(150);                     
  
  digitalWrite(led[3], LOW); 
  digitalWrite(led[2], HIGH); 
  delay(150); 
  digitalWrite(led[2], LOW); 
  digitalWrite(led[1], HIGH);
  delay(150); 
  digitalWrite(led[1], LOW);      
  digitalWrite(led[0], HIGH);    
  delay(150);   
}

void sound(){
  lcd.clear();
  int pos = 180;
  int m = 0;
  int n = 0;
  int z = 0;
  int nr_par;
  if(repeat==6 || repeat == 2){
     nr_par = 0;
  }
  else if(repeat==0){
    nr_par = 4;
  }
  else if(repeat==4){
    nr_par = 2;
  }
  
  int nr_impar= nr_par+1;
  lcd.setCursor(0, 1);
  lcd.print("Bafta la Examene"); 
  for(int i = 0; i < numeroNote; i++){
    
    lcd.setCursor(0, 0);
    lcd.print(mesaje[z]);
    delay(150);
    digitalWrite(led[m],LOW);
    digitalWrite(led[n],LOW);
    m = random(0,4);
    n = random(0,4);
    int durata = 1500 / songs[nr_impar][i];
    tone(buzzerPin, songs[nr_par][i], durata); 
    digitalWrite(led[m],HIGH);
    digitalWrite(led[n],HIGH);
    delay(durata * 1.3);
    myservo.write(pos);
    pos = pos -7;
    z++;
    if(z==5){
      z=0;
    }
 }
  repeat = nr_par;
  digitalWrite(led[m],LOW);
  digitalWrite(led[n],LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Lasati un Like");
    lcd.setCursor(0, 1);
    lcd.print("       :)");
   
}
