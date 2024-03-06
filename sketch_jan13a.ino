
const int buzzerPin = 5;
const int ledPin = 6;
const int ledPin2 = 4;
const int motionPin = 7;
const int buttonPin = 12;

boolean buzzer_mode = false;

int ledState = LOW;
long previousMillis = 0; 
long interval = 100;  
int Received=-1;
int connection=0;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(buzzerPin,OUTPUT);

  pinMode(buttonPin, INPUT);
  
  delay(5000);
  
}

void loop()
{

 if(Serial.available()>0)
 {
    Received=Serial.read();
 }
 if(connection==1 && Received=='0')
 {
  Received='9';
  connection=0;
 }
 
 if(connection==0 && Received=='1')
 {
  Received='9';
  connection=1;
 }

if(connection== 1){

  if(buzzer_mode==false)
  {
    digitalWrite(ledPin, HIGH);
  }
  else{
   digitalWrite(ledPin, LOW);
  }
  if (digitalRead(motionPin)) {
    buzzer_mode = true; 
     
  }

  if (buzzer_mode){

   
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;   
      if (ledState == LOW)
        ledState = HIGH;
      else
        ledState = LOW;
   
    digitalWrite(ledPin2, ledState);
    
    }
    tone(buzzerPin,1000);
  }

  if (buzzer_mode == false) {

    noTone(buzzerPin);  
  }

  int button_state = digitalRead(buttonPin);
  if (button_state || Received=='2') {buzzer_mode = false;

  Received='9';
  digitalWrite(ledPin2, LOW);}
  }

  else if (connection==0){
    digitalWrite(ledPin, LOW);
     digitalWrite(ledPin2, LOW);
    buzzer_mode = false;
     noTone(buzzerPin);  
  }
}