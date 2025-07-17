#include <stdio.h>
#include "TTCArdGame.h"

int main(void)
{
    // if(argc != 2) {
    //     printf("Need to set the name of the playes as an argument.\n");
    //     return 1;
    // } else{
    //     string player = argv[1];
    // }

    deck *d = createDeck();
    // shuffleDeck(d);
    removeCardsByNumber(d, ace);
    printDeck(d);
    int a = findCardInDeck(d, &(card){.suit = hearts, .rank = two});
    printf("%d\n", a);
    free(d->cards);
    free(d);

    return 0;
}