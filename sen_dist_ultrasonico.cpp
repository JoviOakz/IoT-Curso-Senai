#include <LiquidCrystal.h>

#define TRIGGER 13
#define ECHO 12
#define LDR A0

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int current_time_millis;
int time_passed_millis;
bool is_emitting;

int ldr_read()
{
    return analogRead(LDR);
}

double measure_distance()
{
    unsigned long duration = pulseIn(ECHO, HIGH);
    return duration * 0.034 / 2;
}

void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 2);

    pinMode(LDR, INPUT);
    pinMode(ECHO, INPUT);
    pinMode(TRIGGER, OUTPUT);

    digitalWrite(TRIGGER, LOW);
    current_time_millis = millis();
    is_emitting = false;
}

void loop()
{
    time_passed_millis = millis() - current_time_millis;

    if (is_emitting && (time_passed_millis >= 20))
    {
        digitalWrite(TRIGGER, LOW);
        is_emitting = false;

        double distance = measure_distance();
        lcd.setCursor(0, 0);
        lcd.print(distance);

        int luminosity = ldr_read();
        lcd.setCursor(0, 1);
        lcd.print(luminosity);

        current_time_millis = millis();
    }
    else if (time_passed_millis >= 80)
    {
        digitalWrite(TRIGGER, HIGH);
        is_emitting = true;

        current_time_millis = millis();
    }
}