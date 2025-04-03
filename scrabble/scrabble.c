#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int scrabble(string word);

int main(void)
{
    string player_1 = get_string("Player 1: ");
    string player_2 = get_string("Player 2: ");
    int player_1_point = scrabble(player_1);
    int player_2_point = scrabble(player_2);

    if (player_1_point > player_2_point)
    {
        printf("Player 1 wins!\n");
    }
    else if (player_2_point > player_1_point)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int scrabble(string word)
{
    int point = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char word_array[n];
        word_array[i] = toupper(word[i]);
        if ((word_array[i] == 'A') || (word_array[i] == 'E') || (word_array[i] == 'I') ||
            (word_array[i] == 'L') || (word_array[i] == 'N') || (word_array[i] == 'O') ||
            (word_array[i] == 'R') || (word_array[i] == 'S') || (word_array[i] == 'T') ||
            (word_array[i] == 'U'))
        {
            point += 1;
        }
        else if ((word_array[i] == 'D') || (word_array[i] == 'G'))
        {
            point += 2;
        }
        else if ((word_array[i] == 'B') || (word_array[i] == 'C') || (word_array[i] == 'M') ||
                 (word_array[i] == 'P'))
        {
            point += 3;
        }
        else if ((word_array[i] == 'H') || (word_array[i] == 'V') || (word_array[i] == 'W') ||
                 (word_array[i] == 'Y'))
        {
            point += 4;
        }
        else if (word_array[i] == 'K')
        {
            point += 5;
        }
        else if ((word_array[i] == 'J') || (word_array[i] == 'X'))
        {
            point += 8;
        }
        else if ((word_array[i] == 'Q') || (word_array[i] == 'Z'))
        {
            point += 10;
        }
    }
    return point;
}
