#include <string>
#include <cstdlib>
#include <ctime>

const int LIGHT_SENSOR = A5;
bool sunlight_hit_triggered = false;
bool sunlight_stop_triggered = false;

void trigger_sunlight_hit()
{
    if (sunlight_hit_triggered) return;
    
    Particle.publish("SunlightHitTerrarium", "", PRIVATE);
    sunlight_hit_triggered = true;
    sunlight_stop_triggered = false;
}

void trigger_sunlight_stopped()
{
    if (sunlight_stop_triggered) return;
    
    Particle.publish("SunlightStoppedHittingTerrarium", "", PRIVATE);
    sunlight_stop_triggered = true;
    sunlight_hit_triggered = false;
}

void setup()
{
    pinMode(LIGHT_SENSOR, INPUT);
}

void loop()
{
    int light = analogRead(LIGHT_SENSOR);
    
    // I do have an actual light sensor connected, but I'm going to use fake values to test the IFTTT trigger more easily.
    light = rand() % 4000;
    
    if (light > 2000) trigger_sunlight_hit();
    else trigger_sunlight_stopped();

    delay(10000);
}