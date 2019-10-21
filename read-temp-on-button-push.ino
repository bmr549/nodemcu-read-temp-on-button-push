/*

  read-temp-on-button-push

  When a button is pressed completely, a single temperature value is read from
  an attached TMP36 analog temperature sensor.

  The temperature is only read after the button has been realeased.
 
 */

const int PROBE = A0;
const int BUTTON = 16;

float buttonState, lastButtonState;

void setup() {

  Serial.begin(9600);
  pinMode(PROBE, INPUT);
  pinMode(BUTTON, INPUT);

  // prime our instance variables
  buttonState = digitalRead(BUTTON);
  lastButtonState = buttonState;
  
}

void loop() {

  buttonState = digitalRead(BUTTON);

  if (buttonState < 0.5 && lastButtonState >= 0.5) { // button cycle completed

    // read the probe's analog input (0-1023) and convert it into celsius
    // print via the serial connection
    int analogProbeInput = analogRead(PROBE);
    float celsius = convertAnalogInputToCelsius(analogProbeInput);
    
    Serial.print("Temperature (C°): "); Serial.println(celsius);
    
  }

  lastButtonState = buttonState;

  delay(50);
  
}

float convertAnalogInputToCelsius(int analogInput) {
  
  float celsius = ((( (float) analogInput / (float) 1024) * 3.3 - 0.5) * 1000) / 10;
  return celsius;
  
}
