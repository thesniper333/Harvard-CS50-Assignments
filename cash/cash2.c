#include <cs50.h>
#include <stdio.h>

//int change_owed;
//int comparison(int change_owed);
int quarters = 0;
int dimes = 0;
int nickels = 0;
int pennies = 0;


int main(void)
{

    int change_owed = get_int("Enter the change owed");
    while (change_owed > 0)
        {
            if (change_owed >= 25)
            {
                change_owed -= 25;
                quarters += 1;
            }

        }

     //return quarters + dimes + nickels + pennies;
   printf("Total coin =  %i\n%i\n%i\n%i\n%i", quarters, dimes, nickels, pennies,change_owed );

}



