#include <Servo.h>

int LED_VD = 11;
int LED_VM = 13;
int degree;
Servo SM;

void ligaMotor()
{
    digitalWrite(LED_VD, LOW);
    digitalWrite(LED_VM, HIGH);
}

void desligaMotor()
{
    digitalWrite(LED_VD, HIGH);
    digitalWrite(LED_VM, LOW);
}

void setup()
{
    Serial.begin(9600);
    pinMode(LED_VM, OUTPUT);
    pinMode(LED_VD, OUTPUT);
    SM.attach(9);
}

void loop()
{
    SM.write(0);
    desligaMotor();

    if (Serial.available() > 0)
    {
        degree = Serial.parseInt();

        if (degree >= 0 && degree <= 180)
        {
            Serial.println("REALIZANDO MOVIMENTO!");
            SM.write(degree);
            ligaMotor();
            delay(1000);
            desligaMotor();
            delay(4000);
            SM.write(0);
            ligaMotor();
            delay(1000);
        }
        else
        {
            Serial.println("ERRO!");
        }
    }
}