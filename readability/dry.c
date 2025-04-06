#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    char a = get_char("Enter");
    if ((a >= 'A') && (a <= 'Z'))
    {
        printf("ok");
    }
}
