#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        // string plaintext = get_string("plaintext:  ");

        int counter = 0; // counting number of digits in the key.

        int n = strlen(argv[1]);

        for (int i = 0; i < n; i++)
        {
            if (isdigit(argv[1][i]))
            {
                counter += 1;
            }
        }

        if (counter == n) // checking if all the characters in the key are digits.
        {
            string plaintext = get_string("plaintext:  "); // taking input of plaintext.

            int key = atoi(argv[1]); // converting the key(Command-Line arguement) into an integer.

            char ciphertext_array[n];

            printf("ciphertext: ");

            for (long j = 0, m = strlen(plaintext); j < m;
                 j++) // for int datatype it is not working for "world, say hello!" input.
            {
                if (isupper(plaintext[j]))
                {
                    if (((plaintext[j] - 65) + key >= 0) && ((plaintext[j] - 65) + key <= 25))
                    {
                        ciphertext_array[j] = (plaintext[j] - 65) + key + 65;
                    }
                    else if (((plaintext[j] - 65) + key) > 25)
                    {
                        ciphertext_array[j] = (((plaintext[j] - 65) + key) % 26) + 65;
                    }
                }
                else if (islower(plaintext[j]))
                {
                    if ((((plaintext[j] - 97) + key) >= 0) && (((plaintext[j] - 97) + key) <= 25))
                    {
                        ciphertext_array[j] = (plaintext[j] - 97) + key + 97;
                    }
                    else if (((plaintext[j] - 97) + key) > 25)
                    {
                        ciphertext_array[j] = (((plaintext[j] - 97) + key) % 26) + 97;
                    }
                }
                else
                {
                    ciphertext_array[j] = plaintext[j];
                }

                printf("%c", ciphertext_array[j]);
            }
            printf("\n");
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
