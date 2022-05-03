#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct datiRimborso {

    int idAuto;
    std::string des_auto;
    std::string targa_Auto;
    double costo_km_auto;
    unsigned int idPersona;
    unsigned int AnnoRimb;
    unsigned int MeseRimb;
    long long int km_rimborso;
};

void caricamentoDati(std::vector<datiRimborso>& listaDati, std::fstream& inputFile);
int stringToInt(std::string);
double stringToDouble(std::string);
void ordinamentoDati(std::vector<datiRimborso>& listaDati);
void intBubbleSort(std::vector<int>& vect);
void inserimentoDati(std::vector<datiRimborso>& listaDati, bool &modDaSalvare);
int ricercaIdAuto(std::vector<datiRimborso> listaDati, const int idRicercato);
void ricercaIdPersona(std::vector<datiRimborso> listaDati, const int idRicercato, std::vector<int> &IdPersonaTrovati);
int ricercaTarga(std::vector<datiRimborso> listaDati, std::string targaRicercata);
void mostramenu();
void mostraDati(std::vector<datiRimborso> listaDati);
void mostra_per_IDAuto(std::vector<datiRimborso>& listaDati,const int pos_ID);
void mostra_per_IDPersona(std::vector<datiRimborso>& listaDati, std::vector<int> &IdPersonaTrovati) ;
void salvaDati(std::vector<datiRimborso> &listaDati, std::fstream &fileDati);
void cancellaRimborso(std::vector<datiRimborso>& listaDati, const int idDaEliminare, bool &modDaSalvare);
bool convalida_targa(const std::string targa);