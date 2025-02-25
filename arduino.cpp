// Define the analog pin connected to ZMPT101B sensor
#define sensorR A0
#define sensorY A1
#define sensorB A2
#define sensorL A3
#define switch1 31
#define switch2 32
#define switch3 33

// Calibration factor (adjust based on actual readings)
#define CALIBRATION_FACTOR 100.0

#define VREF 5.0                  // Reference voltage (5V for Arduino Mega)
#define SENSOR_SENSITIVITY 140    // Sensitivity in mV/A (100mV/A for ACS712-20A)
#define ZERO_CURRENT_VOLTAGE 2500 // 2.5V at 0A (in mV)
#define NUM_SAMPLES 500           // Number of samples for RMS calculation

void setup()
{
    Serial.begin(9600); // Start serial communication
    pinMode(sensorR, INPUT);
    pinMode(sensorY, INPUT);
    pinMode(sensorB, INPUT);
    pinMode(sensorL, INPUT);
    pinMode(switch1, OUTPUT);
    pinMode(switch2, OUTPUT);
    pinMode(switch3, OUTPUT);
}

float getRMSCurrent(int sensorPin)
{
    float sumSquaredCurrent = 0;

    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        int adcValue = analogRead(sensorPin);
        float voltage = (adcValue / 1023.0) * VREF * 1000;                     // Convert ADC to mV
        float current = (voltage - ZERO_CURRENT_VOLTAGE) / SENSOR_SENSITIVITY; // Convert to Amps

        sumSquaredCurrent += current * current; // Sum of squared values
        delayMicroseconds(10);                  // Short delay for sampling
    }

    return sqrt(sumSquaredCurrent / NUM_SAMPLES); // RMS Calculation
}

