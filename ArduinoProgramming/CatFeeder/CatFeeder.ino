#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(0, 1); // RX, TX

Servo myservo;  // create servo object

int pos = 0;    // variable to store the servo position
int data;       // variable to store recieved data
int openclosed = 0; // variable that indicates whether the container is open (1) or closed (0)

void setup() {
  pos = 0;
  openclosed = 0;
  Bluetooth.begin(9600);
  Serial.begin(9600);
  // attaches the servo to pin 9
  myservo.attach(9);  
  myservo.write(pos);  
}

void loop() {
  // Check if data is available on the serial port
  if (Bluetooth.available()){ //wait for data to be received
    data = Bluetooth.read();
    if(data == '1'){ // 1 = open/close command
      openclosed = !openclosed; // if it was open, then close it an
      if(openclosed == 1) {
        for (int p = pos; pos <= 60; pos += 2) { // pos goes from 0 degrees to 60 degrees in steps of 2 degrees
          myservo.write(pos);                    // tell servo to go to position pos
          delay(15); 
        }
      } else if(openclosed == 0) {
        for (int p = pos; pos >= 0; pos -= 2) { // pos goes from 60 degrees to 0 degrees
          myservo.write(pos);                  // tell servo to go to position pos
          delay(15);
        }
      }
    }
  }
  delay(100);
}
