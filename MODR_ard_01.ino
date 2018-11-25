/*

 * Modular robot initial testing.
 * 2 DC motors wired to a tb6612fng
 * left motor outputs connected to pins 2 & 4
 * right motor outputs connected to pins 3 & 5
 * Pin interrupts 2 & 3

 */

//// DEFINITIONS ////

// Encoder pins
#define rig_enc_a 3 
#define rig_enc_b 5
#define lef_enc_a 2
#define lef_enc_b 4

// Direction & speed pins
#define rig_dir_a 6
#define rig_dir_b 7
#define rig_pwm 10
#define lef_dir_a 8                                             
#define lef_dir_b 9
#define lef_pwm 11
#define stb 12

// declarations
int del = 1200;
int spe = 150;
int msg = '0';
int LED = 13;
char data = 0;

//Counters
volatile unsigned long rig_enc_cou = 0;
volatile unsigned long lef_enc_cou = 0;

void dir_stop(){
  
  digitalWrite(lef_dir_a,LOW);
  digitalWrite(lef_dir_b,LOW);
  analogWrite(lef_pwm,spe);

  digitalWrite(rig_dir_a,LOW);
  digitalWrite(rig_dir_b,LOW);
  analogWrite(rig_pwm,spe);
  
}

void dir_back(){
  
  digitalWrite(lef_dir_a,HIGH);
  digitalWrite(lef_dir_b,LOW);
  analogWrite(lef_pwm,spe);

  digitalWrite(rig_dir_a,LOW);
  digitalWrite(rig_dir_b,HIGH);
  analogWrite(rig_pwm,spe);
  
}

void dir_front(){
  
  digitalWrite(lef_dir_a,LOW);
  digitalWrite(lef_dir_b,HIGH);
  analogWrite(lef_pwm,spe);

  digitalWrite(rig_dir_a,HIGH);
  digitalWrite(rig_dir_b,LOW);
  analogWrite(rig_pwm,spe);

  delay(200);
  
}

void dir_right(){
  
  digitalWrite(lef_dir_a,LOW);
  digitalWrite(lef_dir_b,HIGH);
  analogWrite(lef_pwm,spe);

  digitalWrite(rig_dir_a,LOW);
  digitalWrite(rig_dir_b,LOW);
  analogWrite(rig_pwm,spe);
  
}

void dir_left(){
  
  digitalWrite(lef_dir_a,LOW);
  digitalWrite(lef_dir_b,LOW);
  analogWrite(lef_pwm,spe);

  digitalWrite(rig_dir_a,HIGH );
  digitalWrite(rig_dir_b,LOW);
  analogWrite(rig_pwm,spe);
  
}

void rightEncoderEvent() {
  if (digitalRead(rig_enc_a) == HIGH) {
    if (digitalRead(rig_enc_b) == LOW) {
      rig_enc_cou++;
    } else {
      rig_enc_cou--;
    }
  } else {
    if (digitalRead(rig_enc_b) == LOW) {
      rig_enc_cou--;
    } else {
      rig_enc_cou++;
    }
  }
}

void leftEncoderEvent() {
  if (digitalRead(lef_enc_a) == HIGH) {
    if (digitalRead(lef_enc_b) == LOW) {
      lef_enc_cou++;
    } else {
      lef_enc_cou--;
    }
  } else {
    if (digitalRead(lef_enc_b) == LOW) {
      lef_enc_cou--;
    } else {
      lef_enc_cou++;
    }
  }
}

void setup() {

  Serial.begin(9600);

  digitalWrite(stb,HIGH);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  
  pinMode(rig_enc_a, INPUT);
  pinMode(rig_enc_b, INPUT);
  pinMode(lef_enc_a, INPUT);
  pinMode(lef_enc_b, INPUT);

  pinMode(stb, OUTPUT);
  pinMode(lef_dir_a, OUTPUT);
  pinMode(lef_dir_b, OUTPUT);
  pinMode(lef_pwm,OUTPUT);
  
  // initialize hardware interrupts
  attachInterrupt(0, leftEncoderEvent, CHANGE);
  attachInterrupt(1, rightEncoderEvent, CHANGE);
  
}

void loop(){
  
   if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");        

      if(data == '0'){
        dir_stop();
      }
      
      else if(data == '1'){
        dir_front();
      }

      else if (data == '2'){
        dir_right();
      }
            
      else if (data == '3'){
        dir_back();
      }
      
      else if(data == '4'){
         dir_left();
      }
   }
}


