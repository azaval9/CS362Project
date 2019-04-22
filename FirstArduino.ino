/***********************************************
* name:Infrared-Receiver
* function:press the Power key of a remote control,
* and both the LED attached and that connected to pin 13 on the SunFounder Uno board will light up.
* Then press any other key, and the LEDs will go out.
**********************************************/
//Email: support@sunfounder.com
//Website: www.sunfounder.com

#include <NewTone.h>
#include <IRremote.h> 
#include <LiquidCrystal.h>


const int irReceiverPin = 7; //ir receiver module attach to pin2
const int MY_SIZE = 4;
const int buzzer = 8;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

IRrecv irrecv(irReceiverPin); //Creates a variable of type IRrecv
decode_results results; 
int myArray[MY_SIZE];
int i = 0;

void clearArr(int myArray[]) {
  for(int j = 0; j < i ; j++){
     myArray[j] = 0;
  }
}

void buzzerSound( int x){
  NewTone(buzzer, 1000);
  delay(x);
  noNewTone(buzzer);
}

void buzzerRepeat(){
  int i = 0;
  for(i = 0; i < 3; i++){
    NewTone(buzzer, 1000);
    delay(100);
    noNewTone(buzzer);
    delay(200);
  }
  
  
}

void setup()
{
  Serial.begin(9600); //initialize serial monitor
  irrecv.enableIRIn(); //enable ir receiver module
  lcd.begin(16,2);
  lcd.print("Top Secret"); 
  pinMode(buzzer, OUTPUT);
}

void loop() 
{
  if (irrecv.decode(&results)) //if the ir receiver module receiver data
  { 
//    Serial.print("irCode: "); //print"irCode: " 
//    Serial.print(results.value, HEX); //print the value in hexdecimal 
//    Serial.print(", bits: "); //print" , bits: " 
//    Serial.println(results.bits); //print the bits
    
    delay(600);

     //Each statement checks the value of the ir receiver and stores it in the array
    if(results.value == 0xFF6897){
      if(i < 4) {
        myArray[i] = 0;
        i++;
      }
    }
    else if(results.value == 0xFF30CF){
      if(i < 4) {
        myArray[i] = 1;
        i++;
      }
    }
    else if(results.value == 0xFF18E7){
      if(i < 4) {
        myArray[i] = 2;
        i++;
      }
    }
    else if(results.value == 0xFF7A85){
      if(i < 4) {
        myArray[i] = 3;
        i++;
      }
    }
    else if(results.value == 0xFF10EF){
      if(i < 4) {
        myArray[i] = 4;
        i++;
      }
    }
    else if(results.value == 0xFF38C7){
      if(i < 4) {
        myArray[i] = 5;
        i++;
      }
    }
    else if(results.value == 0xFF5AA5){
      if(i < 4) {
        myArray[i] = 6;
        i++;
      }
    }
    else if(results.value == 0xFF42BD){
      if(i < 4) {
        myArray[i] = 7;
        i++;
      }
    }
    else if(results.value == 0xFF4AB5){
      if(i < 4) {
        myArray[i] = 8;
        i++;
      }
    }
    else if(results.value == 0xFF52AD){
      if(i < 4) {
        myArray[i] = 9;
      }
      i++;
    }
    // Clear array
    else if (results.value == 0xFF22DD){
        clearArr(myArray);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Reset Input");
        i = 0;
        delay(3000);
    }
    else if( results.value == 0xFFA25D){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Reset Safe");
      buzzerRepeat();
      Serial.write('R');
      clearArr(myArray);
      delay(3000);
    }
    ///ENTER BUTTON
    else if(results.value == 0xFF02FD){
      if(myArray[0] == 1 && myArray[1] == 0 && myArray[2] == 1 && myArray[3] == 0) {
         lcd.clear();
         lcd.print("Access Granted!");
         buzzerRepeat();
         
         //TODO SEND YES TO NEXT ARDUINO
         Serial.write('O');
         clearArr(myArray);
         delay(3000);
      }
      else {
        lcd.clear();
        lcd.print("Access Denied!");
        buzzerSound(3000);
        clearArr(myArray);
        delay(3000);
      }
      
      i = 0;
    }
    lcd.clear();
    for(int j = 0; j < i ; j++) {
      lcd.setCursor(j, 1);
      lcd.print(myArray[j]);
    }
    lcd.setCursor(0,0);
    lcd.print("Top Secret");
    irrecv.resume(); // Receive the next value 
  } 
}