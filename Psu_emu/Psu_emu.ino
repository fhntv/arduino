volatile int Count = 0;

//volatile boolean OnStateBitOrder[]=[0,0,1,1,0,0,0,0,1,0,1,0,1,0,1];
volatile int OnStateBitOrder[]= {1,1,0,0,1,1,1,1,0,1,0,1,0,1,0,1};//15
volatile int OffStateBitOrder[]={0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,0};//15
                           //    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
volatile int state=0; //0=off, 1=on;

void setup() {
  // put your setup code here, to run once:

attachInterrupt(0, SyncCountReset, FALLING); //digital 2
attachInterrupt(1, SyncCount, RISING ); // digital 3
DDRD = DDRD | B11000000; //pin 7 and 6 out

}

void loop() {
  // put your main code here, to run repeatedly:

}

void SyncCountReset(){
  Count=0;
     
  }
  
void SyncCount(){
  if(Count>15) return;

  if(state = 0){ // OFF
    if(OffStateBitOrder[Count] == 1){
       PORTD = B01000000; //set high
      }
    else
      {
      PORTD = B00000000; //set LOW    
      }
   }
   else
   { // On
    if(OnStateBitOrder[Count] == 1){
       PORTD = B01000000; //set high
      }
    else
      {
      PORTD = B00000000; //set LOW    
      }
    
   }
   
  Count+=1;
  
}
  
