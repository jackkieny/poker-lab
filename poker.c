/*
 * STUDENT: Jack Kieny
 */

/*
 * PokerLab (c) 2018-21 Christopher A. Bohn
 */

/******************************************************************************
 * This simple program should populate a standard 52-card deck and then
 * randomly select five cards from the deck.  It will then print the
 * poker hand and report the best way it can be characterized (flush, full
 * house, one pair, high card, etc.)
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"


card deck[52];          // a "deck" of 52 cards


/* Places the 52 standard cards in deck[]. */
void populate_deck() {
    /* ADD CODE HERE TO PLACE THE 52 STANDARD CARDS IN DECK[] */

    for(int j=0; j<4; j++){
        for(int i=1; i<14; i++){
            int flag;
            switch (j){
                case 0:
                    flag = 0;
                    break;

                case 1:
                    flag = 13;
                    break;

                case 2:
                    flag = 26;
                    break;

                case 3:
                    flag = 39;
                    break;

                default:
                    printf("Something has gone wrong while creating the deck.");
                    exit(0);
            }
            create_card(i, j, &deck[i+flag]);
        }
    }
}


/* Sorts an array of cards in-place from least value to greatest value. */
card *sort(card *subdeck, int size) {
    card temp;
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (subdeck[i].value > subdeck[j].value) {
                temp = subdeck[i];
                subdeck[i] = subdeck[j];
                subdeck[j] = temp;
            }
    return subdeck;
}


/* Randomly selects "size_of_hand" cards and returns them.  The empty_hand argument must
 * have space for at least "size_of_hand" cards. */
card *get_hand(card *empty_hand, int size_of_hand) {
    int selection;
    for (int i = 0; i < size_of_hand; i++) {
        selection = rand() % 52;
        empty_hand[i] = deck[selection];    // if this were more robust, we'd check for duplicates
    }
    return sort(empty_hand, size_of_hand);
}

/* Sorts and prints the current hand */
void print_currentHand(card *current_hand, int size_of_hand){
     sort(get_hand(current_hand, size_of_hand), size_of_hand);
        for (int i=0; i<5; i++){
            char *s = malloc(21);
            printf("%s\n", display_card(&current_hand[i], s));
        }
}


/* Returns 1 if two of the cards in "hand" have the same value; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value. */
int is_pair(card *hand, int size_of_hand) {
    /* STUDY THIS CODE.  WHY DOES IT PRODUCE THE INTENDED RESULT? */
    int pair = 0;
    for (int i = 0; i < size_of_hand - 1; i++)
        pair = pair || (hand[i].value == hand[i + 1].value);    // because hand is sorted, a pair must be two adjacent cards
    return pair;
}

/* Returns 1 if two of the cards in "hand" are a pair and two other are also a pair; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value. */
int is_two_pair(card *hand, int size_of_hand) {
    int number_of_pairs = 0;
    card *partial_hand;
    int i = 0;
    while (i < size_of_hand) {      /* RECALL THAT ARRAYS ARE POINTERS */
        partial_hand = hand + i;    /* THIS IS CHANGING THE ADDRESS IN THE "PARTIAL_HAND" POINTER TO ANOTHER PART OF THE ARRAY */
        if (is_pair(partial_hand, 2)) {
            number_of_pairs++;
            i += 2;
        } else {
            i++;
        }
    }
    return (number_of_pairs == 2);
}


/* Returns 1 if three of the cards in "hand" have the same value; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value. */
int is_three_of_kind(card *hand, int size_of_hand) {
    /* WRITE THIS FUNCTION */

    int threeKind = 0;
    for(int i=0; i<size_of_hand; i++){
       threeKind = threeKind || (hand[i].value == hand[i+1].value && hand[i+1].value == hand[i+2].value);
    }

    return threeKind;
}


/* Returns 1 if the cards have contiguous values; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value. */
int is_straight(card *hand, int size_of_hand) {
    /* STUDY THIS CODE.  WHY DOES IT PRODUCE THE INTENDED RESULT? */
    int not_straight = 0;
    for (int i = 0; i < size_of_hand - 1; i++)
        not_straight = not_straight + abs(hand[i + 1].value - hand[i].value - 1);
    return !not_straight;
}


/* Returns 1 if the cards all have the same suit; returns 0 otherwise. */
int is_flush(card *hand, int size_of_hand) {
    /* STUDY THIS CODE.  WHY DOES IT PRODUCE THE INTENDED RESULT? */
    int flush = 1;
    int suit = hand[0].suit;
    for (int i = 1; i < size_of_hand; i++)
        flush = flush && (hand[i].suit == suit);
    return flush;
}


/* Returns 1 if three of the  cards in "hand" are three of a kind and another two are a pair; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value. */
int is_full_house(card *hand, int size_of_hand) {
    /* WRITE THIS FUNCTION */
    int fullHouse = 0;
    int firstCardValue = hand[0].value;
    int thirdCardValue = hand[2].value;

    if((firstCardValue == hand[1].value) && (thirdCardValue == hand[3].value && thirdCardValue == hand[4].value)){
        fullHouse = 1;
    }
    else if((firstCardValue == hand[1].value && firstCardValue == thirdCardValue) && (hand[3].value == hand[4].value)){
        fullHouse = 1;
    }
    return fullHouse;
}


