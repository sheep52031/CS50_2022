#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int convert_index(int l, int w, int s);

int main(void)
{
    int l = 0;
    int w = 0;
    int s = 0;
    int index;
    int grade;
    string text = get_string("Text:");

    l = count_letters(text);
    w = count_words(text);
    s = count_sentences(text);

    printf("%i letters\n", l);
    printf("%i words\n", w);
    printf("%i sentences\n", s);

    grade = convert_index(l, w, s);

    // Show the grade.
    if (grade > 15)
    {
        printf("Grade 16+\n");
    }

    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Count how many letters and calculates case-insensitively.
int count_letters(string text)
{
    int i = 0;
    int n = 0;

    while (text[i] != '\0')
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            n++;
        }

        i++;
    }
    return n;
}

// Count how many words.
int count_words(string text)
{

    int i = 0;
    int n = 1;

    while (text[i] != '\0')
    {
        if (isspace(text[i]))
        {
            n++;
        }
        i++;
    }

    return n;
}


// Count how many sentences that exclude "Mr." and "Mrs." problems.
int count_sentences(string text)
{
    int i = 0;
    int n = 0;


    while (text[i] != '\0')
    {
        if (text[i] == '!' || text[i] == '?')
        {
            n += 1;
        }
        else if (text[i] == '.')
        {
            if ((text[i - 2] != 'M') && (text[i - 3] != 'M'))
            {
                n += 1;
            }
        }
        i++;
    }
    return n;
}


// Calculate index and rounded to the nearest integer
int convert_index(int l, int w, int s)
{
    float index;
    int newindex;
    char text[5];
    float L = 0;
    float S = 0;

    L = (float) l / (float) w * 100;
    S = (float)s / (float) w * 100;

    index = (0.0588 * L) - (0.296 * S) - 15.8;

    newindex = round(index);

    return newindex;
}