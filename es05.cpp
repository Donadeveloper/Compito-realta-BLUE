#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <locale>
#include "funzioniRimborso.h"

int main()
{
    setlocale(LC_ALL, "");
    std::fstream inputFile("DATIRIMBORSO.CSV", std::fstream::in);
    std::vector<datiRimborso> listaDati;
    caricamentoDati(listaDati, inputFile);

    ordinamentoDati(listaDati);
    mostramenu(listaDati);

    return 0;
}