/* Returns 1 if four of the cards in "hand" have the same value; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value. */
int is_four_of_kind(card *hand, int size_of_hand) {
    /* WRITE THIS FUNCTION */

    int fourKind = 0;
    int firstCardValue = hand[0].value;
    int secondCardValue = hand[1].value;
    if(firstCardValue == secondCardValue && firstCardValue == hand[2].value && firstCardValue == hand[3].value){
        fourKind = 1;
    }
    else if(secondCardValue == hand[2].value && secondCardValue == hand[3].value && secondCardValue == hand[4].value){
        fourKind = 1;
    }

    return fourKind;
}


/* Returns 1 if the cards in "hand" are both a straight and a flush; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value. */
int is_straight_flush(card *hand, int size_of_hand) {
    return is_straight(hand, size_of_hand) && is_flush(hand, size_of_hand);
}


int main(int argc, char const *argv[]) {
    srand(time(NULL));
    populate_deck();
    int sizeOfHand = 5;
    /* ADD WHATEVER CODE HERE YOU NEED */

    printf("\n\t\t|~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\t\t|     WELCOME TO     |\n");
    printf("\t\t|   FIVE CARD DRAW   |\n");
    printf("\t\t|   P  O  K  E  R    |\n");
    printf("\t\t|~~~~~~~~~~~~~~~~~~~~|\n\n\n");
    printf("~~~Current Hand~~~\n");
    card current_hand[sizeOfHand]; //creates a new blank hand
    print_currentHand(current_hand, sizeOfHand); //sorts and prints the current hand

    printf("\n\n"); //Spacing

    printf("How would you like to score your hand?\n");
    printf("1.  One Pair\n2.  Two Pair\n");
    printf("3.  Three of a Kind\n4.  Four of a Kind\n");
    printf("5.  Straight\n6.  Flush\n7.  Full House\n8.  Straight Flush\n");
    printf("9. Auto Score\n");
    printf("0. Exit\n\n");

    int selection = 1;


    while(selection!=0){
        scanf("%d", &selection); //Grabs user input for scoring
        switch(selection){
            case 0:
                exit(0);
                break;

            /* Manual scoring for one pair */
            case 1:
                if(is_pair(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with ONE PAIR! :)\n");
                }else{
                    printf("Sorry, it looks like your hand wasn't good enough\nto be scored in this category :(\n");
                    printf("Better luck next time!\n\n");
                }
                break;

            /* Manual scoring for two pair */
            case 2:
                if(is_two_pair(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with TWO PAIR! :)\n");
                }else{
                    printf("Sorry, it looks like your hand wasn't good enough\nto be scored in this category :(\n");
                    printf("Better luck next time!\n\n");
                }
                break;

            /* Manual scoring for three of a kind */
            case 3:
                if(is_three_of_kind(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with THREE OF A KIND! :)\n");
                }else{
                    printf("Sorry, it looks like your hand wasn't good enough\nto be scored in this category :(\n");
                    printf("Better luck next time!\n\n");
                }
                break;

            /* Manual scoring for four of a kind */
            case 4:
                if(is_four_of_kind(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with FOUR OF A KIND! :)\n");
                }else{
                    printf("Sorry, it looks like your hand wasn't good enough\nto be scored in this category :(\n");
                    printf("Better luck next time!\n\n");
                }
                break;

            /* Manual scoring for straight */
            case 5:
                if(is_straight(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with STRAIGHT! :)\n");
                }else{
                    printf("Sorry, it looks like your hand wasn't good enough\nto be scored in this category :(\n");
                    printf("Better luck next time!\n\n");
                }
                break;

            /* Manual scoring for flush */
            case 6:
                if(is_flush(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with FLUSH! :)\n");
                }else{
                    printf("Sorry, it looks like your hand wasn't good enough\nto be scored in this category :(\n");
                    printf("Better luck next time!\n\n");
                }
                break;

            /* Manual scoring for full house */
            case 7:
                if(is_full_house(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with FULL HOUSE! :)\n");
                }else{
                    printf("Sorry, it looks like your hand wasn't good enough\nto be scored in this category :(\n");
                    printf("Better luck next time!\n\n");
                }
                break;

            /* Manual scoring for straight flush */
            case 8:
                if(is_straight_flush(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with STRAIGHT FLUSH! :)\n");
                }else{
                    printf("Sorry, it looks like your hand wasn't good enough\nto be scored in this category :(\n");
                    printf("Better luck next time!\n\n");
                }
                break;

            /* This checks the hand in order of highest scoring to least so that the user will score in the highest possible category */
            case 9:
                if(is_straight_flush(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with STRAIGHT FLUSH! :)\n");
                    exit(0);
                }
                else if(is_full_house(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with FULL HOUSE! :)\n");
                    exit(0);
                }
                else if(is_flush(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with FLUSH! :)\n");
                    exit(0);
                }
                else if(is_straight(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with STRAIGHT! :)\n");
                    exit(0);
                }
                else if(is_four_of_kind(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with FOUR OF A KIND! :)\n");
                    exit(0);
                }
                else if(is_three_of_kind(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with THREE OF A KIND! :)\n");
                    exit(0);
                }
                else if(is_two_pair(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with TWO PAIR! :)\n");
                    exit(0);
                }
                else if(is_pair(current_hand, sizeOfHand)==1){
                    printf("Congrats! Your hand won with ONE PAIR! :)\n");
                    exit(0);
                }
                else{
                    printf("Sorry, it looks like your hand wasn't good enough\nto be scored on any of the categories :(\n");
                    printf("Better luck next time!\nThanks for playing!\n");
                    exit(0);
                }

            default:
                printf("Input invalid.\nPlease try again...\n\n");
                exit(0);
                break;

        }
        printf("\nPlease enter your next selection\n");
    }

    return 0;
}
