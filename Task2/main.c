#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAXIMUM_GUESSES 6  // Maximum number of incorrect guesses allowed
#define WORD_COUNT 10   // number of words in the word array. we couldve also done const char* words[10] but since the number of
//words is used also elsewhere then we can define it as a constant

// array of words to choose from
// we put "const" for the location of the pointer to not be changeable
const char* words[WORD_COUNT] = { "jazz", "sleeveless", "axiom", "beekeeper", "rhythm", "singleton", "continuous", "telecommunication", "outlaw", "pershendetje"};

//funciton that draws the hangaman figure
void drawHangman(int incorrectGuesses){
    if (incorrectGuesses == 0)
        printf("      _____\n"
               "     |     |\n"
               "     |     \n"
               "     |\n"
               "     |\n"
               "     |\n"
               "_____|________\n");
    else if (incorrectGuesses == 1)
        printf("      _____\n"
               "     |     |\n"
               "     |     O\n"
               "     |\n"
               "     |\n"
               "     |\n"
               "_____|________\n\n");
    else if (incorrectGuesses == 2)
        printf("      _____\n"
               "     |     |\n"
               "     |     O\n"
               "     |     |\n"
               "     |\n"
               "     |\n"
               "_____|________\n");
    else if (incorrectGuesses == 3)
        printf("      _____\n"
               "     |     |\n"
               "     |     O\n"
               "     |    /|\n"
               "     |\n"
               "     |\n"
               "_____|________\n");
    else if (incorrectGuesses == 4)
        printf("      _____\n"
               "     |     |\n"
               "     |     O\n"
               "     |    /|\\\n"
               "     |\n"
               "     |\n"
               "_____|________\n");
    else if (incorrectGuesses == 5)
        printf("      _____\n"
               "     |     |\n"
               "     |     O\n"
               "     |    /|\\\n"
               "     |    /\n"
               "     |\n"
               "_____|________\n");
    else if (incorrectGuesses == 6)
        printf("      _____\n"
               "     |     |\n"
               "     |     O\n"
               "     |    /|\\\n"
               "     |    / \\\n"
               "     |\n"
               "_____|________\n");
}
// function that returns true if the letter is in the word and updates the blanks array with the new letter
bool check_letter(char letter, char word[], char blanks_of_word[]){
    bool found = false;
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] == letter) //if one of the letters of the word is == to the inputted letter then change the
                                //i-th blank position to the letter itself. reveal the letter
        {
            blanks_of_word[i] = letter;
            found = true;
        }
    }
    return found;
}


void playGame(){

// choose a random word from the array we provided at the beginning
    int wordIndex = rand() % WORD_COUNT;
    char* word = (char*) words[wordIndex];

    // the number of incorrect guesses and the word progress to all underscores
    int incorrectGuesses = 0;
    char progress[strlen(word) + 1];
    for (int i = 0; i < strlen(word); i++)
        progress[i] = '_';
    progress[strlen(word)] = '\0';

    // the array of incorrect letters
    char incorrectLetters[MAXIMUM_GUESSES + 1];
    for (int i = 0; i < MAXIMUM_GUESSES; i++)
        incorrectLetters[i] = ' ';
    incorrectLetters[0] = '\0';

    // while loop that loops until the player has won/lost
    while (incorrectGuesses < MAXIMUM_GUESSES && strchr(progress, '_') != NULL) {
        // print current progress and the hangman
        printf("Word: %s\n", progress);
        drawHangman(incorrectGuesses);

        // player's guess
        char guess[3];
        printf("Enter a letter: ");
        scanf("%s", guess);
        printf("\n############################################################\n############################################################\n\n");


        // if statement that checks if the inputted guess is a lowercase letter
        if (guess[0] < 'a' || guess[0] > 'z') {
            printf("Please enter a lowercase letter.\n");
            continue;
        }

        // check if the guess is already been used before. if not, check of it is correct
        if (strchr(incorrectLetters, guess[0]) != NULL || strchr(progress, guess[0]) != NULL) {
            printf("You have already tried that letter. Try again.\n");
        } else {
            if (!check_letter(guess[0], word, progress))  // if its an incorrect guess then add +1 to
                                                                                //number of incorrect guesses
            {
                incorrectGuesses++;

                // add the incorrect letter to the list of incorrect letters
                int len = strlen(incorrectLetters);
                incorrectLetters[len] = guess[0];
                incorrectLetters[len + 1] = ' ';  // add a space after the letter
                incorrectLetters[len + 2] = '\0';
            }
        }
    }

    // print the final result
    if (incorrectGuesses == MAXIMUM_GUESSES){
        printf("      _____\n"
               "     |     |\n"
               "     |     O\n"
               "     |    /|\\\n"
               "     |    / \\\n"
               "     |\n"
               "_____|________\n");
        printf("You lost! The word was: %s\n", word);}
    else
        printf("You won! The word was: %s\n", word);
}

int main(){
    srand(time(0));  // random number generator i looked up on the internet

    printf("   * * * * * * * * * * * *\n");
    printf("   * Welcome to Hangman! *\n");
    printf("   * * * * * * * * * * * *\n");

    playGame();
    return 0;
}