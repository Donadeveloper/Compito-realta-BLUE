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

void mostramenu()
{
    std::cout << "\n\n\t\t------RIMBORSO AUTO------\n";
    std::cout << "\n\tBenvenuto nella gestione dei rimborsi auto cosa vuoi fare?:\n";
    std::cout << "\t [1]  Inserire un rimborso\n";
    std::cout << "\t [2]  Ricercare una vettura presente nel database dei rimborsi\n";
    std::cout << "\t [3]  Ricercare una persona presente nel database dei rimborsi\n";
    std::cout << "\t [4]  Rimuovere un rimborso presente nel database dei rimborsi\n";
    std::cout << "\t [5]  Mostrare i rimborsi presenti nel database dei rimborsi\n";
    std::cout << "\t [6]  Salvataggio \n";
    std::cout << "\t [7]  ESC\n";
}

void mostraDati(std::vector<datiRimborso>listaDati) {
    // Questa funzione stampa a video una tabella contenente tutti i dati presenti nel database

    std::cout << "\n|ID PERSONA\t|ID AUTO\t|TARGA\t\t|COSTO(Euro/Km)\t|KM AUTO\t|MESE\t|ANNO\t|DESCRIZIONE AUTO\n" <<
            "----------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < listaDati.size(); i++) {

        std::cout << "|" << listaDati[i].idPersona << "\t";
        if (listaDati[i].idPersona < 1000000) {
            // Se l'id persona non supera il milione stampo un altro tab (causa formattazione della tabella)
            std::cout << "\t";
        }
        std::cout << "|" << listaDati[i].idAuto << "\t\t";
        std::cout << "|" << listaDati[i].targa_Auto << "\t";
        std::cout << "|" << listaDati[i].costo_km_auto << "\t\t";
        std::cout << "|" << listaDati[i].km_rimborso << "\t";
        if (listaDati[i].km_rimborso < 1000000) {
            // Se l'id auto non supera il milione stampo un altro tab (causa formattazione della tabella)
            std::cout << "\t";
        }
        std::cout << "|" << listaDati[i].MeseRimb << "\t";
        std::cout << "|" << listaDati[i].AnnoRimb << "\t";
        std::cout << "|" << listaDati[i].des_auto << "\t" << std::endl;
    }
}

