#include "card.h"
#include <iostream>

Card::Card(std::string z, int b)
{
    zog = z;
    broj = b;
}

int Card::vrijednost()
{
    if (broj >= 10 )
        return 10;
    else if(broj == 1)
        return 11;
    return broj;
}

void Card::ispis_karte()
{
    std::cout << broj << " " << zog << "\t";
}


