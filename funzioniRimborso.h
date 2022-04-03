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
void inserimentoDati(std::vector<datiRimborso>& listaDati);
int ricercaIdAuto(std::vector<datiRimborso> listaDati, const int idRicercato);
int ricercaIdPersona(std::vector<datiRimborso> listaDati, const int idRicercato);
void mostramenu();
void mostraDati(std::vector<datiRimborso> listaDati);
void mostra_per_IDAuto(std::vector<datiRimborso>& listaDati,const int pos_ID);
void mostra_per_IDPersona(std::vector<datiRimborso>& listaDati,const int pos_ID);