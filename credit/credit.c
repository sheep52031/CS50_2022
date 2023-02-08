#include <cs50.h>
#include <math.h>
#include <stdio.h>


bool checkCCNum(double c);
int  ccVaild(double c, int digits);

int main(void)
{
    double c;

    // Check
    do
    {
        c = get_long("Number: ");
    }
    while (checkCCNum(c));

}


// If card number is not anycard beginning then repeat ask.
// Distinguish the credit card number is which card
// Accept return value(remainder) of function ccVaild.
bool checkCCNum(double c)
{

    // AMEX card beginning numbers is 34 or 37 and 15 digits
    int a = c / pow(10, 13);

    // MASTER card beginning numbers is 51 52 53 54 55 and 16 digits
    int m = c / pow(10, 14);

    // VISA card beginning numbers is 4 ,13 digits
    int v1 = c / pow(10, 12);

    // VISA card beginning numbers is 4 ,16 digits
    int v2 = c / pow(10, 15);




    // If return value of function ccVaild can be divisible by ten
    // then the credit card number is Valid , else is Invalid.

    if (a == 34 || a == 37)
    {
        int remainder = ccVaild(c, 15);

        if (remainder == 0)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }

        return false;
    }
    else if (m == 51 || m == 52 || m == 53 || m == 54 || m == 55)
    {

        int remainder = ccVaild(c, 16);

        if (remainder == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }

        return false;
    }
    else if (v1 == 4)
    {
        int remainder = ccVaild(c, 13);

        if (remainder == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }

        return false;
    }
    else if (v2 == 4)
    {
        int remainder = ccVaild(c, 16);

        if (remainder == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }

        return false;
    }
    else
    {
        printf("INVALID\n");
        return false;
    }

}


// Input value which is credit card numbers and the card digits.
// Used to check the card is match the Luhn’s Algorithm.
int ccVaild(double c, int digits)
{
    int a[digits];
    int etotal = 0;
    int ototal = 0;
    int total = 0;
    int evenpdt = 0;
    int tens = 0;
    int ones = 0;
    int remainder = 0;


    // Let each number of digit input to Array a[]
    for (int i = (digits - 1); i > -1 ; i--)
    {
        a[i] = (c) / (pow(10, i));
        c = (c) - (a[i] * pow(10, i));
    }

    // If it's digits of even and number of digit less than 9 , multiply 2 and add.
    // If that numbers greater than 9 , separate tens and units digit then add both.
    for (int i = 0; i < digits ; i++)
    {
        if ((i % 2) != 0)
        {
            evenpdt = 2 * a[i];

            if (evenpdt > 9)
            {

                tens = evenpdt / 10;

                ones = evenpdt % 10;

                evenpdt = tens + ones;
            }

            etotal = etotal + evenpdt;
        }
    }

    // If it's digits of odd add them.
    for (int i = 0 ; i < digits; i++)
    {
        if ((i % 2) == 0)
        {
            ototal = ototal + (a[i]);
        }
    }

    // Return remainder that division by 10 .

    total = etotal + ototal;

    remainder = total % 10;

    return remainder;

}
