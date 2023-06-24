#include <max6675.h>

//==================== pin Setup Sensor Suhu ==========================================//
int pinThermoSO1 = 2;
int pinThermoCS1 = 5;
int pinThermoSCK1 = 6;

MAX6675 thermocouple1(pinThermoSCK1, pinThermoCS1, pinThermoSO1);

int pinThermoSO2 = 3;
int pinThermoCS2 = 5;
int pinThermoSCK2 = 6;

MAX6675 thermocouple2(pinThermoSCK2, pinThermoCS2, pinThermoSO2);

int pinThermoSO3 = 4;
int pinThermoCS3 = 5;
int pinThermoSCK3 = 6;

MAX6675 thermocouple3(pinThermoSCK3, pinThermoCS3, pinThermoSO3);

int pinThermoSO4 = 7;
int pinThermoCS4 = 5;
int pinThermoSCK4 = 6;

MAX6675 thermocouple4(pinThermoSCK4, pinThermoCS4, pinThermoSO4);

//=========================== PIN Setup SSR ======== //

 int pinSSR1=8;
 int pinSSR2=9;
 int pinSSR3=10;

//============================ data =============================//

float dataSuhu[4]={0,0,0,0};
byte kirimSuhu[8];

double setSensorSuhu1=0;
double setSensorSuhu2=0;
double setSensorSuhu3=0;
double setSensorSuhu4=0;

double setBatasSuhuAtas1=0;
double setBatasSuhuBawah1=0;
double setBatasSuhuAtas2=0;
double setBatasSuhuBawah2=0;
double setBatasSuhuAtas3=0;
double setBatasSuhuBawah3=0;
double setBatasSuhuAtas4=0;
double setBatasSuhuBawah4=0;


//byte kirimSuhu2[4];

void readSensorSuhu()
{
  dataSuhu[0]=thermocouple1.readCelsius();
  dataSuhu[1]=thermocouple2.readCelsius();
  dataSuhu[2]=thermocouple3.readCelsius();
  dataSuhu[3]=thermocouple4.readCelsius();
//  Serial.println(String (dataSuhu1) + ","+ String (dataSuhu2) + ","+ String (dataSuhu3) + "," + String (dataSuhu4));  
}

void kirimData()
{
    kirimSuhu[1]=(dataSuhu[0]*100);
    kirimSuhu[0] = kirimSuhu[1] >> 8;
    kirimSuhu[3]=(dataSuhu[1]*100);
    kirimSuhu[2] = kirimSuhu[3] >> 8;
    kirimSuhu[5]=(dataSuhu[2]*100);
    kirimSuhu[4] = kirimSuhu[5] >> 8;
    kirimSuhu[7]=(dataSuhu[3]*100);
    kirimSuhu[6] = kirimSuhu[7] >> 8;
    Serial1.write(kirimSuhu,8); 
}
void setDataJarakSuhu(double data1,double data2,double data3,double data4)
{
  setBatasSuhuAtas1= (data1 + 1);
  setBatasSuhuBawah1= (data1 - 1);
  setBatasSuhuAtas2= (data2 + 1);
  setBatasSuhuBawah2= (data2 - 1);
  setBatasSuhuAtas3= (data3 + 1);
  setBatasSuhuBawah3= (data3 - 1);
  setBatasSuhuAtas4= (data4 + 1);
  setBatasSuhuBawah4= (data4 - 1);
}

void SSRControl()
{
 
}

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(pinSSR1,OUTPUT);
  pinMode(pinSSR2,OUTPUT);
  pinMode(pinSSR3,OUTPUT);
}

void loop() 
{
  readSensorSuhu();
  kirimData();
  
}
