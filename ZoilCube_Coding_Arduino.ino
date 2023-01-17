#include <Wire.h>
#include <Adafruit_HDC1000.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25
#include <LiquidCrystal_I2C.h>
#include <Adafruit_seesaw.h>
#define Pavalue 101325

float atmvalue = 9.86923E-6;
float valordeconversion_atm;
float tempC;
uint16_t capacitance_read;
int delaytime = 8000;

LiquidCrystal_I2C lcd(0x27,16,2);
Adafruit_BMP085 bmp;
Adafruit_HDC1000 hdc = Adafruit_HDC1000();

Adafruit_seesaw ss;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(1,0);

  if (!bmp.begin()) {
    lcd.println("BMP085 not found");
    while (1) {}
  }

  if (!ss.begin(0x36)) {
    lcd.println("SeeSaw not found");
    while (1) {}
  }

  if (!hdc.begin()){
    lcd.print("HDC1000 not found");
    while (1){}
  }
}

void loop() {
  // put your main code here, to run repeatedly:
//Temperature
lcd.setCursor(1,0);
lcd.print("Temperature=    ");
lcd.setCursor(1,1);
lcd.print(bmp.readTemperature());
lcd.print(" *C     ");

delay (delaytime);

//Altitud
lcd.setCursor(1,0);
lcd.print("Altitude=       ");
lcd.setCursor(1,1);
lcd.print(bmp.readAltitude());
lcd.print(" meters ");

delay (delaytime);

//Presion al nivel del mar
lcd.setCursor(1,0);
lcd.print("Calc PSeaLvl=   ");
lcd.setCursor(1,1);
valordeconversion_atm = (bmp.readSealevelPressure() * atmvalue);
lcd.print(valordeconversion_atm);
lcd.print("  atm     ");

delay(delaytime);

//Temperatura suelo
lcd.setCursor(1,0);
lcd.print("Temp Soil=      ");
lcd.setCursor(1,1);
tempC = ss.getTemp();
lcd.print(tempC);
lcd.print(" *C     ");

delay(delaytime);

//CapSuelo
lcd.setCursor(1,0);
lcd.print("Capacitive=     ");
lcd.setCursor(1,1);
capacitance_read = ss.touchRead(0);
lcd.print("cap read    ");

delay(delaytime);

//Temp HDC1000
lcd.setCursor(1,0);
lcd.print("Temp HCD1000=   ");
lcd.setCursor(1,1);
lcd.print(hdc.readTemperature());
lcd.print(" *C     ");

delay (delaytime);

//Humidity HDC1000
lcd.setCursor(1,0);
lcd.print("Humidity % =    ");
lcd.setCursor(1,1);
lcd.print(hdc.readHumidity());
lcd.print(" %           ");

delay (delaytime);

}
