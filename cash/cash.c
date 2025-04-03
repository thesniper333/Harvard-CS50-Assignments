#include <cs50.h>
#include <stdio.h>

int change;
int comparison(int change_owed);
int quarters = 0;
int dimes = 0;
int nickels = 0;
int pennies = 0;

int main(void)
{

    do
    {
        change = get_int("Enter the change owed");
    }
    while (change < 0);
    printf("Total coin =  %i\n", comparison(change));
}

int comparison(int change_owed)
{
    do
    {

        if (change_owed >= 25)
        {
            change_owed -= 25;
            quarters += 1;
        }
        else if (change_owed >= 10)
        {
            change_owed -= 10;
            dimes += 1;
        }
        else if (change_owed >= 5)
        {
            change_owed -= 5;
            nickels += 1;
        }
        else if (change_owed >= 1)
        {
            change_owed -= 1;
            pennies += 1;
        }
    }
    while (change_owed > 0);
    return quarters + dimes + nickels + pennies;
}
