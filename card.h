/*                       *
 * DO NOT EDIT THIS FILE *
 *                        */

/*
 * PokerLab (c) 2018-21 Christopher A. Bohn
 */

/******************************************************************************
 * This header, along with its source code, defines a card and provides a
 * couple of operations for cards
 ******************************************************************************/

#ifndef CARD_HEADER
#define CARD_HEADER


typedef enum {
    CLUBS, DIAMONDS, HEARTS, SPADES
} suits;

typedef struct {
    int value;      // 1=Ace, 11=Jack, 12=Queen, 13=Queen. 2-10 as that number. No other values allowed.
    suits suit;
} card;

card *create_card(int face, suits suit, card *blank_card);
char *display_card(card *the_card, char *display_string);

#endif  /* !CARD_HEADER */
