#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <locale>
#include "funzioniRimborso.h"

int main()
{
    setlocale(LC_ALL, "");
    std::fstream fileDati("DATIRIMBORSO.csv", std::fstream::in);
    if (fileDati.fail()) {
        std::cout << "Lettura del file \"DATIRIMBORSO.csv\" fallita. Verificare che esso sia presente" << std::endl;
        exit(0);
    }
    std::vector<datiRimborso> listaDati;
    caricamentoDati(listaDati, fileDati);

    mostramenu(listaDati, fileDati);

    fileDati.close();
    return 0;
}
