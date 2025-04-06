#include <cs50.h>
#include <stdio.h>
#include <string.h>



int main(void)
{
        string s = get_string("Enter");
        for (int i = 0, n = strlen(s); i < n; i++)
        {

                if (s[i] >= 'a' && s[i] <= 'z')
                {
                        int ascii_s = s[i];
                        int ascii_upcase_s = ascii_s - 32;
                        char char_upcase_s = ascii_upcase_s;


                        printf("%c", char_upcase_s);
                }
                else
                {
                        printf("%c", s[i]);
                }
        }
        printf("\n");

}



