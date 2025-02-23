#include <PZEM004Tv30.h>

PZEM004Tv30 pzemR(&Serial1);
PZEM004Tv30 pzemY(&Serial2);
PZEM004Tv30 pzemB(&Serial3);

void setup()
{
    pinMode(13, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);
    Serial.begin(9600);
    delay(2000); // Allow sensor to initialize
}

class Phase
{
public:
    float voltage, current, power, energy, frequency, powerFactor;
    Phase(float v, float c, float p, float e, float f, float pf) : voltage(v), current(c), power(p), energy(e), frequency(f), powerFactor(pf) {}
};

void logic(float r, float y, float b, float l, int s1, int s2, int s3)
{
    if (s1)
        r -= l;
    if (s2)
        y -= l;
    if (s3)
        b -= l;

    float diff1 = abs(r - y);
    float diff2 = abs(y - b);
    float diff3 = abs(r - b);

    // All powers are equal
    if (!diff1 & !diff2 & !diff3)
    {
        digitalWrite(13, 0);
        digitalWrite(14, 0);
        digitalWrite(15, 0);
    }

    // Difference between power of R phase and Y phase is highest
    if (diff1 > diff2 && diff1 > diff3)
    {
        if (r < y)
        {
            digitalWrite(13, 1);
            digitalWrite(14, 0);
            digitalWrite(15, 0);
        }
        else
        {
            digitalWrite(13, 0);
            digitalWrite(14, 1);
            digitalWrite(15, 0);
        }
    }

    // Difference between power of Y phase and B phase is highest
    if (diff2 > diff1 && diff2 > diff3)
    {
        if (r < b)
        {
            digitalWrite(13, 0);
            digitalWrite(14, 1);
            digitalWrite(15, 0);
        }
        else
        {
            digitalWrite(13, 0);
            digitalWrite(14, 0);
            digitalWrite(15, 1);
        }
    }

    // Difference between power of R phase and B phase is highest
    if (diff3 > diff1 && diff3 > diff1)
    {
        if (r < y)
        {
            digitalWrite(13, 1);
            digitalWrite(14, 0);
            digitalWrite(15, 0);
        }
        else
        {
            digitalWrite(13, 0);
            digitalWrite(14, 0);
            digitalWrite(15, 1);
        }
    }
}

void loop()
{
    // R-phase
    float voltageR = pzemR.voltage();
    float currentR = pzemR.current();
    float powerR = pzemR.power();
    float energyR = pzemR.energy();
    float frequencyR = pzemR.frequency();
    float pfR = pzemR.pf();

    // Y-phase
    float voltageY = pzemY.voltage();
    float currentY = pzemY.current();
    float powerY = pzemY.power();
    float energyY = pzemY.energy();
    float frequencyY = pzemY.frequency();
    float pfY = pzemY.pf();

    // B-phase
    float voltageB = pzemB.voltage();
    float currentB = pzemB.current();
    float powerB = pzemB.power();
    float energyB = pzemB.energy();
    float frequencyB = pzemB.frequency();
    float pfB = pzemB.pf();

    // Switches condition
    auto s1 = digitalRead(13);
    auto s2 = digitalRead(14);
    auto s3 = digitalRead(15);

    // Phase R_Phase(voltageR, currentR, powerR, energyR, frequencyR, pfR);
    // Phase Y_Phase(voltageY, currentY, powerY, energyY, frequencyY, pfY);
    // Phase B_Phase(voltageB, currentB, powerB, energyB, frequencyB, pfB);

    logic(R_Phase.power, Y_Phase.power, B_Phase.power, s1, s2, s3);
    delay(10000);
}

void loop()
{
    float voltage = pzem.voltage();
    if (isnan(voltage))
    {
        Serial.println("Error: No data received from PZEM!");
    }
    else
    {
        Serial.print("Voltage: ");
        Serial.println(voltage);
    }

    float current = pzem.current();
    if (isnan(current))
    {
        Serial.println("Error: No data received from PZEM!");
    }
    else
    {
        Serial.print("Current: ");
        Serial.println(current);
    }

    float power = pzem.power();
    if (isnan(power))
    {
        Serial.println("Error: No data received from PZEM!");
    }
    else
    {
        Serial.print("Power: ");
        Serial.println(power);
    }

    float energy = pzem.energy();
    if (isnan(energy))
    {
        Serial.println("Error: No data received from PZEM!");
    }
    else
    {
        Serial.print("Energy: ");
        Serial.println(energy);
    }

    float frequency = pzem.frequency();
    if (isnan(frequency))
    {
        Serial.println("Error: No data received from PZEM!");
    }
    else
    {
        Serial.print("Frequency: ");
        Serial.println(frequency);
    }

    float pf = pzem.pf();
    if (isnan(pf))
    {
        Serial.println("Error: No data received from PZEM!");
    }
    else
    {
        Serial.print("Power Factor: ");
        Serial.println(pf);
    }

    delay(2000);
}