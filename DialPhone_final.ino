#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT


// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 46 bytes
  { 255,0,0,53,0,39,0,17,0,0,0,15,1,106,200,1,1,3,0,67,
  7,77,95,11,4,2,26,21,67,35,20,41,45,5,2,26,11,67,9,124,
  90,16,4,2,26,21 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  char text_01[21]; // string UTF8 end zero
  char text_02[11]; // string UTF8 end zero
  char text_03[21]; // string UTF8 end zero

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
#include <PCM.h>

int needToPrint = 0;
int count;
int in = 9;
int lastState = LOW;
int trueState = LOW;
long lastStateChangeTime = 0;
int cleared = 0;

int dialHasFinishedRotatingAfterMs = 100;
int debounceDelay = 10;

String number ="";
int zeroCount = 0;  

void setup()
{
  Serial.begin(115200);
  pinMode(in, INPUT);

  RemoteXY_Init (); 

}

void loop() {
    RemoteXY_Handler();  // Ensure RemoteXY interface communication is handled

    int reading = digitalRead(in);  // Read the state of the input pin

    if ((millis() - lastStateChangeTime) > dialHasFinishedRotatingAfterMs) {
        if (needToPrint) {
            int digit = (count - 1) % 10;  // Calculate the current dial digit

            number += String(digit);  // Append the digit to `number`
            needToPrint = 0;  // Reset the needToPrint flag
            count = 0;  // Reset the count
            cleared = 0; 
            Serial.print(" " + number);  // Print the current number to Serial Monitor
            strncpy(RemoteXY.text_01, number.c_str(), sizeof(RemoteXY.text_01) - 1);
            RemoteXY.text_01[sizeof(RemoteXY.text_01) - 1] = '\0'; 
            snprintf(RemoteXY.text_02, sizeof(RemoteXY.text_02), "%d", digit);  // Display current digit

            // Check for consecutive zeros
            if (digit == 0) {
                zeroCount++;
            } else {
                zeroCount = 0;
            }

            // If four consecutive zeros are detected it will reset the number (incase of missclicking the digits on the physical phone)
            if (zeroCount == 4) {
                number = "";
                strncpy(RemoteXY.text_03, "0000 detected", sizeof(RemoteXY.text_03) - 1);
                RemoteXY.text_03[sizeof(RemoteXY.text_03) - 1] = '\0';  
                zeroCount = 0; 
                strncpy(RemoteXY.text_01, number.c_str(), sizeof(RemoteXY.text_01) - 1);  
                RemoteXY.text_01[sizeof(RemoteXY.text_01) - 1] = '\0'; 
            } else {
                RemoteXY.text_03[0] = '\0';  // this should only be typed as an else only once or nothing will ever get displayed on text_03 
            }
        }
    }

    if (reading != lastState) {
        lastStateChangeTime = millis();  // Update the last state change time
    }

    if ((millis() - lastStateChangeTime) > debounceDelay) {
        if (reading != trueState) {
            trueState = reading;
            if (trueState == HIGH) {
                count++;
                needToPrint = 1;  
            }
        }
    }

    lastState = reading;  // Update the last state variable

    
    if (number == "1234") {
        number = "";  // Clear the number
        strncpy(RemoteXY.text_03, "Secret", sizeof(RemoteXY.text_03) - 1); 
        RemoteXY.text_03[sizeof(RemoteXY.text_03) - 1] = '\0';
    } else {
         // BAAAAAAAAAAAAAAJJJJJJJJJSSSSSSSSS
    }
    if (number == "1337") {
        number = ""; 
        strncpy(RemoteXY.text_03, "ELIT", sizeof(RemoteXY.text_03) - 1); 
        RemoteXY.text_03[sizeof(RemoteXY.text_03) - 1] = '\0';
    }
    if (number == "049191262") {
        number = ""; 
        strncpy(RemoteXY.text_03, "lös: p13_f4c3", sizeof(RemoteXY.text_03) - 1); 
        RemoteXY.text_03[sizeof(RemoteXY.text_03) - 1] = '\0';
    }
    if (number == "0123456789") {
        number = ""; 
        strncpy(RemoteXY.text_03, "ABCDEFGHIJ", sizeof(RemoteXY.text_03) - 1); 
        RemoteXY.text_03[sizeof(RemoteXY.text_03) - 1] = '\0';
    }
    if (number == "112") {
        number = ""; 
        strncpy(RemoteXY.text_03, "Vad har inträffat?", sizeof(RemoteXY.text_03) - 1); 
        RemoteXY.text_03[sizeof(RemoteXY.text_03) - 1] = '\0';
    }
       if (number == "31415") {
        number = ""; 
        strncpy(RemoteXY.text_03, "YUMMY PIE", sizeof(RemoteXY.text_03) - 1); 
        RemoteXY.text_03[sizeof(RemoteXY.text_03) - 1] = '\0';
    }
      if (number == "666") {
        number = ""; 
        strncpy(RemoteXY.text_03, ">:)", sizeof(RemoteXY.text_03) - 1); 
        RemoteXY.text_03[sizeof(RemoteXY.text_03) - 1] = '\0';
    }
      if (number == "11414") {
        number = ""; 
        strncpy(RemoteXY.text_03, "POLISEN KOMMER", sizeof(RemoteXY.text_03) - 1); 
        RemoteXY.text_03[sizeof(RemoteXY.text_03) - 1] = '\0';
    }
     if (number == "1177") {
        number = ""; 
        strncpy(RemoteXY.text_03, "synd synd", sizeof(RemoteXY.text_03) - 1); 
        RemoteXY.text_03[sizeof(RemoteXY.text_03) - 1] = '\0';
    }
  
}

