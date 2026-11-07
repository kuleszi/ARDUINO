void setup() {
  //connecting LEDs
 pinMode(13, OUTPUT); // red to pin 13
 pinMode(12, OUTPUT); // yellow to pin 12
 pinMode(11, OUTPUT); // green to pin 11
 Serial.begin(9600); //initialization of serial communication at 9600 bits per second
}

void loop() {
  Loop for the average reading:
  int sum = 0; //a variable that will be the sum of the first 5 readings
  for (int i = 0; i < 5; i++){
    //with each iteration we add the value from the potentiometer to the sum
    sum += analogRead(A0); //analogRead(A0) retrieves data from the potentiometer connected to input A0
    delay(1); //we wait 1ms and collect the next reading
  }

  int sensorValue = sum/5; //for the value we will use in the delay between the LED flashes, we take the value of the sum of our 5 readings made by the loops and divide it by 5 - which gives us our average
  sensorValue = map(sensorValue, 0, 1023, 300, 1500); //then we insert our average into the map() function, which allows us to convert a given value into different ranges

  //Signaling system:
  //STOP PHASE
  digitalWrite(13, HIGH); //only the red LED is lit - we are standing still
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  Serial.println("STOP"); //the appropriate text is displayed in the serial monitor (println cannot be called before the diode lights up, because then the commands in the console will be displayed in the wrong phase)
  delay(sensorValue); //we wait for the next stage for as long as the speed selected on the potentiometer (average value)

  //READY PHASE
  digitalWrite(13, HIGH); //red LED is still lit
  digitalWrite(12, HIGH); //we add the yellow one - we are preparing for take-off 
  digitalWrite(11, LOW);
  Serial.println("READY"); //the appropriate text is displayed in the serial monitor
  delay(sensorValue); //we wait for the next stage for as long as the speed selected on the potentiometer (average value)

  //GO PHASE
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH); //the two previous LEDs go out, the green one lights up - let's go
  Serial.println("GO"); //the appropriate text is displayed in the serial monitor
  delay(sensorValue); //we wait for the next stage for as long as the speed selected on the potentiometer (average value)

  //END PHASE
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH); //the green LED turns off, only the yellow one lights up - we stop
  digitalWrite(11, LOW);
  Serial.println("END"); //the appropriate text is displayed in the serial monitor
  delay(sensorValue); //we wait for the next stage for as long as the speed selected on the potentiometer (average value)

  //the end, we go back to the beginning
}
