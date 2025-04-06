#include <cs50.h>
#include <stdio.h>
int check();

int main(void)
{
    printf("%i\n", check());
    printf("It will be printed\n");
    return 1;
     printf("Will not be printed for main\n");


}
int check()
{
    return 1;
    printf("Will not be printed\n");
}

