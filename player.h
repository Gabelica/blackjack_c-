#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "card.h"


class Player
{
    public:
        int novac;
        std::vector<Card> ruka;
        std::string ime;

        Player(std::string);
        void ispisi_karte();
        bool napravi_ulog(int);
        void info();
        void nova_ruka();
        void primi_kartu(Card k);
        int izracunaj_bodove();
        bool provjera_21();
        void pobjeda(int);
        void izgubio();


};

#endif // PLAYER_H
