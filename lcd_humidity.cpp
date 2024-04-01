#include <LiquidCrystal_I2C.h>

const uint8_t PIN_TMP = A0;
const uint8_t PIN_MOIST = A1;

LiquidCrystal_I2C lcd(0x20, 16, 2);

double moisture;
double temperature;

double get_voltage()
{
    double aux = analogRead(PIN_TMP);
    return (aux / 1024) * 5;
}

void setup()
{
    Serial.begin(9600);

    pinMode(PIN_TMP, INPUT);
    pinMode(PIN_MOIST, INPUT);

    lcd.init();
}

void loop()
{
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 0);

    temperature = (get_voltage() - 0.5) * 100;
    moisture = analogRead(PIN_MOIST);

    Serial.println(temperature);
    Serial.println(moisture);

    lcd.print(temperature);
    lcd.setCursor(0, 1);
    lcd.print(moisture);
}