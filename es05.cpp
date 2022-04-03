#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <locale>
#include "funzioniRimborso.h"

int main()
{
    int scelta;
    bool ciclo = true;
    std::fstream inputFile("DATIRIMBORSO.CSV", std::fstream::in);
    std::vector<datiRimborso> listaDati;
    int IDcercato;
    int IDtrovato;
    caricamentoDati(listaDati, inputFile);
    setlocale(LC_ALL, "");

    while (ciclo)
    {
        ordinamentoDati(listaDati);
        mostramenu();
        std::cout << "\n n scelta: ";
        std::cin >> scelta;
        switch(scelta)
        {
        case 1:
            inserimentoDati(listaDati);
            break;
        case 2:
             std::cout << "Inserisci l'ID dell'auto che vuoi cercare:  ";
            std::cin >> IDcercato;
            IDtrovato = ricercaIdAuto(listaDati, IDcercato);
            if (IDtrovato!=-1)
                mostra_per_IDAuto(listaDati,IDtrovato);
            else
                std::cout << "non presente\n";
            break;
        case 3:
            std::cout << "Inserisci l'ID della persona che vuoi cercare:  ";
            std::cin >> IDcercato;
            IDtrovato = ricercaIdPersona(listaDati, IDcercato);
            if (IDtrovato!=-1)
                mostra_per_IDPersona(listaDati,IDtrovato);
            else
                std::cout << "non presente\n";
            break;
        case 4:
            break;
        case 5:
            mostraDati(listaDati);
            break;
        case 6:
            break;
        case 7:
            ciclo=false;
        }
        system("pause");
        system("cls");
    }
    return 0;

}