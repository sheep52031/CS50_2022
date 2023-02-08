#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char key_26(string key);
char encrypt(char p, string key);
bool repeat_letter(string key);

int main(int argc, string argv[])
{
    int maps = 0;
    string key = argv[1];
    char ciphertext[100];

    if (argc == 2)
    {
        if (key_26(key) == 'a')
        {
            string plaintext = get_string("plaintext: ");

            for (int i = 0, n = strlen(plaintext); i < (n + 1); i++)
            {

                if (i == (n + 1))
                {
                    ciphertext[i] = '\0';
                }
                else
                {
                    ciphertext[i] = encrypt(plaintext[i], key);
                }
            }

            printf("ciphertext:%s\n", ciphertext);
        }

        // Other conditions that about wrong key of input.
        switch (key_26(key))
        {

            case 'b':
                printf("Key must contain repeated characters.\n");
                return 1;

            case 'c':
                printf("Key must only contain alphabetic characters.\n");
                return 1;

            case 'd':
                printf("Key must contain 26 characters.\n");
                return 1;

            case 'e':
                printf("Key must contain 26 characters.\n");
                return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    return 0;
}


// This function can encrypt and return each ciphert letters.
char encrypt(char p, string key)
{
    int n = 0;
    char a = ' ';

    if (islower(p))
    {
        // Calculate p is the first few letters.
        n = (int) p - 97;

        // plaintext of letter is lower so convert it.
        a = tolower(key[n]);
    }
    else if (isupper(p))
    {
        // Calculate p is the first few letters.
        n = (int) p - 65;

        // plaintext of letter is upper so convert it.
        a = toupper(key[n]);
    }
    else
    {
        // number or symbols don't encrypt.
        a = p;
    }
    return a;
}

// This function can check user input "Key" every conditions.
char key_26(string key)
{
    int j = 0;
    bool checkrepeat;

    // Check keys has 26 letters
    if (strlen(key) == 26)
    {
        // If keys letters all are Engilsh letters then j = 26
        for (int i = 0; i < 26; i++)
        {
            if (isupper(key[i]) || islower(key[i]))
            {
                j++;
            }
        }

        // If j = 26 then check all 26 letters has repeat letters.
        if (j == 26)
        {
            // Call function check key is repeat?
            checkrepeat = repeat_letter(key);

            if (checkrepeat == false)
            {
                // a -> keys hasn't any repeat and all letters are Engilsh letters.
                return 'a';
            }
            else
            {
                // b -> keys has repeat letters.
                return 'b';
            }
        }
        else
        {
            // c -> Users input 26 letters but not all Engilsh letters.
            return 'c';
        }
    }
    else if (strlen(key) > 26)
    {
        // d -> key has over much than 26 letters.
        return 'd';
    }

    else
    {
        // e -> keys hasn't input 26 letters.
        return 'e';
    }
}

// Check the key has any letter repeat?
bool repeat_letter(string key)
{
    int n = strlen(key);
    bool repeat;
    char check = ' ';

    for (int i = 0; i < n; i++)
    {
        check = key[i];

        // Through 'check' of letter loop through each key letters has repeat?
        for (int j = i + 1 ; j < n ; j++)
        {
            if (check == key[j])
            {
                repeat = true;
                return repeat;
            }
            repeat = false;
        }
    }
    return repeat;
}