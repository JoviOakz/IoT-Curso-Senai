#include <Ethernet.h>
#include <SPI.h>

const int botaoPin = 3;
const int ledPin = 2;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

IPAddress ip(10, 196, 49, 32);

EthernetClient client;

EthernetServer server(80);

void setup()
{
    Ethernet.begin();
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

    client = server.available();

    if (client)
    {
        boolean linhaEmBranco = true;

        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read();

                if (c == '\n' && linhaEmBranco)
                {
                    client.println("HTTP/ 1.1 200 ok");

                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println("Refresh: 2");
                    client.println("<!DOCTYPE HTML");
                    client.println();
                    client.println("<html>");
                    client.println("<center> <font size = 6> <p>Verificando o estado do LED</p> </font> </center>");
                    client.println("<b>" + estadoLed + "</b>");
                    client.println("</html>");
                    break;
                }

                if (c == '\n')
                {
                    linhaEmBranco = true;
                }
                else if (c != '\r')
                {
                    linhaEmBranco = false;
                }
            }
        }

        delay(10);
        client.stop();
    }
}