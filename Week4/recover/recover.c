#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int BLOCK_SIZE = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    int counter = 0;

    char filename[8];

    BYTE buffer[BLOCK_SIZE];

    FILE *img = NULL;

    FILE *card = fopen(argv[1], "r");


    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // image can't opened for reading.
    if (card == NULL)
    {
        return 1;
    }

    // Loop through to read card , once to read 512B.
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // If found JPEGs’ signatures open new img and set the name of img.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If found first signatures write it to img.
            if (counter == 0)
            {
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);
                counter++;
            }

            // If after the second time to found signatures.
            // Frist thing is close the img file, and keep writing to new file.
            else if (counter > 0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);
                counter++;
            }

        }
        // If already found frist signatures but didn't found next
        // signatures then keeping writing the block.
        else if (counter > 0)
        {
            fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }

    }

    // When all card has writen close img and card file.
    fclose(img);
    fclose(card);
}