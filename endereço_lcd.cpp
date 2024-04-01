// Segue Código que retorno o endereço do display lcd i2c

#include <Wire.h>

void setup()
{
    Serial.begin(9600); // Inicializa a comunicação serial
    Wire.begin();       // Inicializa a biblioteca Wire para comunicação I2C
}

void loop()
{
    byte error, address;
    int nDevices;

    Serial.println("Scanning...");

    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        // Solicitação ao dispositivo
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        // Verifica se há resposta do dispositivo
        if (error == 0)
        {
            Serial.print("Dispositivo encontrado no endereço 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Erro desconhecido no endereço 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("Nenhum dispositivo encontrado.");
    else
        Serial.println("Fim da verificação.");

    delay(5000); // Espera 5 segundos antes de realizar uma nova verificação
}