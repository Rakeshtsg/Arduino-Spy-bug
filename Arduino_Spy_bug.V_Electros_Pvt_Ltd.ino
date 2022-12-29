/*
  File: example.ino
  Author: Rakesh T S V.Electros Pvt Ltd
  Date: 1/1/2022
  Description: Arduino Spy bug An Arduino spy bug is a small electronic device that is designed to be hidden in a location and used to secretly record audio 
  These devices are often used for surveillance or espionage, and they can be made using a small microcontroller such as an Arduino board and a microphone or other sensor.
*/


#include <TMRpcm.h>
#include <SD.h>
#include <SPI.h>
TMRpcm audio;
int file_number = 0;
char filePrefixname[50] = "spy";
char exten[10] = ".wav";
const int recordLed = 2;
const int mic_pin = A0;
const int sample_rate = 84000;

#define SD_CSPin 4
// delay function for with serial log.

void wait_min(int mins) {
  int count = 0;
  int secs = mins * 60;
  while (1) {
    Serial.print('.');
    delay(1000);
    count++;
    if (count == secs) {
      count = 0;
      break;
    }
  }
  Serial.println();
  return ;
}
void setup() {
  // put your setup code here, to run once:
  //initialises the serial connection between the arduino and any connected serial device(e.g. computer, phone, raspberry pi...)
  Serial.begin(9600);
  //Sets up the pins
  pinMode(mic_pin, INPUT);
  pinMode(recordLed, OUTPUT);
  Serial.println("loading... SD card");
  if (!SD.begin(SD_CSPin)) {
    Serial.println("An Error has occurred while mounting SD");
  }
  while (!SD.begin(SD_CSPin)) {
    Serial.print(".");
    delay(500);
  }
  audio.CSPin = SD_CSPin;
}
void loop() {
  Serial.println("####################################################################################");
  char fileSlNum[20] = "";
  itoa(file_number, fileSlNum, 10);
  char file_name[50] = "";
  strcat(file_name, filePrefixname);
  strcat(file_name, fileSlNum);
  strcat(file_name, exten);
  Serial.print("New File Name: ");
  Serial.println(file_name);
  digitalWrite(recordLed, HIGH);
  audio.startRecording(file_name, sample_rate, mic_pin);
  Serial.println("startRecording ");
  // record audio for 2mins. means , in this loop process record 2mins of audio.
  // if you need more time duration recording audio then
  // pass higher value into the wait_min(int mins) function.
  wait_min(1);
  digitalWrite(recordLed, LOW);
  audio.stopRecording(file_name);
  Serial.println("stopRecording");
  file_number++;
  Serial.println("####################################################################################");
}