void loop()
{
    float voltage = 233.0;
    float current_R = getRMSCurrent(sensorR);
    Serial.println("---Power before---");
    float power_R = current_R * voltage;
    // Serial.print("R phase Current: ");
    // Serial.print(current_R, 3); // Print with 2 decimal places
    // Serial.println(" A");
    Serial.print("R phase Power: ");
    Serial.print(voltage * current_R, 2); // Print with 2 decimal places
    Serial.println(" W");

    float current_Y = getRMSCurrent(sensorY);
    float power_Y = current_Y * voltage;
    // Serial.print("Y phase Current: ");
    // Serial.print(current_Y, 3); // Print with 2 decimal places
    // Serial.println(" A");
    Serial.print("Y phase Power: ");
    Serial.print(voltage * current_Y, 2); // Print with 2 decimal places
    Serial.println(" W");

    float current_B = getRMSCurrent(sensorB);
    float power_B = current_B * voltage;
    // Serial.print("B phase Current: ");
    // Serial.print(current_B, 3); // Print with 2 decimal places
    // Serial.println(" A");
    Serial.print("B phase Power: ");
    Serial.print(voltage * current_B, 2); // Print with 2 decimal places
    Serial.println(" W");

    float current_L = getRMSCurrent(sensorL);
    float power_L = current_L * voltage;
    // Serial.print("L phase Current: ");
    // Serial.print(current_L, 3); // Print with 2 decimal places
    // Serial.println(" A");
    Serial.print("L phase Power: ");
    Serial.print(voltage * current_L, 2); // Print with 2 decimal places
    Serial.println(" W");

    int s1 = digitalRead(switch1);
    int s2 = digitalRead(switch2);
    int s3 = digitalRead(switch3);

    //// LOGIC ////
    if (s1)
        power_R -= power_L;
    if (s2)
        power_Y -= power_L;
    if (s3)
        power_B -= power_L;

    float diff1 = abs(power_R - power_Y);
    float diff2 = abs(power_Y - power_B);
    float diff3 = abs(power_R - power_B);

    // All powers are equal
    if (!diff1 & !diff2 & !diff3)
    {
        digitalWrite(switch1, 0);
        digitalWrite(switch2, 0);
        digitalWrite(switch3, 0);
    }
    Serial.println("---Power After---");
    // Difference between power of R phase and Y phase is highest
    if (diff1 > diff2 && diff1 > diff3)
    {
        if (power_R < power_Y)
        {
            // Switching
            digitalWrite(switch1, 1);
            digitalWrite(switch2, 0);
            digitalWrite(switch3, 0);

            // Power display
            Serial.print("R phase Power: ");
            Serial.print(voltage * (current_R + current_L), 2);
            Serial.println(" W");
            Serial.print("Y phase Power: ");
            Serial.print(voltage * current_Y, 2);
            Serial.println(" W");
            Serial.print("B phase Power: ");
            Serial.print(voltage * current_B, 2);
            Serial.println(" W");
        }
        else
        {
            // Switching
            digitalWrite(switch1, 0);
            digitalWrite(switch2, 1);
            digitalWrite(switch3, 0);

            // Power display
            Serial.print("R phase Power: ");
            Serial.print(voltage * current_R, 2);
            Serial.println(" W");
            Serial.print("Y phase Power: ");
            Serial.print(voltage * (current_Y + current_L), 2);
            Serial.println(" W");
            Serial.print("B phase Power: ");
            Serial.print(voltage * current_B, 2);
            Serial.println(" W");
        }
    }

    // Difference between power of Y phase and B phase is highest
    if (diff2 > diff1 && diff2 > diff3)
    {
        if (power_Y < power_B)
        {
            // Switching
            digitalWrite(switch1, 0);
            digitalWrite(switch2, 1);
            digitalWrite(switch3, 0);

            // Display Power
            Serial.print("R phase Power: ");
            Serial.print(voltage * current_R, 2);
            Serial.println(" W");
            Serial.print("Y phase Power: ");
            Serial.print(voltage * (current_Y + current_L), 2);
            Serial.println(" W");
            Serial.print("B phase Power: ");
            Serial.print(voltage * current_B, 2);
            Serial.println(" W");
        }
        else
        {
            // Switching
            digitalWrite(switch1, 0);
            digitalWrite(switch2, 0);
            digitalWrite(switch3, 1);

            // Power Display
            Serial.print("R phase Power: ");
            Serial.print(voltage * current_R, 2);
            Serial.println(" W");
            Serial.print("Y phase Power: ");
            Serial.print(voltage * current_Y, 2);
            Serial.println(" W");
            Serial.print("B phase Power: ");
            Serial.print(voltage * (current_B + current_L), 2);
            Serial.println(" W");
        }
    }

    // Difference between power of R phase and B phase is highest
    if (diff3 > diff1 && diff3 > diff1)
    {
        if (power_R < power_B)
        {
            // Switching
            digitalWrite(switch1, 1);
            digitalWrite(switch2, 0);
            digitalWrite(switch3, 0);

            // Power display
            Serial.print("R phase Power: ");
            Serial.print(voltage * (current_R + current_L), 2);
            Serial.println(" W");
            Serial.print("Y phase Power: ");
            Serial.print(voltage * current_Y, 2);
            Serial.println(" W");
            Serial.print("B phase Power: ");
            Serial.print(voltage * current_B, 2);
            Serial.println(" W");
        }
        else
        {
            // Switching
            digitalWrite(switch1, 0);
            digitalWrite(switch2, 0);
            digitalWrite(switch3, 1);

            // Power Display
            Serial.print("R phase Power: ");
            Serial.print(voltage * current_R, 2);
            Serial.println(" W");
            Serial.print("Y phase Power: ");
            Serial.print(voltage * current_Y, 2);
            Serial.println(" W");
            Serial.print("B phase Power: ");
            Serial.print(voltage * (current_B + current_L), 2);
            Serial.println(" W");
        }
    }
    Serial.println("-----------------------------------------");

    delay(8000); // Update every second
}