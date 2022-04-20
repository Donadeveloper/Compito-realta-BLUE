#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <locale>
#include "funzioniRimborso.h"

int main()
{
    setlocale(LC_ALL, "");
    std::fstream fileDati("DATIRIMBORSO.CSV", std::fstream::in);
    std::vector<datiRimborso> listaDati;
    caricamentoDati(listaDati, fileDati);

    mostramenu(listaDati, fileDati);

    fileDati.close();
    return 0;
}