void inserimentoDati(std::vector<datiRimborso>& listaDati) {
    /* Questa funzione chiede all'utente tutti i dati di una nuova struct da inserire nei rimborsi, e poi la inserisce nel vettore ordinatamente
    Poichè il campo idAuto deve essere un numero che identifica univocamente un'auto, nel caso in cui l'utente ne inserisca uno già
    esistente, egli può decidere se eliminare l'attuale inserimento o sovrascrivere il vecchio rimborso */

    const int CARATTERI_TARGA = 7;
    datiRimborso datiInseriti;
    int nRimborsi = listaDati.size();
    int buffer_int;
    std::string buffer_string;
    double buffer_double;
    char buffer_char;
    int indiceAutoPresente = -1;
    bool sovrascrittura = false;

    std::cout << "\n[INSERIMENTO NUOVO RIMBORSO]";

    // Inserimento idPersona
    do {
        std::cout << "\nID Persona - numero intero identificativo della persona: ";
        std::cin >> buffer_int;
    } while (buffer_int <= 0);
    datiInseriti.idPersona = buffer_int;

    // Inserimento idAuto
    do {
        std::cout << "ID Auto - numero intero identificativo dell'auto: ";
        std::cin >> buffer_int;
    } while (buffer_int <= 0);

    // Gestione del caso in cui l'idAuto inserito sia già presente tra i dati
    indiceAutoPresente = ricercaIdAuto(listaDati, buffer_int);

    if (indiceAutoPresente >= 0) {
        do {
            std::cout << "\n[!] ID AUTO TROVATO NEI DATI.\nInterrompere l'inserimento del nuovo rimborso o sovrascrivere quello gia esistente?(i/s): ";
            std::cin >> buffer_char;
        } while (buffer_char != 'i' && buffer_char != 'I' && buffer_char != 's' && buffer_char != 'S');
        if (buffer_char == 'i' || buffer_char == 'I')
            return;
        else {
            sovrascrittura = true;
            std::cout << "Verr� sovrascritto il rimborso dell'auto di ID " << buffer_int << ". Targa e descrizione non verranno modificati\n\n";
        }
    }
    datiInseriti.idAuto = buffer_int;

    // Inserimento targa
    if (sovrascrittura)
        datiInseriti.targa_Auto = listaDati[indiceAutoPresente].targa_Auto;
    else {
        do {
            std::cout << "Targa auto (7 caratteri): ";
            std::cin >> buffer_string;
        } while (buffer_string.size() != CARATTERI_TARGA);
        datiInseriti.targa_Auto = buffer_string;
    }

    // Inserimento costo_km_auto
    do {
        std::cout << "Costo al km dell'auto: ";
        std::cin >> buffer_double;
    } while (buffer_double <= 0.0);
    datiInseriti.costo_km_auto = buffer_double;

    // Inserimento anno rimborso
    do {
        std::cout << "Anno del rimborso dell'auto: ";
        std::cin >> buffer_int;
    } while (buffer_int < 1960 || buffer_int > 3000);
    datiInseriti.AnnoRimb = buffer_int;

    // Inserimento mese rimborso
    do {
        std::cout << "Mese del rimborso dell'auto: ";
        std::cin >> buffer_int;
    } while (buffer_int < 1 || buffer_int > 12);
    datiInseriti.MeseRimb = buffer_int;

    // Inserimento km_rimborso
    do {
        std::cout << "Km da rimborsare: ";
        std::cin >> buffer_int;
    } while (buffer_int <= 0 || buffer_int > 10000000);
    datiInseriti.km_rimborso = buffer_int;

    // Inserimento descrizione auto
    if (sovrascrittura)
        datiInseriti.des_auto = listaDati[indiceAutoPresente].des_auto;
    else {
        do {
            std::cout << "Descrizione auto (generalmente è il produtore): ";
            std::cin >> buffer_string;
        } while (buffer_string.size() > 20);
        datiInseriti.des_auto = buffer_string;
    }

    // Inserimento del rimborso finale nel vettore contenente tutti i dati e ordinamento
    if (sovrascrittura) {
        listaDati[indiceAutoPresente] = datiInseriti;
    }
    else {
        listaDati.push_back(datiInseriti);
    }
    ordinamentoDati(listaDati);
    return;

}


void ordinamentoDati(std::vector<datiRimborso>& listaDati) {
    // Questa funzione ordina le struct contenute nel vettore listaDati secondo il loro campo "idPersona"
    // L'algoritmo di ordinamento utilizzato è il bubble sort ottimizzato con sentinella
    // Ad ogni iterazione del bubble sort, se i due elementi comparati hanno idPersona uguale, essi vengono ordinati secondo il campo targa

    int vectSize;
    datiRimborso temp_swap;

    vectSize = listaDati.size();

    bool sentinella_swap;
    for (int i = 0; i < vectSize; i++) {
        sentinella_swap = false;
        for (int j = 0; j < vectSize - 1 - i; j++) {
            if (listaDati[j].idPersona > listaDati[j + 1].idPersona) {
                // Ordinamento per IdPersona
                temp_swap = listaDati[j];
                listaDati[j] = listaDati[j + 1];
                listaDati[j + 1] = temp_swap;
                sentinella_swap = true;
            }
            if ((listaDati[j].idPersona == listaDati[j + 1].idPersona) && (listaDati[j].targa_Auto > listaDati[j + 1].targa_Auto)) {
                // Se due elementi hanno idPersona uguale, li ordino in base al campo "targa" (secondo l'ordine alfabetico)
                temp_swap = listaDati[j];
                listaDati[j] = listaDati[j + 1];
                listaDati[j + 1] = temp_swap;
                sentinella_swap = true;
            }
        }
        if (sentinella_swap == false) {
            // Se non ho scambiato di posto nessuna struct in un'iterazione, il vettore � ordinato e posso uscire dal ciclo
            break;
        }

    }
    return;
}

