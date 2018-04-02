#ifndef GAME_H
#define GAME_H
#include "deck.h"
#include "player.h"



class Game
{
    public:
        Game(int, int);
        int limit;
        Deck *dek;
        Player *igrac;
        std::vector<Card> djeliteljeve_karte;
        bool imam_igraca;
        void stvori_igraca(std::string);
        void zapocni_igru();
        Card dijeli();
        void nova_ruka();
        void primi_kartu(Card, bool);
        void ispisi_karte();
        int izracunaj_bodove();
        bool provjera_21();
        void pobjeda();
        void izgubio(int);
        void pauza_konzole();
        void dobitnik(int);



};

#endif // GAME_H
