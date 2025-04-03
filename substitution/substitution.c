#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        int counter = 0;
        for (int i = 0; i < 26; i++)
        {
            if (isalpha(argv[1][i]))
            {
                counter += 1; // counting number of alphabetical characters in the key.
            }
        }
        if (counter == 26) // checking if all the characters in the key is alphabet.
        {
            char key_case_insensitive[26];

            for (int l = 0; l < 26; l++)
            {
                key_case_insensitive[l] = toupper(argv[1][l]);
            }
            int letter_frequency;
            for (int j = 65; j <= 90;
                 j++) // checking frequency of alphabet in the key which should be 1 strictly.
            {
                letter_frequency = 0;
                for (int k = 0; k < 26; k++)
                {
                    char ascii_char = j;

                    if (ascii_char == key_case_insensitive[k])
                    {
                        letter_frequency += 1;
                    }
                }
                if (letter_frequency != 1)

                {
                    printf("Key should not have repetitive alphabetical characters.\n");
                    return 1;
                }
            }

            string plaintext = get_string("plaintext:"); // input of plaintext.
            printf("ciphertext:");                       // output of ciphertext(cipher_text_array).

            for (int m = 0, n = strlen(plaintext); m < n;
                 m++) // encrypting by substituting(replacing) each character as instructed.
            {
                char cipher_text_array[n];
                if (isupper(plaintext[m]))
                {
                    cipher_text_array[m] = key_case_insensitive[plaintext[m] - 65];
                }
                else if (islower(plaintext[m]))
                {
                    cipher_text_array[m] = tolower(key_case_insensitive[plaintext[m] - 97]);
                }
                else
                {
                    cipher_text_array[m] = plaintext[m];
                }
                printf("%c", cipher_text_array[m]);
            }
            printf("\n");
        }
        else
        {
            printf("Key should have 26 distinctive alphabetical characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}