void caricamentoDati(std::vector<datiRimborso>& listaDati, std::fstream& inputFile)
{
    datiRimborso temporaneo;
    std::string temp;
    while (!inputFile.eof())
    {
        getline(inputFile, temp, ';');
        temporaneo.idPersona = stringToInt(temp);

        getline(inputFile, temp, ';');
        temporaneo.idAuto = stringToInt(temp);

        getline(inputFile, temporaneo.targa_Auto, ';');

        getline(inputFile, temp, ';');
        temporaneo.costo_km_auto = stringToDouble(temp);

        getline(inputFile, temp, ';');
        temporaneo.AnnoRimb = stringToInt(temp);

        getline(inputFile, temp, ';');
        temporaneo.MeseRimb = stringToInt(temp);

        getline(inputFile, temp, ';');
        temporaneo.km_rimborso = stringToDouble(temp);

        getline(inputFile, temporaneo.des_auto);

        listaDati.push_back(temporaneo);
    }

    listaDati.pop_back();

    return;
}

int stringToInt(std::string str)
{
    int dim = str.length(), temp = 0;
    for (int i = 0; i < dim; i++)
    {
        if ((str[i] >= '0') && (str[i] <= '9'))
        {
            temp = temp * 10;
            temp = temp + (str[i] - '0');
        }
    }
    return temp;
}

double stringToDouble(std::string str)
{
    int dim = str.length();
    double temp = 0, divisore = 1, moltiplicatore = 10;
    bool decimale = false;

    for (int i = 0; i < dim; i++)
    {
        if (decimale)
        {
            divisore = divisore * 10;
            moltiplicatore = 1;
        }
        if ((str[i] >= '0') && (str[i] <= '9'))
        {
            temp = temp * moltiplicatore;
            temp = temp + ((str[i] - '0') / divisore);
        }
        if (str[i] == '.')
        {
            decimale = true;
        }
    }
    return temp;
}

void ordinamentoDati_secondo_idAuto(std::vector<datiRimborso>& listaDati) {
    /* questo ordinamento deve essere fatto quando si richiede una ricerca per IDAuto
    che altrimenti potrebbe dare problemi se per esempio la persona con IDPersona 1
    ha l'auto con ID 24 questo perchè l'ordinamento del database in generale è fatto secondo l'IDPersona */

    int vectSize;
    datiRimborso temp_swap;

    vectSize = listaDati.size();

    bool sentinella_swap;
    for (int i = 0; i < vectSize; i++) {
        sentinella_swap = false;
        for (int j = 0; j < vectSize - 1 - i; j++) {
            if (listaDati[j].idAuto > listaDati[j + 1].idAuto) {
                // Ordinamento per IdAuto
                temp_swap = listaDati[j];
                listaDati[j] = listaDati[j + 1];
                listaDati[j + 1] = temp_swap;
                sentinella_swap = true;
            }
        }
        if (sentinella_swap == false) {
            // Se non ho scambiato di posto nessuna struct in un'iterazione, il vettore è ordinato e posso uscire dal ciclo
            break;
        }

    }
    return;
}

int ricercaIdAuto(std::vector<datiRimborso> listaDati, const int idRicercato)//ricerca secondo IDAuto
{
    ordinamentoDati_secondo_idAuto(listaDati);//ordinamento per poter usufruire della ricerca per IDAuto
    int sx = 0, dx = listaDati.size() - 1, med, pos = -1;
    while ((sx <= dx) && (pos == -1))
    {
        med = (sx + dx) / 2;
        if (listaDati[med].idAuto == idRicercato)
            pos = med;
        else if (idRicercato < listaDati[med].idAuto)
                dx = med - 1;                           //se l'ID è più piccolo allora il punto destro diminuirà cosi da spostare il punto medio per la ricerca più a sinistra
        else
        {
            sx = med + 1;                               //se l'ID è più grande allora il punto sinistro aumenterà cosi da spostare il punto medio per la ricerca più a destra
        }
    }
    return pos;
}

