#include <SD.h>
#include <SPI.h>
#define CS_PIN 4 //Chip select pin for SD Card module

int f=30; //sampling frequency

File myFile;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  pinMode(CS_PIN, OUTPUT);
  
  Serial.print("Initializing SD card...");

  if (!SD.begin(CS_PIN)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  char a='a';
  if (Serial.read()==a){
    myFile = SD.open("test.csv", FILE_WRITE);
    if (myFile) {
      long time1=millis();
      while(millis()-time1<10000){ //data collection over a period of 60sec
        long tmpTime=millis();
        int data;
        long timeStamp;
        while(millis()-tmpTime<1000/f){ // data collection every 20ms
          data = map(analogRead(A0),0,1023,0,5000);
          timeStamp = millis();
          // close the file:
        }
        Serial.print(data);
        Serial.print(" , ");
        Serial.println(timeStamp);
        myFile.print(data);
        myFile.print(" , ");
        myFile.println(timeStamp);
        //myFile.println(data + " , " + timeStamp);
      }
      // close the file:
      myFile.close();
      Serial.println("done.");
    }
    else {
      // if the file didn't open, print an error:
      Serial.println("error opening breathing_data.csv");
    }
  }

}
