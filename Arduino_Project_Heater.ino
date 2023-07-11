//#include <SoftwareSerial.h>
#include "nextion.h"
#include <EEPROM.h>
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

int pinSSR[3] = {10, 9, 8};
#define statusSSR1 A0
#define statusSSR2 A1
#define statusSSR3 A2

//============================ data =============================//

float dataSuhu[4] = {0, 0, 0, 0};
byte kirimSuhu[8];
uint16_t suhuSementara[4];

//double setSensorSuhu1=0;
//double setSensorSuhu2=0;
//double setSensorSuhu3=0;
//double setSensorSuhu4=0;

double setBatasSuhuAtas[3] = {0, 0, 0};
double setBatasSuhuBawah[3] = {0, 0, 0};

double setDataSuhu[3] = {0, 0, 0};

int Received[37];

const int setSelisihSuhu = 15;
const int error = 1;



//byte kirimSuhu2[4];

void readSensorSuhu()
{
  dataSuhu[0] = thermocouple1.readCelsius();
  delay(10);
  dataSuhu[1] = thermocouple2.readCelsius();
  delay(10);
  dataSuhu[2] = thermocouple3.readCelsius();
  delay(10);
  dataSuhu[3] = thermocouple4.readCelsius();
  delay(10);


  for (int x = 0; x <= 3; x++)
  {
    if (dataSuhu[x] >= 40)
    {
      dataSuhu[x] = (dataSuhu[x] + ((dataSuhu[x] / 3) - (setSelisihSuhu)));
    }
    else if (dataSuhu < 40)
    {
      dataSuhu[x] = dataSuhu[x];
    }

  }
  //  dataSuhu[0]=dataSuhu[0]+26;
  //  dataSuhu[1]=dataSuhu[1]+34;
  //  dataSuhu[2]=dataSuhu[2]-20;
  //  dataSuhu[3]=dataSuhu[3]+5;

  Serial.print("Thermocouple : ");
  for (int x = 0; x <= 3; x++)
  {
    Serial.print("suhu " + String(x + 1) + "  :" + String(dataSuhu[x]) + "  ");
  }
  Serial.println();
  // Serial.println(Curr_set);
  //      Serial.println(Curr_ten_set);
  //      Serial.println(Curr_hun_set);
  //  Serial.print("Thermocouple : ");
  //  Serial.println(String (dataSuhu1) + ","+ String (dataSuhu2) + ","+ String (dataSuhu3) + "," + String (dataSuhu4));
}

void kirimData()
{
  suhuSementara[0] = (uint16_t)(dataSuhu[0] * 100.00);
  suhuSementara[1] = (uint16_t)(dataSuhu[1] * 100.00);
  suhuSementara[2] = (uint16_t)(dataSuhu[2] * 100.00);
  suhuSementara[3] = (uint16_t)(dataSuhu[3] * 100.00);
  kirimSuhu[1] = (byte)(dataSuhu[0] * 100.00);
  kirimSuhu[0] = suhuSementara[0] >> 8;
  kirimSuhu[3] = (byte)(dataSuhu[1] * 100.00);
  kirimSuhu[2] = suhuSementara[1] >> 8;
  kirimSuhu[5] = (byte)(dataSuhu[2] * 100.00);
  kirimSuhu[4] = suhuSementara[2] >> 8;
  kirimSuhu[7] = (byte)(dataSuhu[3] * 100.00);
  kirimSuhu[6] = suhuSementara[3] >> 8;
  //  kirimSuhu[6] = 9;
  //  kirimSuhu[7] = 9;
  Serial2.write(kirimSuhu, 8);
  //  Serial.println("YAA");
  //    for(int x=0;x<8;x++)
  //    {
  //      Serial.print(kirimSuhu[x]);
  //      Serial.print("\t");
  //    }
  //    Serial.println();

}
void setBatasSuhu()
{
  for (int x = 0; x <= 2; x++)
  {
    setBatasSuhuAtas[x] = setDataSuhu[x] + 1;
    setBatasSuhuBawah[x] = setDataSuhu[x] - 1;
  }
}

