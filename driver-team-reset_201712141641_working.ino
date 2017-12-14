/*
This project will take the button inputs from the TALLYH0 Photon and open a relay
on the TALLYH1 Photon. This is to give Master Control remote reset capabilites
for the TEAM unit at Driver.
*/

#include <NCD4Relay.h>  // Relay control library
NCD4Relay rc;  // Initialize the relay control library
unsigned long lastTime;

void setup() {

rc.setAddress(0,0,0);  // Set realay controller board address
rc.turnOffAllRelays();  // Make sure all relays are off

Particle.subscribe("Studio", CloudHandler, "370050001551353531343431");

}

void loop() {
/*    
    if ((Time.now() - lastTime) > 120) {
        Particle.publish("Driver", "online");
        
    lastTime = Time.now();
    }
*/
}

void CloudHandler(const char *event, const char *data) {
    if (String(data) == "ping") {  // Respond to the ping from Studio
        Particle.publish("Driver", "pong");
    }
    if (String(data) == "reset") {
        Particle.publish("Driver", "got_reset");
        rc.turnOnRelay(1);
        delay(3000);
        rc.turnOffRelay(1);
        Particle.publish("Driver", "reset_done");
        
    }
    
}

/*
void PingHandler(const char *event, const char *data) {
    Particle.publish("Driver", "pong");
}

void ResetTeam(const char *event, const char *data) {
    if (String(data) == "reset") {
        // Reset code here.
    }
}
*/
