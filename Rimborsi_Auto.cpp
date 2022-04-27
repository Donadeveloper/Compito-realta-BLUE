#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <locale>
#include "funzioniRimborso.h"

int main()
{
    setlocale(LC_ALL, "");

    // Apertura file csv contenente i dati
    std::fstream fileDati("DATIRIMBORSO.csv", std::fstream::in);

    // Controllo che l'apertura sia andata a buon fine
    if (fileDati.fail()) {
        std::cout << "Lettura del file \"DATIRIMBORSO.csv\" fallita. Verificare che esso sia presente" << std::endl;
        exit(0);
    }

    // Creazione vector principale contenente i dati e caricamento da file
    std::vector<datiRimborso> listaDati;
    caricamentoDati(listaDati, fileDati);

    // Inizio output del programma
    mostramenu(listaDati, fileDati);

    // Chiusura programma e file csv
    std::cout << "Chiusura programma. . .";
    fileDati.close();
    return 0;
}
