#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int n;
    do
    {
        n = get_int("Enter the Height of the Pyramid");
    }
    while (n <= 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - (i + 1); j++)

        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
