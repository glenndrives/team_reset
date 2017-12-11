/*
This project will take the button inputs from the TALLYH0 Photon and open a relay
on the TALLYH1 Photon. This is to give Master Control remote reset capabilites
for the TEAM unit at Driver.
*/

// Status LEDs
int greenLed = D0; // Indicates connectivity to the Driver unit
int redLed = D1;  // On for a period of time after a reset to indicate success.
// Push Buttons
int buttonOne = D2;
int buttonTwo = D3;

int pingInterval = 14; // Chnage this value to set the time between pings in seconds
int buttonDelay = 3; // Delay in seconds both buttons have to be pressed before a reset is sent

bool pingReply = FALSE;  // Indicates a successful ping response
bool resetSent = FALSE;  // Used to indicate a reset was sent for turning off the red LED
bool buttonsPressed = FALSE;  // Indicate both buttons have been pressed

unsigned long lastPing; // Placeholder for ping interval
unsigned long lastReset; // Time last reset was sent to reset the red reset light
unsigned long lastButtonsPressed;  // Time both buttons were pressed


void setup() {
    // Start serial for debugging
    Serial.begin(115200);
    Particle.subscribe("Driver", PingHandler, "2c0028000851353531343431");

// Setup the Digital pins
pinMode(greenLed, OUTPUT);
pinMode(redLed, OUTPUT);
pinMode(buttonOne, INPUT_PULLUP);
pinMode(buttonTwo, INPUT_PULLUP);

}

void loop() {
    digitalWrite(redLed, !digitalRead(buttonTwo));  // turn on red LED when button two is pressed. Testing
    
    if ((Time.now() - lastPing) > pingInterval) {  // Ping Driver to test connectivity
        if (!pingReply) {              // Turn off LED if there is no ping reply from Driver
            digitalWrite(greenLed, 0);
        }
        pingReply = FALSE;  // Set ping reply to FALSE before pinging Driver
        Particle.publish("Studio", "ping");  // Publish ping to get Driver to respond
        
    lastPing = Time.now();
    }
    
    if ((digitalRead(buttonOne) == 0) && (digitalRead(buttonTwo) == 0)) {  // Enter if both buttons pressed
        delay(300);  // Debounce 
        if (!buttonsPressed) {  // If previous state of buttonsPressed is FALSE set to true
            buttonsPressed = TRUE;
            lastButtonsPressed = Time.now();  // Set the last time the buttons were pressed
            Serial.println("buttonsPressed: %s lastButtonsPressed: %d", btoa(buttonsPressed), lastButtonsPressed);
        }
        if ((Time.now() - lastButtonsPressed) > buttonDelay) {
            Serial.println("Reset\n\n");
        }
    }
    else {
        buttonsPressed = FALSE;  // If the buttons aren't pressed set to FALSE to reset cycle
    }


}
// This function is called when the Particle.subscribe("Driver"... gets pong
void PingHandler(const char *event, const char *data) {
    if(String(data) == "pong") {
        digitalWrite(greenLed, 1);  // Set the green LED on if Driver responds
        pingReply = TRUE;  // Set to TRUE on ping response to keep LED on between pings
    }
}
