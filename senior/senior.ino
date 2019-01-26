#include <Servo.h>  

String inString;
int value;

boolean q = false,e= false,a= false, d= false, space= false;


int M1 = 6, M2 = 7, M3 = 8, M4 = 9, GATE = 11;
int M1e = 5, M2e = 3;

int GATE_OPEN = 10;
int GATE_CLOSED = 90;


Servo gate;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  Serial.setTimeout(100);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(M1e, OUTPUT);
  pinMode(M2e, OUTPUT);

  analogWrite(M1e, 0);
  analogWrite(M2e, 0);

  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
  

  gate.attach(GATE);
}

// the loop function runs over and over again forever
void loop() {
  updatePins();
  
  // MOTEUR GAUCHE
  if(a){
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    digitalWrite(M1e, HIGH);
  }
  else if (q) {
    digitalWrite(M1, LOW);
    digitalWrite(M2, HIGH);
    digitalWrite(M1e, HIGH);
  }
  else {
    digitalWrite(M1e, LOW);
  }


  // MOTEUR DROIT
  if(d){
    digitalWrite(M3, HIGH);
    digitalWrite(M4, LOW);
    digitalWrite(M2e, HIGH);
  }
  else if (e) {
    digitalWrite(M3, LOW);
    digitalWrite(M4, HIGH);
    digitalWrite(M2e, HIGH);
  }
  else {
    digitalWrite(M2e, LOW);
  }
  

  // SERVO
  if(space)
    gate.write(10);
  else
    gate.write(100);
    
  delay(100);
}

void updatePins(){
  while(Serial.available() > 0){
    String command = Serial.readStringUntil('\n');
    if(command != ""){
      Serial.println(command);
      String key = command.substring(0, 2);
      int value = command.substring(2, 5).toInt();

      if(key == "q.")
        q = value;
      else if(key == "e.")
        e = value;
      else if(key == "a.")
        a = value;
      else if(key == "d.")
        d = value;
      else if(key == "sp")
        space = value;
    }
  }
}
 