void statusSSR()
{
  if (digitalRead(statusSSR1) == LOW)
  {
    String status1 = "t4.txt=\"" + String ("ON") + "\"";
    Serial1.print(status1);
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }
  else if (digitalRead(statusSSR1) == HIGH)
  {
    String status2 = "t4.txt=\"" + String ("OFF") + "\"";
    Serial1.print(status2);
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }
  if (digitalRead(statusSSR2) == LOW)
  {
    String status3 = "t5.txt=\"" + String ("ON") + "\"";
    Serial1.print(status3);
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }
  else if (digitalRead(statusSSR2) == HIGH)
  {
    String status4 = "t5.txt=\"" + String ("OFF") + "\"";
    Serial1.print(status4);
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }
  if (digitalRead(statusSSR3) == LOW)
  {
    String status5 = "t6.txt=\"" + String ("ON") + "\"";
    Serial1.print(status5);
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }
  else if (digitalRead(statusSSR1) == HIGH)
  {
    String status6 = "t6.txt=\"" + String  ("OFF") + "\"";
    Serial1.print(status6);
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }

}

void SSRControl()
{
  for (int x = 0; x <= 2; x++)
  {
    Serial.print("SSR ");
    Serial.print(x);
    if (dataSuhu[x] <= setBatasSuhuBawah[x])
    {
      Serial.println(" Hidup");
      digitalWrite(pinSSR[x], HIGH);
    }
    else if (dataSuhu[x] >= setBatasSuhuAtas[x] || dataSuhu[x] == setDataSuhu[x])
    {
      Serial.println(" mati");
      digitalWrite(pinSSR[x], LOW);
    }
  }
}

void tampilanLayar()
{
  String suhu0 = "t0.txt=\"" + String (dataSuhu[0]) + "\"";
  Serial1.print(suhu0);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  String suhu1 = "t1.txt=\"" + String (dataSuhu[1]) + "\"";
  Serial1.print(suhu1);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  String suhu2 = "t2.txt=\"" + String (dataSuhu[2]) + "\"";
  Serial1.print(suhu2);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  String suhu3 = "t3.txt=\"" + String (dataSuhu[3]) + "\"";
  Serial1.print(suhu3);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
}

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  Serial2.begin(9600);
  pinMode(pinSSR[0], OUTPUT);
  pinMode(pinSSR[1], OUTPUT);
  pinMode(pinSSR[2], OUTPUT);
  pinMode(statusSSR1, INPUT_PULLUP);
  pinMode(statusSSR2, INPUT_PULLUP);
  pinMode(statusSSR3, INPUT_PULLUP);

  Volt_set = EEPROM.read(0);
  Volt_ten_set = EEPROM.read(1);
  Volt_hun_set = EEPROM.read(2);

  Curr_set = EEPROM.read(3);
  Curr_ten_set = EEPROM.read(4);
  Curr_hun_set = EEPROM.read(5);

  pow_set = EEPROM.read(6);
  pow_ten_set = EEPROM.read(7);
  pow_hun_set = EEPROM.read(8);

  //  Serial.print(String(Volt_set) + " ");
  //  Serial.print(String(Volt_ten_set) + " ");
  //  Serial.print(String(Volt_hun_set) + " ");
  //  Serial.println();
  //  Serial.print(String(Curr_set) + " ");
  //  Serial.print(String(Curr_ten_set) + " ");
  //  Serial.print(String(Curr_hun_set) + " ");
  //  Serial.println();
  //  Serial.print(String(pow_set) + " ");
  //  Serial.print(String(pow_ten_set) + " ");
  //  Serial.print(String(pow_hun_set) + " ");
  //  Serial.println();

  delay(200);
  // delay(3000);
  Serial.println(Serial1.available());
  //   if(Serial1.available()>11)
  //    {
  //        for(int x=0;x<=11;x++)
  //      {
  //        Serial.print(Serial1.read());
  //        Serial.print(" ");
  //      }
  //    }



  //  for(int x=0;x<=8;x++)
  //  {
  //    Serial.print(EEPROM.read(x]);
  //    Serial.print("  ")
  //  }

  Voltage_set = Volt_set + (Volt_ten_set / 10) + (Volt_hun_set / 100);  //We summ all parts to get the total set voltage value
  Current_set = Curr_set + (Curr_ten_set / 10) + (Curr_hun_set / 100);
  Power_set = pow_set + (pow_ten_set / 10) + (pow_hun_set / 100);

  setDataSuhu[0] = Voltage_set;
  setDataSuhu[1] = Current_set;
  setDataSuhu[2] = Power_set;
  setBatasSuhu();

  Serial.print(String(setDataSuhu[0]) + " ");
  Serial.print(String(setDataSuhu[1]) + " ");
  Serial.print(String(setDataSuhu[2]) + " ");


  String suhuBefore = "t9.txt=\"" + String (setDataSuhu[0]) + "\"";
  Serial1.print(suhuBefore);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  String suhuBefore1 = "t10.txt=\"" + String (setDataSuhu[1]) + "\"";
  Serial1.print(suhuBefore1);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);

  String suhuBefore2 = "t11.txt=\"" + String (setDataSuhu[2]) + "\"";
  Serial1.print(suhuBefore2);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);


  //   delay(1000);


}

