#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
            string key_case_insensitive = "AACB";
            int letter_frequency;
            for (int j = 65; j < 69; j++)
            {
                letter_frequency = 0;
                printf("1st %i\n", letter_frequency);
                for (int k = 0; k < 4; k++)
                {

                    char ascii_char = j;
                    
                    if (ascii_char == key_case_insensitive[k])
                    {
                        letter_frequency += 1;

                    }
                }

            }
            printf("%i\n",letter_frequency);




}
