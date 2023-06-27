#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID   "TMPL6s3LsjDs4"
#define BLYNK_TEMPLATE_NAME "Heater Monitoring"
#define BLYNK_AUTH_TOKEN    "5ce4OLayXPbTo1417cpmFYe6VpcPDQ7m"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define SSID     "rajaaa"
#define PASSWORD "18091998"

BlynkTimer timer;

float suhuValue1 = 0.0, suhuValue2 = 0.0, suhuValue3 = 0.0, suhuValue4 = 0.0;
byte dataInput[8];

void myTimerEvent()
{
  Blynk.virtualWrite(V3, suhuValue4);
  Blynk.virtualWrite(V2, suhuValue3);
  Blynk.virtualWrite(V1, suhuValue2);
  Blynk.virtualWrite(V0, suhuValue1);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, SSID, PASSWORD);
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  timer.run();
  
  if(Serial2.available() > 7){
    // for(int a = 0; a < 8; a++){
    //   dataInput[a] = Serial2.read();
    //   Serial.print(dataInput[a]);
    //   Serial.print("\t");
    // }
    // Serial.println();
    suhuValue1 = ((dataInput[0] << 8) + dataInput[1]) / 100.0;
    suhuValue2 = ((dataInput[2] << 8) + dataInput[3]) / 100.0;
    suhuValue3 = ((dataInput[4] << 8) + dataInput[5]) / 100.0;
    suhuValue4 = ((dataInput[6] << 8) + dataInput[7]) / 100.0;
    // Serial.print(suhuValue1);
    // Serial.print("\t");
    // Serial.print(suhuValue2);
    // Serial.print("\t");
    // Serial.print(suhuValue3);
    // Serial.print("\t");
    // Serial.println(suhuValue4);
  }
}
