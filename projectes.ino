int inputPin = D5;              // Input pin for PIR sensor
int buzzer = D7;                                 
int pirState = LOW;             // Default to no motion detected
int val = 0;                    // Variable used for reading the pin status

int calibrateTime = 10000;      // Wait for the sensor to calibrate

void setup()
{
  pinMode(inputPin, INPUT);     // Declare sensor as input
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
}


void loop()
{

  if (calibrated()) // If the sensor is calibrated
  {
  
    readTheSensor(); // Get the data from the sensor


    reportTheData(); // Report if the state has been changed
  }
  
  delay(1000);
  
}

void readTheSensor() 
{
  val = digitalRead(inputPin); // Reads sensor value
}

bool calibrated() 
{
  return millis() - calibrateTime > 0;
}

void reportTheData() {

  if (val == HIGH) 
  {

    if (pirState == LOW) 
    {
     
      Particle.publish("Motion Detected!"); // Publishes event that motion has been activated
      
      analogWrite(buzzer, 50); // Activate buzzer if motion is detected
      delay(500);
      analogWrite(buzzer, 0);
      delay(250);
      analogWrite(buzzer, 100);
      delay(500);
      analogWrite(buzzer, 0);
      

      pirState = HIGH; // State is HIGH
      
    }
  } 
  else 
  {
      
    if (pirState == HIGH) 
    {
      pirState = LOW; // State is LOW if no motion is detected
    }
    
  }
}


