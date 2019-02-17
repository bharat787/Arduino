#include <LiquidCrystal.h>
#include <dht.h>

#include <Wire.h>
#include <DS3231.h>

DS3231 clock;
RTCDateTime dt;

#define REDLITE 3
#define GREENLITE 5
#define BLUELITE 6

///////////////////////////////////////////////////////////////////
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


//////////////////////////////////////////////////////////CLOCK INIT

////////////////////////////////////////////////////////////////////

int pinDHT11 = 2;

dht DHT;
int brightness =255;

void setup() {

  Wire.begin();
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);

 

 pinMode(REDLITE, OUTPUT);
  pinMode(GREENLITE, OUTPUT);
  pinMode(BLUELITE, OUTPUT);
 
  brightness = 100;
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Bharat Gupta");
  lcd.setCursor(0, 1);
  lcd.print("Clk with RTC");
  delay(1500);
  lcd.clear();


  Serial.begin(115200);


}

void loop() {
//////////////////////////////////////////////////////////////////////
  //Setting the time will stop the clock to set the time

 
dt = clock.getDateTime();

lcd.setCursor(0,0);
if(dt.hour < 10){
  lcd.print("0");
  lcd.print(dt.hour);
}
else{
lcd.print(dt.hour);
}
lcd.print(":");
if(dt.minute <10){
  lcd.print("0");
  lcd.print(dt.minute);
  }
 else
 {
lcd.print(dt.minute);
 }
lcd.print(":");
if(dt.second <10){
  lcd.print("0");
  lcd.print(dt.second);
  }
 else
 {
lcd.print(dt.second);
lcd.print(" ");
lcd.print(dt.day);
lcd.print("/");
lcd.print(dt.month);
lcd.print("/");
lcd.print(dt.year - 2000);
//if(dt.hour>12){
//  lcd.print("PM");
//}
//else{
//  lcd.print("AM");
//}
 }


  Serial.print("Raw data: ");
  //Serial.print(dt.year);   Serial.print("-");
 // Serial.print(dt.month);  Serial.print("-");
  //Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println(""); 

 for (int i = 0; i < 255; i++) {
    setBacklight(i, 0, 255-i);
    delay(10);
  }
  for (int i = 0; i < 255; i++) {
    setBacklight(255-i, i, 0);
    delay(10);
  }
  for (int i = 0; i < 255; i++) {
    setBacklight(0, 255-i, i);
    delay(10);
  }


/////////////////////////////////////////////////////////////////////  

///////////////////////////////////////////////////////////////
 
/////////////////////////////////////////////////////////////
    //FROM SENSOR TO SERIAL
     Serial.print("DHT11, \t");
  int ch = DHT.read11(pinDHT11);
  switch (ch)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
  // DISPLAY DATA
  Serial.print(DHT.humidity, 2);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 2);

  delay(200);

 //////////////////////////////////////////////////////////// 
    
    lcd.setCursor(0, 1);
    lcd.print("Tp:");
    //lcd.print((int)temperature);
    lcd.print(DHT.temperature, 1);
    //lcd.print("*C");
    lcd.print(" ");
    lcd.print("Hm:");
    lcd.print(DHT.humidity, 1);
    lcd.print("%");
  

}
void setBacklight(uint8_t r, uint8_t g, uint8_t b) {
  // normalize the red LED - its brighter than the rest!
  r = map(r, 0, 255, 0, 100);
  g = map(g, 0, 255, 0, 150);
 
  r = map(r, 0, 255, 0, brightness);
  g = map(g, 0, 255, 0, brightness);
  b = map(b, 0, 255, 0, brightness);
 
  // common anode so invert!
  r = map(r, 0, 255, 255, 0);
  g = map(g, 0, 255, 255, 0);
  b = map(b, 0, 255, 255, 0);
  Serial.print("R = "); Serial.print(r, DEC);
  Serial.print(" G = "); Serial.print(g, DEC);
  Serial.print(" B = "); Serial.println(b, DEC);
  analogWrite(REDLITE, r);
  analogWrite(GREENLITE, g);
  analogWrite(BLUELITE, b);
}


