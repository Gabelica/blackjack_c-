#include "game.h"
#include "deck.h"
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

Game::Game(int broj_dekova, int l)
{
    dek = new Deck(broj_dekova);
    limit = l;
    imam_igraca = false;
}


void Game::stvori_igraca(std::string i)
{
    if(!imam_igraca)
    {
        igrac = new Player(i);
        std::cout << igrac->ime << " se pridruzio stolu!\n";
    }
    else
    {
        std::cout << igrac->ime << " je vec za stolom!\n";
        return;
    }
    imam_igraca = true;
}

void Game::zapocni_igru()
{
    if(!imam_igraca)
    {
        std::cout << "Igrac ne postoji!\n";
        return;
    }

    //GAME LOOP
    std::cout << "Zapoceli ste novu igru sa " << dek->broj_dekova << " deka i djelitelj udara do "<< limit << ".\nIme igraca je "<< igrac->ime << " i ima " << igrac->novac << " kuna.\n";

    while (igrac->novac > 0)
    {
        int isplata = 2;
        //UNOS ULOGA
            std::cout << "\nUnesite ulog :";
            int ulog;
            std::cin >> ulog;

            //PROVJERA DA JE ULOG U SKLADU S PRAVILIMA
            while (igrac->napravi_ulog(ulog))
            {
                std::cout <<"Neispravan ulog!\nMolimo unesite ponovno :";
                std::cin >> ulog;
            }
            if (ulog == 0)
            {
                igrac->info();
                 return;
            }
            igrac->novac -= ulog;
            int nagrada = (ulog*isplata);

                //DJELJENJE
        igrac->primi_kartu(dijeli());
        igrac->primi_kartu(dijeli());
        std::cout << "\n\tVas zbroj bodova iznosi " << igrac->izracunaj_bodove() << ". \n";
        primi_kartu(dijeli(),true);
        primi_kartu(dijeli(),false);

        //IGRAC IGRA
        char unos = '\0';
        int broj_unosa = 0;

        if (igrac->izracunaj_bodove() == 21)
            igrac->pobjeda(nagrada);
        else if (izracunaj_bodove() == 21)
            pobjeda();

        std::cout << "\n\t(S)tani, (P)rimi, (D)upliraj\n";

        while(unos!='s')
        {
            std::cin >> unos;
            if(broj_unosa == 0 && unos == 'd')
            {
                isplata = 4;
                igrac->primi_kartu(dijeli());
                provjera_21();
                unos = 's';
                break;
            }
            else if (unos == 'p')
            {
                igrac->primi_kartu(dijeli());

                if (igrac->izracunaj_bodove()> 21)
                    {
                        igrac->izgubio();
                        break;
                    }
                std::cout << "(S)tani, (P)rimi\n";
                std::cout << "Trenutni broj bodova iznosi: " << igrac->izracunaj_bodove() << " \n";
                unos = '\0';

            }
            else
                break;
            broj_unosa++;
        }

        //DJELJITELJ IGRA
        std::cout << "\n\tDjeljiteljev red.\n";
            while (izracunaj_bodove() <= limit)
        {
            primi_kartu(dijeli(),true);
            pauza_konzole();
        }


        //KRAJ IGRE
        system("cls");
        std::cout << "Trenutni broj  vasih bodova iznosi: " << igrac->izracunaj_bodove() << " \n";
        std::cout << "Trenutni broj djeliteljevih bodova iznosi: " << izracunaj_bodove() << " \n";

        std::cout << "\n\n\t";
        dobitnik(nagrada);


        std::cout << "\n\tPritisni bilo koju tipku za nastavak.";
        std::cin >> unos;
        igrac->info();
        igrac->nova_ruka();
        nova_ruka();

    }
}

Card Game::dijeli()
{
    Card temp = dek->dek.back();
    dek->dek.pop_back();
    return temp;
}

void Game::nova_ruka()
{
    djeliteljeve_karte.clear();
}

void Game::primi_kartu(Card k, bool t)
{
    djeliteljeve_karte.push_back(k);
    if (t)
    {
        std::cout << "\n\tDjeljitelj prima kartu "; k.ispis_karte(); std::cout << "\n" ;
        std::cout << "\n\tDjeljitelj ima karte: ";ispisi_karte();
        std::cout << "\n\tTrenutni broj djeliteljevih bodova iznosi: " << izracunaj_bodove() << " \n";
    }
    else
        std::cout << "\n\tDjeljitelj prima kartu XX\n";


}

void Game::ispisi_karte()
{
    for(std::vector<Card>::iterator it = djeliteljeve_karte.begin(); it != djeliteljeve_karte.end(); it++)
    {
       it->ispis_karte(); std::cout << "  ";
    }
    std::cout << "\n";
}

int Game::izracunaj_bodove()
{
    int vrijednost = 0;
    int broj_aseva = 0;
    for(std::vector<Card>::iterator it = djeliteljeve_karte.begin(); it!=djeliteljeve_karte.end(); it++)
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

bool Game::provjera_21()
{
    if (izracunaj_bodove() > 21)
        return true;
    else
        return false;
}

void Game::pobjeda()
{
    std::cout << "Nazalost izgubili ste!\n";
}

void Game::izgubio(int u)
{
    igrac->pobjeda(u);
}

void Game::pauza_konzole()
{
    std::this_thread::sleep_for (std::chrono::seconds(1));
}

void Game::dobitnik(int n)
{
    if(igrac->provjera_21()==false && provjera_21()==false)
    {
        if (igrac->izracunaj_bodove()==21)
        {
            igrac->pobjeda(n);
        }
    else if (izracunaj_bodove() < igrac->izracunaj_bodove())
        {
            igrac->pobjeda(n);
        }
    else
        {
            pobjeda();
            igrac->izgubio();
        }
    }
    else
    {
        if (provjera_21() == true)
            igrac->pobjeda(n);
        else if (igrac->provjera_21() == true)
            igrac->izgubio();
    }
}
