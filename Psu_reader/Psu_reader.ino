

void setup() {
  // put your setup code here, to run once:
int i;

for(i=2;i<=13;i++){
  pinMode(i, INPUT); 
  digitalWrite(i, LOW); 
  }

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
int State0 = 0;
int State1 = 0;
String str = "";
int i; 
int PrevPinState[13];

for(i=2;i<=13;i++){
    State0 = digitalRead(i);

    if(PrevPinState[i]!=State0){
    Serial.print(i);
    Serial.print("Pin:");
    Serial.print(State0);
    Serial.print(" ");
    PrevPinState[i]=State0;
    Serial.print("\n");
    
     }
      
    
  }




  

}
