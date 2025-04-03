from cs50 import get_string


def main():
    text = get_string("Text: ")
    number_of_letters = letters_counter(text)
    number_of_words = words_counter(text)
    number_of_sentences = sentences_counter(text)

    L = (number_of_letters / number_of_words) * 100

    S = (number_of_sentences / number_of_words) * 100

    index = round(0.0588 * L - 0.296 * S - 15.8)

    if (index < 1):
        print("Before Grade 1")

    elif (index >= 16):
        print("Grade 16+")

    else:
        print(f"Grade {index}")


def letters_counter(text_letters):

    letters = 0
    n = len(text_letters)

    for i in range(n):
        if (((text_letters[i] >= 'a') and (text_letters[i] <= 'z')) or
                ((text_letters[i] >= 'A') and (text_letters[i] <= 'Z'))):
            letters += 1

    return letters


def words_counter(text_words):
    words = 0
    n = len(text_words)
    for i in range(n):
        if (text_words[i] == ' '):
            words += 1

    return words + 1


def sentences_counter(text_sentences):
    sentences = 0
    n = len(text_sentences)
    for i in range(n):
        if ((text_sentences[i] == '?') or (text_sentences[i] == '.') or (text_sentences[i] == '!')):
            sentences += 1

    return sentences


main()