int ricercaIdPersona(std::vector<datiRimborso> listaDati, const int idRicercato) //ricerca secondo IDPersona
{
    int sx = 0, dx = listaDati.size() - 1, med, pos = -1;
    while ((sx <= dx) && (pos == -1))
    {
        med = (sx + dx) / 2;
        if (listaDati[med].idPersona == idRicercato)
            pos = med;
        else if (idRicercato < listaDati[med].idPersona)
            dx = med - 1;                               //se l'ID è più piccolo allora il punto destro diminuirà cosi da spostare il punto medio per la ricerca più a sinistra
        else
        {
            sx = med + 1;                               //se l'ID è più grande allora il punto sinistro aumenterà cosi da spostare il punto medio per la ricerca più a destra
        }
    }
    return pos;
}

void mostra_per_IDAuto(std::vector<datiRimborso>& listaDati,const int pos_ID)   //funzione che mostra tutti i dati inerenti all'IDAuto cercato
{
    std::cout << "\n|ID PERSONA\t|ID AUTO\t|TARGA\t\t|COSTO(Euro/Km)\t|KM AUTO\t|MESE\t|ANNO\t|DESCRIZIONE AUTO\n" <<
            "----------------------------------------------------------------------------------------------------------------\n";

        std::cout << "|" << listaDati[pos_ID].idPersona << "\t";
        if (listaDati[pos_ID].idPersona < 1000000) 
            std::cout << "\t";  // Se l'id persona non supera il milione stampo un altro tab (causa formattazione della tabella)
        std::cout << "|" << listaDati[pos_ID].idAuto << "\t\t";
        std::cout << "|" << listaDati[pos_ID].targa_Auto << "\t";
        std::cout << "|" << listaDati[pos_ID].costo_km_auto << "\t\t";
        std::cout << "|" << listaDati[pos_ID].km_rimborso << "\t";
        if (listaDati[pos_ID].km_rimborso < 1000000)
            std::cout << "\t";  // Se l'id auto non supera il milione stampo un altro tab (causa formattazione della tabella)
        std::cout << "|" << listaDati[pos_ID].MeseRimb << "\t";
        std::cout << "|" << listaDati[pos_ID].AnnoRimb << "\t";
        std::cout << "|" << listaDati[pos_ID].des_auto << "\t" << std::endl;
}

void mostra_per_IDPersona(std::vector<datiRimborso>& listaDati,const int pos_ID)    // funzione che mostra tutti i dati inerenti all'ID persona cercato
{
    std::vector<datiRimborso>ID_cercato;                                            //creo un vector temporaneo per salvare tutti i dati appartenenti all'IDPersona cercato
    for(int i=0;i<listaDati.size();i++)
    {
        if(listaDati[i].idPersona==listaDati[pos_ID].idPersona)                     /*controllo per in quali posizioni i si trovano tutti i dati appartenenti alla persona cercata
                                                                                    che si trova in posizione pos_ID e li salvo nel vector temporane*/
        {
            datiRimborso save_ID_temp=listaDati[i];
            ID_cercato.push_back(save_ID_temp);
        }
    }

    std::cout << "\n|ID PERSONA\t|ID AUTO\t|TARGA\t\t|COSTO(Euro/Km)\t|KM AUTO\t|MESE\t|ANNO\t|DESCRIZIONE AUTO\n" <<
            "----------------------------------------------------------------------------------------------------------------\n";
    for(int i=0;i<ID_cercato.size();i++)        //con il vector temporaneo mostro a video all'utente tutti i dati della persona
    {
        std::cout << "|" << ID_cercato[i].idPersona<<"\t";
        if (ID_cercato[i].idPersona < 1000000)
            std::cout << "\t"; // Se l'id persona non supera il milione stampo un altro tab (causa formattazione della tabella)
        std::cout << "|" << ID_cercato[i].idAuto << "\t\t";
        std::cout << "|" << ID_cercato[i].targa_Auto << "\t";
        std::cout << "|" << ID_cercato[i].costo_km_auto << "\t\t";
        std::cout << "|" << ID_cercato[i].km_rimborso << "\t";
        if (ID_cercato[i].km_rimborso < 1000000)
            std::cout << "\t";
        std::cout << "|" << ID_cercato[i].MeseRimb << "\t";
        std::cout << "|" << ID_cercato[i].AnnoRimb << "\t";
        std::cout << "|" << ID_cercato[i].des_auto << "\t" << std::endl;
    }

}