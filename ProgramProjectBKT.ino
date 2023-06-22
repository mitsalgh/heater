//         ##********PROJECT HMI BERDINE CREATIVE TEKNOLOGI**********##
int Volt_in = 7 ;
int Curr_in = 8 ;
float Volt_set = 0;             //Variables for the ones voltage values 
float Volt_ten_set = 0;         //Variables for the tenths voltage values 
float Volt_hun_set = 0;         //Variables for the hundredths voltage values 
float Curr_set = 0;             //Variables for the ones current values 
float Curr_ten_set = 0;         //Variables for the tenths current values 
float Curr_hun_set = 0;         //Variables for the hundredths current values 
float pow_set = 0;             //Variables for the ones current values 
float pow_ten_set = 0;         //Variables for the tenths current values 
float pow_hun_set = 0; 
float hertz_set = 0;             //Variables for the ones current values 
float hz_ten_set = 0;         //Variables for the tenths current values 
float hz_hun_set = 0; 

float Voltage_set = 0.0;        //Here we save the final voltage value (teh sum of all 3 votage variables above)
float Current_set = 0.0;
float Power_set = 0.0;
float Hertz_set = 0.0;          //Here we save the final current value (teh sum of all 3 current variables above)

int Real_Voltage = 0;           //Variable for the real read of the voltage output
int Real_Current = 0;           //Variable for the real read of the current value
int Real_Power = 0;    
int Real_Hertz = 0 ;         //The power will be current*voltage

bool output_enabeled = false;   //This will show if the output is enabeled or not

void setup() 
{
 pinMode(Volt_in,INPUT);
 pinMode(Curr_in,INPUT);
 Serial.begin(9600);          //Default baud rate of the Nexion TFT is 9600!
 /*Uncomment and delete this line if you want to change baud rate to 115200
 Serial.print("bauds=115200");
 Serial.write(0xff);
 Serial.write(0xff);
 Serial.write(0xff);
 Serial.print("cle 5,255");   //Send instruction to clear the waveform
 Serial.write(0xff);
 Serial.write(0xff);
 Serial.write(0xff);*/
}


void loop() {
  
  if(Serial.available()>0)
  {
    String Received  = Serial.readString();     //get the received string from the display
    //Serial.println(Received);
    
    if(Received[0] == 'b')                      /*In the display code, when the back button is pressed I send all the variables
    But first I send the "b" character. That's why, when we detect a "b", then we store each forth character as a float value. 
    why each forth? because after each sent value, the uartt will write 3 full bytes as seen before*/
    {
      Volt_set = float(Received[1]);        //First, than the 5th, than the 9th etc...
      Volt_ten_set = float(Received[5]);
      Volt_hun_set = float(Received[9]);
      
      Curr_set = float(Received[13]); 
      Curr_ten_set = float(Received[17]); 
      Curr_hun_set = float(Received[21]); 

      pow_set = float(Received[25]);
      pow_ten_set = float(Received[29]);
      pow_hun_set = float(Received[33]);

      hertz_set = float(Received[37]);
      hz_ten_set = float(Received[41]);
      hz_hun_set = float(Received[45]);

      Voltage_set = Volt_set + (Volt_ten_set/10) + (Volt_hun_set/100);      //We summ all parts to get the total set voltage value
      Current_set = Curr_set + (Curr_ten_set/10) + (Curr_hun_set/100);      //We summ all parts to get the total set current value

     /* 
      Serial.println(Volt_set);
      Serial.println(Volt_ten_set);
      Serial.println(Volt_hun_set);  
      Serial.println(Curr_set);
      Serial.println(Curr_ten_set);
      Serial.println(Curr_hun_set); //Uncomment this for serial debug
      */
    }   
     
    if(Received[1] == 'f')                //if we receive an f, then the output will turn off
    {
      output_enabeled = false;
      Serial.print("Output: ");
      Serial.println(output_enabeled);
    }    

     if(Received[1] == 'n')               //if we receive an n, then the output will turn on
    {
      output_enabeled = true;
      Serial.print("Output: ");
      Serial.println(output_enabeled);
    }   
  }//end of if serial
/*
 Real_Voltage = map(analogRead(Volt_in),0,1024,0,3200);     Read the values of the potentiometers and map the output to 0 to 3200 In the display code in the timer, we divide 3200 in such a way that we het 32,00 volts. 
 Real_Current = map(analogRead(Curr_in),0,1024,0,300);      //Read the values of the potentiometers
 Real_Power = Real_Voltage/100*Real_Current;                //Get the power
 */
 Serial.print("Real_Voltage.val="); //The variable we will change on nthe screen, in this case the voltage value
 Serial.print(Real_Voltage);        //Send the voltage value
 Serial.write(0xff);
 Serial.write(0xff);
 Serial.write(0xff);
 Serial.print("Real_Current.val="); //The variable we will change on nthe screen, in this case the current value
 Serial.print(Real_Current);        //Send the current value
 Serial.write(0xff);
 Serial.write(0xff);
 Serial.write(0xff);
 Serial.print("Real_Power.val="); //The variable we will change on nthe screen, in this case the power value
 Serial.print(Real_Power);        //Send the power value
 Serial.write(0xff);
 Serial.write(0xff);
 Serial.write(0xff);
 Serial.print("Real_Hertz.val="); //The variable we will change on nthe screen, in this case the power value
 Serial.print(Real_Hertz);        //Send the power value
 Serial.write(0xff);
 Serial.write(0xff);
 Serial.write(0xff);
}

