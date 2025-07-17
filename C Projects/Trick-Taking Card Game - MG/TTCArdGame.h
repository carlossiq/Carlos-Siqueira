#pragma once

#include "../carlos.h"
#include <string.h>
#include <ctype.h>
#define MAX_CARDS 52

enum
{
    spades,
    hearts,
    clubs,
    diamonds
};
enum
{
    ace = 1,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king
};

typedef struct
{
    int suit; // 0: Spades, 1: Hearts, 2: Clubs, 3: Diamonds
    int rank; // 1-13 (Ace to King)
} card;

typedef struct
{
    card *cards;
    int top;
} deck;

typedef enum
{
    playerTurn,
    computerTurn
} turnType;

typedef struct
{
    card *array;
    size_t size;
    turnType turn;
} Hand;

typedef struct
{
    card *array;
    size_t size;
    size_t capacity;
} Table;

typedef struct
{
    string name;
    int scorre;
} Player;

typedef struct
{
    deck *d;
    Hand **hand;
    Table *table;
    Player *players;
    turnType currentTurn;
} Game;

// Declarações
card *createCard(int suit, int rank);
deck *createDeck();
card *pickCardFromDeck(deck *d);
bool isValidCard(card *c);
bool isValidDeck(deck *d);
bool isDeckEmpty(deck d);
bool isValidCardString(string s);
void addCardToDeck(deck *d, card *c);
void addCardToHand(Hand *h, card *c);
void addCardToTable(Table *t, card *newCard);
void removeCardFromDeck(deck *d, card takenCard);
void removeCardsByNumber(deck *d, int cardToRemove);
void removeCardFromHand(Hand *h, card *c);
int findCardInDeck(deck *d, card *c);
int findCardInHand(Hand *h, card *c);
int toCard(char c);
void shuffleDeck(deck *d);
void printDeck(deck *d);
void printCard(card *c);
void printHand(Hand *h);
void printTable(Table *t);
bool isValidHand(Hand *h);
int RunGame(string playerName);
void dealCards(Game *game);

int toCard(char c)
{
    if (c >= '2' && c <= '9')
        return c - '0';
    if (toupper(c) == 'A')
        return ace;
    if (toupper(c) == 'S')
        return spades;
    if (toupper(c) == 'H')
        return hearts;
    if (toupper(c) == 'C')
        return clubs;
    if (toupper(c) == 'D')
        return diamonds;
    if (toupper(c) == 'J')
        return jack;
    if (toupper(c) == 'Q')
        return queen;
    if (toupper(c) == 'K')
        return king;
    return -1;
}

