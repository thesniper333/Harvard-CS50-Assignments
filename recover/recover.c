#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    FILE *card_out = NULL;

    uint8_t buffer[512];

    int counter = 0;

    char filename[8] = {0};

    while (fread(buffer, 1, sizeof(uint8_t) * 512, card) == 512)
    {

        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF &&
            (buffer[3] & 0xF0) == 0xE0)
        {

            if (card_out != NULL)
            {
                fclose(card_out);
            }
            sprintf(filename, "%03d.jpg", counter++);

            card_out = fopen(filename, "w");
        }

        if (card_out != NULL)
        {
            fwrite(buffer, 1, sizeof(uint8_t) * 512, card_out);
        }
    }

    if (card_out != NULL)
    {
        fclose(card_out);
    }

    fclose(card);

    return 0;
}
