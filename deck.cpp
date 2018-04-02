#include "deck.h"
#include <algorithm>

Deck::Deck(int b)
{
    broj_dekova = b;
    novi_dek();
}

void Deck::novi_dek()
{
    dek.clear();
    for(int i = 0; i < broj_dekova; i++)
    {
        for(int j = 1; j < 14; j++)
        {
            dek.push_back(Card("Hearts",j));
            dek.push_back(Card("Clubs",j));
            dek.push_back(Card("Diamonds",j));
            dek.push_back(Card("Spades",j));
        }
    }
    std::random_shuffle(dek.begin(), dek.end());
}

void Deck::ispisi_karte()
{
    for (std::vector<Card>::iterator it = dek.begin() ; it != dek.end(); it++)
    {
        it->ispis_karte();
    }
}