bool isValidCardString(string s)
{
    if (strlen(s) < 2)
        return false;
    int suitSymbols[] = {'S', 'H', 'C', 'D'};
    char *rankNames[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    for (int i = 0; i < 4; i++)
    {
        if (toupper(s[0]) == suitSymbols[i])
        {
            for (int j = 0; j < 13; j++)
            {
                if (strcmp(s + 1, rankNames[j]) == 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isValidHand(Hand *h)
{
    if (h == NULL)
    {
        fprintf(stderr, "Hand is NULL\n");
        exit(EXIT_FAILURE);
    }
    return (h->size >= 0 && h->size <= 4);
}

void setCard(Table *t, Hand *h)
{
    if (!isValidHand(h) || t == NULL)
    {
        fprintf(stderr, "Table or Hand is NULL\n");
        exit(EXIT_FAILURE);
    }
    if (h->size == 0)
    {
        fprintf(stderr, "Hand is empty\n");
        return;
    }
    string cardString;
    do
    {
        cardString = getString("Set the Card: ");
    } while (!isValidCardString(cardString));

    card *newCard = malloc(sizeof(card));
    if (!newCard)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newCard->suit = toCard(cardString[0]);
    if (isdigit(cardString[1]))
        newCard->rank = atoi(cardString + 1);
    else
        newCard->rank = toCard(cardString[1]);

    if (!isValidCard(newCard))
    {
        fprintf(stderr, "Invalid card\n");
        free(newCard);
        exit(EXIT_FAILURE);
    }

    addCardToTable(t, newCard);
    removeCardFromHand(h, newCard);
    free(newCard);
}

card *createCard(int rank, int suit)
{
    card *newCard = malloc(sizeof(card));
    if (!newCard)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newCard->suit = suit;
    newCard->rank = rank;
    return newCard;
}

bool isValidCard(card *c)
{
    if (c == NULL)
    {
        fprintf(stderr, "Card is NULL\n");
        exit(EXIT_FAILURE);
    }
    return (c->suit >= spades && c->suit <= diamonds && c->rank >= ace && c->rank <= king);
}

bool isValidDeck(deck *d)
{
    if (d == NULL)
    {
        fprintf(stderr, "Deck is NULL\n");
        exit(EXIT_FAILURE);
    }
    return (d->top >= 0 && d->top <= MAX_CARDS);
}

void addCardToDeck(deck *d, card *c)
{
    if (!isValidDeck(d) || !isValidCard(c))
    {
        fprintf(stderr, "Invalid deck/card\n");
        exit(EXIT_FAILURE);
    }
    if (d->top >= MAX_CARDS)
    {
        fprintf(stderr, "Deck is full\n");
        exit(EXIT_FAILURE);
    }

    if (d->cards == NULL)
    {
        d->cards = malloc(MAX_CARDS * sizeof(card));
        if (!d->cards)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    d->cards[d->top++] = *c;
}

void addCardToHand(Hand *h, card *c)
{
    if (!isValidCard(c))
    {
        fprintf(stderr, "Invalid card\n");
        exit(EXIT_FAILURE);
    }
    card *newArray = realloc(h->array, (h->size + 1) * sizeof(card));
    if (!newArray)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(h->array);
        exit(EXIT_FAILURE);
    }
    h->array = newArray;
    h->array[h->size++] = *c;
}

void addCardToTable(Table *t, card *newCard)
{
    if (!isValidCard(newCard))
    {
        fprintf(stderr, "Invalid card\n");
        exit(EXIT_FAILURE);
    }
    card *newCards = realloc(t->array, (t->size + 1) * sizeof(card));
    if (!newCards)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(t->array);
        exit(EXIT_FAILURE);
    }
    t->array = newCards;
    t->array[t->size++] = *newCard;
}

card *pickCardFromDeck(deck *d)
{
    if (!isValidDeck(d) || d->top == 0)
    {
        fprintf(stderr, "Deck empty or invalid\n");
        exit(EXIT_FAILURE);
    }
    card *newCard = createCard(d->cards[d->top - 1].rank, d->cards[d->top - 1].suit);
    removeCardFromDeck(d, *newCard);
    return newCard;
}

void printCard(card *c)
{
    if (!isValidCard(c))
    {
        fprintf(stderr, "Invalid card\n");
        exit(EXIT_FAILURE);
    }
    int suitSymbols[] = {'S', 'H', 'C', 'D'};
    char *rankNames[] = {"", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    printf("%s%c\n", rankNames[c->rank], suitSymbols[c->suit]);
}

void printDeck(deck *d)
{
    if (!isValidDeck(d))
    {
        fprintf(stderr, "Invalid deck\n");
        exit(EXIT_FAILURE);
    }
    int suitSymbols[] = {'S', 'H', 'C', 'D'};
    char *rankNames[] = {"", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    for (int i = 0; i < d->top; i++)
        printf("%s%c ", rankNames[d->cards[i].rank], suitSymbols[d->cards[i].suit]);
    printf("\n");
}

void printHand(Hand *h)
{
    if (!isValidHand(h))
    {
        fprintf(stderr, "Invalid hand\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < h->size; i++)
        printCard(&h->array[i]);
}

void printTable(Table *t)
{
    if (!t || !t->array)
    {
        fprintf(stderr, "Table is NULL or empty\n");
        return;
    }
    for (size_t i = 0; i < t->size; i++)
        printCard(&t->array[i]);
}

deck *createDeck()
{
    deck *d = malloc(sizeof(deck));
    if (!d)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    d->cards = NULL;
    d->top = 0;
    for (int suit = spades; suit <= diamonds; suit++)
        for (int rank = ace; rank <= king; rank++)
        {
            card *newCard = createCard(rank, suit);
            addCardToDeck(d, newCard);
            free(newCard);
        }
    return d;
}

int RunGame(string playerName)
{
    Game *game = malloc(sizeof(Game));
    if (!game)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    game->d = createDeck();
    // ... iniciar players, mãos, mesa, etc.
    printf("Game started for %s\n", playerName);
    // Liberar depois (exemplo)
    free(game->d->cards);
    free(game->d);
    free(game);
    return 0;
}
