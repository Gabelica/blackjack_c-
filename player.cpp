#include "player.h"
#include <iostream>
#include <stdlib.h>

Player::Player(std::string i)
{
    novac = 1000;
    ime = i;
}

void Player::ispisi_karte()
{
    for(std::vector<Card>::iterator it = ruka.begin(); it != ruka.end(); it++)
    {
        it ->ispis_karte();
    }
}

bool Player::napravi_ulog(int n)
{
    return novac-n>=0 && n>=0?false:true;
}

void Player::info()
{
    system("cls");
    std::cout << "\n/////////////////////////////////////////////////////////////////\n";
    std::cout << "\t\t" << ime <<"\n\t\tIznos na racunu je "<< novac << "kuna.\n";
    std::cout << "/////////////////////////////////////////////////////////////////\n";
}

void Player::nova_ruka()
{
    ruka.clear();
}

void Player::primi_kartu(Card k)
{
    ruka.push_back(k);
    std::cout << ime << " prima kartu "; k.ispis_karte();
}

int Player::izracunaj_bodove()
{
    int vrijednost = 0;
    int broj_aseva = 0;
    for(std::vector<Card>::iterator it = ruka.begin(); it!=ruka.end(); it++)
    {
        vrijednost += it->vrijednost();
        if(it->vrijednost() == 11)
            broj_aseva++;
    }
    if (vrijednost > 21 && broj_aseva == 0)
    {
        return vrijednost;
    }
    else if (vrijednost > 21)
    {
        for (int i = 0; i < broj_aseva; i++)
        {
            vrijednost -= 10;
            if(vrijednost <= 21)
                return vrijednost;
        }
    }
    return vrijednost;
}

bool Player::provjera_21()
{
    if (izracunaj_bodove() > 21)
        return true;
    else
        return false;
}

void Player::pobjeda(int u)
{
    std::cout << "Cestitamo pobjedili ste!\n";
    novac += (u);
}
void Player::izgubio()
{
    if (provjera_21() == true)
        std::cout << "Presli ste 21 i izgubili ste igru!\n";
    else
        std::cout << "Djeljitelj je imao vise bodova od vas!\n";
}
