#include <max6675.h>


int pinThermoSO1 = 2;
int pinThermoCS1 = 3;
int pinThermoSCK1 = 4;

MAX6675 thermocouple1(pinThermoSCK1, pinThermoCS1, pinThermoSO1);

int pinThermoSO2 = 2;
int pinThermoCS2 = 3;
int pinThermoSCK2 = 4;

MAX6675 thermocouple2(pinThermoSCK2, pinThermoCS2, pinThermoSO2);

int pinThermoSO3 = 5;
int pinThermoCS3 = 6;
int pinThermoSCK3 = 7;

MAX6675 thermocouple3(pinThermoSCK3, pinThermoCS3, pinThermoSO3);

int pinThermoSO4 = 8;
int pinThermoCS4 = 9;
int pinThermoSCK4 = 10;

MAX6675 thermocouple4(pinThermoSCK4, pinThermoCS4, pinThermoSO4);



//============================ data =============================//

int dataSuhu1=0;
int dataSuhu2=0;
int dataSuhu3=0;
int dataSuhu4=0;

void readSensorSuhu()
{
  dataSuhu1=thermocouple1.readCelsius();
  dataSuhu2=thermocouple2.readCelsius();
  dataSuhu3=thermocouple3.readCelsius();
  dataSuhu4=thermocouple4.readCelsius();
  Serial.println(String (dataSuhu1) + ","+ String (dataSuhu2) + ","+ String (dataSuhu3) + "," + String (dataSuhu4));  
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  
 
}
