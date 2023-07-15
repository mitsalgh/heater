#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID   "TMPL6s3LsjDs4"
#define BLYNK_TEMPLATE_NAME "Heater Monitoring"
#define BLYNK_AUTH_TOKEN    "5ce4OLayXPbTo1417cpmFYe6VpcPDQ7m"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiManager.h>

#define SSID     "rajaaa"
#define PASSWORD "18091998"

BlynkTimer timer;
WiFiManager wifiManager;

float suhuValue1 = 0.0, suhuValue2 = 0.0, suhuValue3 = 0.0, suhuValue4 = 0.0;
byte dataInput[10];
byte countData = 0;
bool header = false;

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
  pinMode(2, OUTPUT);

  WiFi_WifiManager();

  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.run();
  // Blynk.begin(BLYNK_AUTH_TOKEN, SSID, PASSWORD);
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  // WiFi_ManagerReconnect();
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("WiFi Manager : Reconnect WiFi Manager");
    // wifiManager.resetSettings();
    wifiManager.autoConnect("HEATER-KU");
    Serial.println("WiFi Manager : Reconnect WiFi Manager Success");
  }
  else{
    Blynk.run();
    timer.run();
    
    if(Serial2.available() > 0){
      byte data = Serial2.read();
      Serial.print(countData);
      Serial.print(" ");
      Serial.println(data);
      if(countData == 0){
        if(data == 0xAA) {
          dataInput[0] = data;
          countData++;
        }
        else countData = 0;
      }
      else if(countData == 1) {
        if(data == 0x10) {
          dataInput[1] = data;
          countData++;
          return;
        }
        else countData = 0;
      }

      if(dataInput[0] == 0xAA && dataInput[1] == 0x10 && countData > 1){
        dataInput[countData] = data;
        countData++;

        if(countData >= 10){
          countData = 0;
          suhuValue1 = ((dataInput[2] << 8) + dataInput[3]) / 100.0;
          suhuValue2 = ((dataInput[4] << 8) + dataInput[5]) / 100.0;
          suhuValue3 = ((dataInput[6] << 8) + dataInput[7]) / 100.0;
          suhuValue4 = ((dataInput[8] << 8) + dataInput[9]) / 100.0;
          Serial.print(suhuValue1);
          Serial.print("\t");
          Serial.print(suhuValue2);
          Serial.print("\t");
          Serial.print(suhuValue3);
          Serial.print("\t");
          Serial.println(suhuValue4);
        }
      }

      
//      Serial.println(Serial2.read());
      //  for(int a = 0; a < 8; a++){
      //    dataInput[a] = Serial2.read();
      //    Serial.print(dataInput[a]);
      //    Serial.print("\t");
      //  }
      //  Serial.println();
      
      // 
    }
  }
}

void WiFi_WifiManager(){
  Serial.println("WiFi : Init WiFi Manager");
  // wifiManager.resetSettings();
  wifiManager.autoConnect("HEATER-KU");
  Serial.println("WiFi : WiFi Manager Connected");
}

void WiFi_ManagerReconnect(){
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("WiFi Manager : Reconnect WiFi Manager");
    // wifiManager.resetSettings();
    wifiManager.autoConnect("HEATER-KU");
    Serial.println("WiFi Manager : Reconnect WiFi Manager Success");
  }
}
