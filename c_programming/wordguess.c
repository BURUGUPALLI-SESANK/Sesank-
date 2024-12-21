#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORD_LENGTH 100
#define MAX_ATTEMPTS 10
#define WORDS_COUNT 10

// Function prototypes
void displayWelcomeMessage();
void displayGameRules();
void pickRandomWord(char *word);
void initializeGuessedWord(char *guessedWord, int length);
void displayGameState(const char *guessedWord, int attemptsLeft, const char *wrongGuesses);
int processGuess(char guess, const char *word, char *guessedWord, char *wrongGuesses);
int isWordGuessed(const char *word, const char *guessedWord);

int main() {
    char word[MAX_WORD_LENGTH];
    char guessedWord[MAX_WORD_LENGTH];
    char wrongGuesses[MAX_ATTEMPTS + 1] = "";
    char guess;
    int attemptsLeft = MAX_ATTEMPTS;
    int wordGuessed = 0;

    // Seed random number generator
    srand(time(NULL));

    // Game start
    displayWelcomeMessage();
    displayGameRules();

    pickRandomWord(word);
    initializeGuessedWord(guessedWord, strlen(word));

    while (attemptsLeft > 0 && !wordGuessed) {
        displayGameState(guessedWord, attemptsLeft, wrongGuesses);
        printf("\nEnter your guess: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (!isalpha(guess)) {
            printf("Invalid input. Please enter a letter.\n");
            continue;
        }

        int result = processGuess(guess, word, guessedWord, wrongGuesses);

        if (result == 0) {
            printf("\'%c\' is incorrect!\n", guess);
            attemptsLeft--;
        } else if (result == -1) {
            printf("You already guessed \"%c\". Try again.\n", guess);
        }

        wordGuessed = isWordGuessed(word, guessedWord);
    }

    if (wordGuessed) {
        printf("\nCongratulations! You guessed the word: %s\n", word);
    } else {
        printf("\nGame over! The correct word was: %s\n", word);
    }

    return 0;
}

void displayWelcomeMessage() {
    printf("***********************************\n");
    printf("*    Welcome to Word Guess Game!  *\n");
    printf("***********************************\n\n");
}

void displayGameRules() {
    printf("Game Rules:\n");
    printf("1. A word will be chosen randomly.\n");
    printf("2. You need to guess the word letter by letter.\n");
    printf("3. You have %d wrong attempts before the game ends.\n", MAX_ATTEMPTS);
    printf("4. Good luck and have fun!\n\n");
}

void pickRandomWord(char *word) {
    const char *words[WORDS_COUNT] = {
        "apple",
        "banana",
        "cherry",
        "dragon",
        "elephant",
        "falcon",
        "grape",
        "honey",
        "igloo",
        "jungle"
    };
    int index = rand() % WORDS_COUNT;
    strcpy(word, words[index]);
}

void initializeGuessedWord(char *guessedWord, int length) {
    for (int i = 0; i < length; i++) {
        guessedWord[i] = '_';
    }
    guessedWord[length] = '\0';
}

void displayGameState(const char *guessedWord, int attemptsLeft, const char *wrongGuesses) {
    printf("\nCurrent word: %s\n", guessedWord);
    printf("Attempts left: %d\n", attemptsLeft);
    if (strlen(wrongGuesses) > 0) {
        printf("Wrong guesses: %s\n", wrongGuesses);
    }
}

int processGuess(char guess, const char *word, char *guessedWord, char *wrongGuesses) {
    int found = 0;
    int alreadyGuessed = strchr(guessedWord, guess) || strchr(wrongGuesses, guess);

    if (alreadyGuessed) {
        return -1;
    }

    for (int i = 0; i < strlen(word); i++) {
        if (word[i] == guess) {
            guessedWord[i] = guess;
            found = 1;
        }
    }

    if (!found) {
        size_t len = strlen(wrongGuesses);
        wrongGuesses[len] = guess;
        wrongGuesses[len + 1] = '\0';
    }

    return found;
}

int isWordGuessed(const char *word, const char *guessedWord) {
    return strcmp(word, guessedWord) == 0;
}
