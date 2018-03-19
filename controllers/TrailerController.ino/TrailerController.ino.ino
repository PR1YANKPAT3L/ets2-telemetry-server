/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
#include <ArduinoJson.h>

int incomingByte = 0;
char inData[20]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character
String data = "";
char* actualData = "";
#define INPUT_SIZE 100

// the setup routine runs once when you press reset:
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

void parseData(char* data) {
  //  Serial.println("DATA: " + data);

  char* command = strtok(data, "&");
  while (command != 0) {
    char* sep = strchr(command, ':');
    if (sep != 0) {
      *sep = 0;
      int spd = atoi(command);
      ++sep;
      int pos = atoi(sep);

      Serial.println(pos);
    }
  }
}

// the loop routine runs over and over again forever:
void loop() {
  //  digitalWrite(LED_BUILTIN, LOW);
  //  // send data only when you receive data:
  //  if (Serial.available() > 0) {
  //    if (index < 19) // One less than the size of the array
  //    {
  //      inChar = Serial.read(); // Read a character
  //      inData[index] = inChar; // Store it
  //      index++; // Increment where to write next
  //      inData[index] = '\0'; // Null terminate the string
  //    }
  //    Serial.print("LOL: ");
  //    Serial.print(inData);
  //    delay(100);
  //    // read the incoming byte:
  //    //    incomingByte = Serial.read();
  //    //    data = Serial.readString();
  //    //
  //    //    // say what you got:
  //    //    Serial.print("I received: ");
  //    //    //    Serial.println(incomingByte, DEC);
  //    //    Serial.println(data);
  //    //    digitalWrite(LED_BUILTIN, HIGH);
  //
  //  }

  if (Serial.available() > 0) {
    inChar = Serial.read();
    data += char(inChar);

    if (data == "START") {
      Serial.println("STARTING");
      data = "";
    } else {
      if (char(inChar) == '}') {
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& root = jsonBuffer.parseObject(data);
        if (!root.success()) {
          Serial.println("FAILED");
        } else {
          const char* inParkMode = root["inParkMode"];
          double truckSpeed = root["speed"];
          double truckAngle = root["angle"];
          Serial.println("");
          Serial.print("SPEED:");
          Serial.print(truckSpeed);
          Serial.print("|ANGLE");
          Serial.print(truckAngle);
          Serial.println("");
        }

        data = "";
      }
    }
    //
    //    if (data == "START")
    //    {
    //      Serial.println("STARTING");
    //      data = "";
    //    } else {
    //      Serial.println(data);
    ////      if (char(inChar) == '{') {
    ////        actualData += char(inChar);
    ////
    ////        if (char(inChar) == '}') {
    ////          StaticJsonBuffer<200> jsonBuffer;
    ////
    ////          JsonObject& root = jsonBuffer.parseObject(actualData);
    ////          actualData = "";
    ////          if (!root.success()) {
    ////            Serial.println("FAILED");
    ////          } else {
    ////            Serial.println("WORKS");
    ////          }
    ////          data = "";
    ////        }
    ////      }
    //    }
  }
}
