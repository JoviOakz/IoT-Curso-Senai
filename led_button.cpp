const int botaoPin = 3;
const int ledPin = 2;

void setup()
{
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(botaoPin, INPUT);
}

String leEstadoLed()
{
    if (digitalRead(botaoPin) == HIGH)
    {
        digitalWrite(ledPin, HIGH);
        return "Aceso";
    }
    else
    {
        digitalWrite(ledPin, LOW);
        return "Apagado";
    }
}

void loop()
{
    String estadoLed = leEstadoLed();
    Serial.println(estadoLed);
    delay(500);
}