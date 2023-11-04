# TODO
import re


def main():
    s = input("Text: ")
    numLetters = count_Letters(s)
    numWords = count_words(s)
    numSentences = count_sentences(s)

    L = float(numLetters / numWords) * 100.0
    S = float(numSentences / numWords) * 100.0

    res = 0.0588 * L - 0.296 * S - 15.8
    idx = round(res)

    if res >= 16:
        print("Grade 16+")
    elif res < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {idx}")


def count_Letters(text):
    pattern = r"[',.!? ]"
    str = re.sub(pattern, "", text)
    return len(str)


def count_words(text):
    words = text.split()
    return len(words)


def count_sentences(text):
    sentences = re.split(r"[.?!]", text)
    return len(sentences) - 1


main()
