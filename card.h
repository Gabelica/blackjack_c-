#ifndef CARD_H
#define CARD_H
#include <string>


class Card
{
    public:
        Card(std::string, int );

        std::string zog;
        int broj;


        int vrijednost();
        void ispis_karte();

};

#endif // CARD_H
