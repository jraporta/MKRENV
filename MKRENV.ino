#include <Arduino_MKRENV.h>
#include <SPI.h>
#include <SD.h>
#include "RoundRobinbyJR.h"

File myFile;
char fileName[20] = "reg24h.txt";
const int trigger = 12*25;
const int logsToRemove = 12;
unsigned long Time = 5*60*1000;
unsigned long prevTime = 0;

void setup() {
  Serial.begin(9600);

  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

void loop() {
  String serialInput = "";
  if ((prevTime + Time) < millis()) {
    getENVValues();
    prevTime = millis();
    if (NumberOfLogs(fileName) >= trigger) {
      Serial.print("Deleting oldest logs.....");
      RemoveOldLogs(fileName, trigger, logsToRemove);
      Serial.println("done.");
    }
  }
  while (Serial.available()) {
    serialInput += char(Serial.read());
  }
  if (serialInput == "check") {
    fileInfo();
  }
}

void getENVValues() {
  // read all the sensor values
  float temperature = ENV.readTemperature();
  float humidity    = ENV.readHumidity();
  float pressure    = ENV.readPressure();
  //  float illuminance = ENV.readIlluminance();
  float uva         = ENV.readUVA();
  float uvb         = ENV.readUVB();
  float uvIndex     = ENV.readUVIndex();

  myFile = SD.open(fileName, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to ");
    Serial.print(fileName);
    Serial.print(" .....");
    unsigned int prueba = millis();
    myFile.print(int(millis() / 1000.0));
    myFile.print(" s ");
    myFile.print(temperature);
    myFile.print(" °C ");
    myFile.print(humidity);
    myFile.print(" % ");
    myFile.print(pressure);
    myFile.print(" kPa ");
    myFile.print(uva);
    myFile.print(" UVA ");
    myFile.print(uvb);
    myFile.print(" UVB ");
    myFile.print(uvIndex);
    myFile.println(" UVIndex");
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening test.txt");
  }
}

void fileInfo() {
  Serial.print(fileName);
  Serial.print(" contains ");
  int num = NumberOfLogs(fileName);
  Serial.print(num);
  Serial.println(" logs.\nShowing contents...");
  PrintFile(fileName);
}
