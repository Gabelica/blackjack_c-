#include <iostream>
#include "game.h"

int main()
{
    std::string ime;
    Game black_jack(6,17); // broj dekova i djeljiteljev limit
    std::cout << "Unesite ime igraca: ";
    std::cin >> ime;
    black_jack.stvori_igraca(ime);
    black_jack.zapocni_igru();


}