unsigned long int prevTime = 0;
int x;
void loop()
{
  if (Serial1.available() > 0)
  {
    byte data = Serial1.read();
    Received[x] = data;
    x++;


    if (Received[0] == 98) {
      if (x == 37) {
        Volt_set = double(Received[1]);        //First, than the 5th, than the 9th etc...
        Volt_ten_set = double(Received[5]);
        Volt_hun_set = double(Received[9]);

        EEPROM.write(0, Volt_set);
        EEPROM.write(1, Volt_ten_set);
        EEPROM.write(2, Volt_hun_set);

        Curr_set = double(Received[13]);
        Curr_ten_set = double(Received[17]);
        Curr_hun_set = double(Received[21]);
        EEPROM.write(3, Curr_set);
        EEPROM.write(4, Curr_ten_set);
        EEPROM.write(5, Curr_hun_set);

        pow_set = double(Received[25]);
        pow_ten_set = double(Received[29]);
        pow_hun_set = double(Received[33]);
        EEPROM.write(6, pow_set);
        EEPROM.write(7, pow_ten_set);
        EEPROM.write(8, pow_hun_set);


        Voltage_set = Volt_set + (Volt_ten_set / 10) + (Volt_hun_set / 100);  //We summ all parts to get the total set voltage value
        Current_set = Curr_set + (Curr_ten_set / 10) + (Curr_hun_set / 100);
        Power_set = pow_set + (pow_ten_set / 10) + (pow_hun_set / 100); //We summ all parts to get the total set current value

        setDataSuhu[0] = Voltage_set;
        setDataSuhu[1] = Current_set;
        setDataSuhu[2] = Power_set;
        String suhuBefore = "t9.txt=\"" + String (setDataSuhu[0]) + "\"";
        Serial1.print(suhuBefore);
        Serial1.write(0xff);
        Serial1.write(0xff);
        Serial1.write(0xff);

        String suhuBefore1 = "t10.txt=\"" + String (setDataSuhu[1]) + "\"";
        Serial1.print(suhuBefore1);
        Serial1.write(0xff);
        Serial1.write(0xff);
        Serial1.write(0xff);

        String suhuBefore2 = "t11.txt=\"" + String (setDataSuhu[2]) + "\"";
        Serial1.print(suhuBefore2);
        Serial1.write(0xff);
        Serial1.write(0xff);
        Serial1.write(0xff);
        Serial.print("Set Suhu HMI : ");
        Serial.print(setDataSuhu[0]);
        Serial.print("\t");
        Serial.print(setDataSuhu[1]);
        Serial.print("\t");
        Serial.println(setDataSuhu[2]);

        setBatasSuhu();
        x = 0;
        Serial.println("Bisa");
      }
    }
    else {
      x = 0;
    }

  }

  if ((millis() - prevTime) > 500) {
    readSensorSuhu();
    kirimData();
    tampilanLayar();
    SSRControl();
    prevTime = millis();
  }

}
