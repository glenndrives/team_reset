/*
This project will take the button inputs from the TALLYH0 Photon and open a relay
on the TALLYH1 Photon. This is to give Master Control remote reset capabilites
for the TEAM unit at Driver.
*/

unsigned long lastTime;

void setup() {

Particle.subscribe("Studio", CloudHandler, "370050001551353531343431");
// Particle.subscribe("Studio", PingHandler, "370050001551353531343431");
// Particle.subscribe("team_reset", ResetTeam, "370050001551353531343431");
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
