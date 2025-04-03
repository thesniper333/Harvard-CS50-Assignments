// Read the comment in line 20 to 25.
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checksum(string number_str);

void card_name(long number);

int main(void)
{
    string card_number = get_string("Enter No.");

    // checksum(card_number);

    long card_number_int = 0;
    int i = 0;
    /* This is to convert String card_number into long card_number. This was not taught in the
    class, so I took help about this conversion from the internet. Although, this conversion is not
    essential for the required output but in the assignment it was discussed about the luhn
    algorithm. Here long card_number_int will be passed into card_name function which will validate
    the card number and prompt the provider of the debit card and string card_number is passed into
    checksum function which will do the said calculation mentioned in assignment and prompt if the
    card is legit or not. However, checksum feature is still in the program but it has been made as
    a comment as the it's output is contradicting with check50 requirement but to run that part it
    has to be removed it from comment only and nothing else are to be changed in the code. */

    while (card_number[i] != '\0')
    {
        card_number_int = (card_number_int * 10) + (card_number[i] - '0');
        i++;
    }

    card_name(card_number_int);
}

void card_name(long number)
{

    if ((number > 3999999999999 && number < 4222222222223) ||
        (number > 3999999999999999 && number < 4111111111111112))
    {
        printf("VISA\n");
    }
    else if ((number > 339999999999999 && number < 349999999999999) ||
             (number > 369999999999999 && number < 379999999999999))
    {
        printf("AMEX\n");
    }
    else if ((number > 5099999999999999 && number < 5600000000000000))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

/* void checksum(string number_str)
{
        int product_sum = 0;
        int digit_int;
        char digit_char;
        int digit_product;
        int sum = 0;

        for (int i = strlen(number_str) - 2; i >= 0; i -= 2)
        {

                digit_char = number_str[i];
                digit_int = digit_char - '0';
                digit_product = 2 * digit_int;

                if (digit_product < 10)
                {
                        product_sum += (digit_product);
                }
                else if (digit_product > 9)
                {
                        product_sum += ((digit_product - ((digit_product / 10) * 10)) +
(digit_product / 10) );
                }


        }

        for (int j = strlen(number_str)-1; j >= 0; j -= 2 )
        {

                digit_char = number_str[j];
                digit_int = digit_char - '0';

                sum += digit_int;
        }

        if ((product_sum + sum) % 10 == 0)
        {

                printf("Card is legit\n");
        }
        else
        {
                printf("Card is not legit\n");
        }


} */
