// Define the analog pin connected to ZMPT101B sensor
#define ZMPT101B_PIN A0

// Calibration factor (adjust based on actual readings)
#define CALIBRATION_FACTOR 100.0

// Number of samples for averaging
#define NUM_SAMPLES 500

int count = 0;
float setValue = 0;
void setup()
{
    Serial.begin(9600); // Start serial communication
    pinMode(ZMPT101B_PIN, INPUT);
}

// Function to measure AC voltage
float get_AC_Voltage()
{
    float sum = 0;

    // Collect multiple samples
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        int sensorValue = analogRead(ZMPT101B_PIN);
        float voltage = sensorValue * (5.0 / 1023.0); // Convert ADC to voltage
        sum += voltage * voltage;                     // Square it for RMS calculation
    }

    float mean = sum / NUM_SAMPLES;         // Mean of squared values
    float rmsVoltage = sqrt(mean);          // Root Mean Square (RMS) value
    return rmsVoltage * CALIBRATION_FACTOR; // Adjust with calibration factor
}

void loop()
{
    float voltage = get_AC_Voltage();
    Serial.print("AC Voltage: ");
    Serial.print(voltage, 2); // Print with 2 decimal places
    Serial.println(" V");
    // if (count < 2) {
    //   float voltage =  get_AC_Voltage();
    //   Serial.print("AC Voltage: ");
    //   Serial.print(voltage, 2); // Print with 2 decimal places
    //   Serial.println(" V");
    //   if (count == 1) {
    //     setValue = voltage;
    //     Serial.print("AC Voltage: ");
    //     Serial.print(voltage, 2); // Print with 2 decimal places
    //     Serial.println(" V");
    //   }
    //   count++;
    // } else {
    //   Serial.print("AC Voltage: ");
    //   Serial.print(setValue, 2); // Print with 2 decimal places
    //   Serial.println(" V");
    // }
    delay(1000); // Update every second
}