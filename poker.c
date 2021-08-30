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
    return -1;
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
    return -1;
}


/* Returns 1 if four of the cards in "hand" have the same value; returns 0 otherwise.
 * "hand" must be sorted from least value to greatest value. */
int is_four_of_kind(card *hand, int size_of_hand) {
    /* WRITE THIS FUNCTION */
    return -1;
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
    printf("\t\t|   P  O  K  E  R    |\n");
    printf("\t\t|~~~~~~~~~~~~~~~~~~~~|\n\n\n");
    printf("~~~Current Hand~~~\n");
    card current_hand[sizeOfHand]; //creates a new blank hand
    print_currentHand(current_hand, sizeOfHand); //sorts and prints the current hand

    printf("\n\n"); //Spacing

    printf("How would you like to score your hand?\n");
    printf("1.  One Pair\n2.  Two Pair\n");
    printf("3.  Three of a Kind\n4.  Four of a Kind\n");
    printf("5.  Straight\n6.  Flush\n7.  Full House\n8.  Straight Flush\n\n");




//    for(int i=0; i<53; i++){
//        char *s = malloc(21);
//       printf("%s\n", display_card(&deck[i], s));
//    }
    return 0;
}
