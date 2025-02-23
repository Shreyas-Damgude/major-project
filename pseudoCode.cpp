// Pseudo Code
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    float power_R, power_Y, power_B, power_L;

    bool switch1, switch2, switch3;

    /*
    if (all powers are equal)
    {
        keep the switches as it is
    }
    */

    // If any of the switch is on deduct the load power from that phase power
    if (switch1)
        power_R -= power_L;
    if (switch2)
        power_Y -= power_L;
    if (switch3)
        power_B -= power_L;

    // Calculate differences
    float diff1 = abs(power_R - power_Y);
    float diff2 = abs(power_Y - power_B);
    float diff3 = abs(power_R - power_B);

    // If all powers are equal
    if (!diff1 & !diff2 & !diff3)
    {
        // turn off all the switches
    }

    if (diff1 > diff2 && diff1 > diff3)
    {
        if (power_R < power_Y)
        {
            // turn on switch 1
        }
        else
        {
            // turn on switch 2
        }
    }

    if (diff2 > diff1 && diff2 > diff3)
    {
        if (power_R < power_B)
        {
            // turn on switch 2
        }
        else
        {
            // turn on switch 3
        }
    }

    if (diff3 > diff1 && diff3 > diff1)
    {
        if (power_R < power_Y)
        {
            // turn on switch 1
        }
        else
        {
            // turn on switch 3
        }
    }

    return 0;
}
