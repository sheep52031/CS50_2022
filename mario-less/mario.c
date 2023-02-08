#include <cs50.h>
#include <stdio.h>

void mkLpyr(int h);
bool checkValue(int h);

int main(void)
{

    // prompting user typing height of pyramid,if wrong then keep ask
    int h;

    do
    {
        printf("Please typing 1~8 for your pyramid height!\n");
        h = get_int("Height:");
    }
    while (checkValue(h));

    mkLpyr(h);
}


// make a left aligned pyramid
// input is height
void mkLpyr(int h)
{
    // This loop determine the column.
    for (int i = 0; i < h ; i++)
    {
        // This loop determine the row
        for (int j = 0; j < h; j++)
        {
            if (j >= (h - (i + 1)))
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// check user typing input is 1~8
bool checkValue(int h)
{
    if ((h >= 1) && (h <= 8))
    {
        return false;
    }
    else
    {
        return true;
    }
}
