#include <LiquidCrystal.h>

const int fanPin  = 10; //initializes fan
const int tempPin = A5; //initializes sensor

const int ledR = 9;//Red pin
const int ledG = 8;//Green pin
const int ledB = 7;//Blue pin

const int rs = 12, e = 11, db4 = 5, db5 = 4, db6 = 3, db7 = 2;

LiquidCrystal lcd(rs, e, db4, db5, db6, db7);

float voltage;
float temperature; //**

//Determine if RGB operators are on or off
void setColor(bool r, bool g, bool b) {
  digitalWrite(ledR, r ? HIGH : LOW);
  digitalWrite(ledG, g ? HIGH : LOW);
  digitalWrite(ledB, b ? HIGH : LOW);
}

void setup() {
  
    pinMode(fanPin, OUTPUT);
    
    lcd.begin(16, 2); //Turns on LCD
    lcd.print("Initializing..."); 
    delay(2000);
    lcd.clear();
  
  	//Sets pins for RGB
    pinMode(ledR, OUTPUT); 
    pinMode(ledG, OUTPUT);
    pinMode(ledB, OUTPUT);
    setColor(0,0,0);
}

void loop() {
  	//converting from voltage to temperature
    int reading = analogRead(tempPin);
    temperature = (reading*(5.0/1024.0) - 0.5) * 100.0;

	if (temperature < 15) {
    	analogWrite(fanPin, 0);
    	setColor(0,0,1);
		}
	else if (temperature < 25){ 
    	analogWrite(fanPin, 20);
    	setColor(1,0,1);
		}
	else if (temperature < 50){
    	analogWrite(fanPin, 30);
    	setColor(1,0,0);
		}
	else {
    	analogWrite(fanPin, 40);
    	setColor(1,1,0);
		}

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature, 0);
    lcd.print(" C    ");

    lcd.setCursor(0, 1);
    lcd.print("Fan: ");
    if (temperature < 15)      
      lcd.print("OFF   ");
    else if (temperature < 25) 
      lcd.print("LOW   ");
    else if (temperature < 50) 
      lcd.print("MED   ");
    else                       
      lcd.print("HIGH  ");

    delay(200);
}
