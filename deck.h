#ifndef DECK_H
#define DECK_H
#include <vector>
#include "card.h"


class Deck
{
    public:
        int broj_dekova;
        std::vector<Card> dek;


        Deck(int);
        void novi_dek();
        void ispisi_karte();

};

#endif // DECK_H
