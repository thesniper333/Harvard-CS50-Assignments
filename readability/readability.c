#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int letters_counter(string text_letters);
int words_counter(string text_words);
int sentences_counter(string text_sentences);

int main(void)
{
    string text = get_string("Text: ");
    int number_of_letters = letters_counter(text);     // Actual number of letters in text
    int number_of_words = words_counter(text);         // Actual number of words in text
    int number_of_sentences = sentences_counter(text); // Actual number of sentences in text

    float L = ((float) number_of_letters / (float) number_of_words) *
              100; // Average number of letters in 100 words
    float S = ((float) number_of_sentences / (float) number_of_words) *
              100; // Average number of sentences in 100 words

    int index = round(0.0588 * L - 0.296 * S - 15.8); // Coleman-Liau index

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int letters_counter(string text_letters)
{
    int letters = 0;

    for (int i = 0, n = strlen(text_letters); i < n; i++)
    {

        if (((text_letters[i] >= 'a') && (text_letters[i] <= 'z')) ||
            ((text_letters[i] >= 'A') && (text_letters[i] <= 'Z')))
        {
            letters += 1;
        }
    }
    return letters;
}

int words_counter(string text_words)
{
    int words = 0;

    for (int i = 0, n = strlen(text_words); i < n; i++)
    {
        if (text_words[i] == ' ')
        {
            words += 1;
        }
    }
    return words + 1;
}

int sentences_counter(string text_sentences)
{
    int sentences = 0;

    for (int i = 0, n = strlen(text_sentences); i < n; i++)
    {
        if ((text_sentences[i] == '?') || (text_sentences[i] == '.') || (text_sentences[i] == '!'))
        {
            sentences += 1;
        }
    }
    return sentences;
}
