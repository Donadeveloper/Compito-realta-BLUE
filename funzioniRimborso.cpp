#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <locale>

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
void inserimentoDati(std::vector<datiRimborso>& listaDati, bool &modDaSalvare);
int ricercaIdAuto(std::vector<datiRimborso> listaDati, const int idRicercato);
int ricercaIdPersona(std::vector<datiRimborso> listaDati, const int idRicercato);
void mostramenu(std::vector<datiRimborso> listaDati, std::fstream &fileDati);
void mostraDati(std::vector<datiRimborso> listaDati);
void mostra_per_IDAuto(std::vector<datiRimborso>& listaDati,const int pos_ID);
void mostra_per_IDPersona(std::vector<datiRimborso>& listaDati,const int pos_ID);
void salvaDati(std::vector<datiRimborso> &listaDati, std::fstream &fileDati);
void cancellaRimborso(std::vector<datiRimborso>& listaDati, const int idDaEliminare, bool &modDaSalvare);

void mostramenu(std::vector<datiRimborso> listaDati, std::fstream &fileDati)
{
    unsigned int scelta;
    unsigned int IDcercato;
    unsigned int IDtrovato;
    bool modDaSalvare = false;
    bool fineProgramma = false;
    while (true) {

        std::cout << "\n\n\t\t------RIMBORSO AUTO------\n";
        std::cout << "\n\tBenvenuto nella gestione dei rimborsi auto cosa vuoi fare?:\n";
        std::cout << "\t [1]  Inserire un rimborso\n";
        std::cout << "\t [2]  Ricercare una vettura presente nel database dei rimborsi\n";
        std::cout << "\t [3]  Ricercare una persona presente nel database dei rimborsi\n";
        std::cout << "\t [4]  Rimuovere un rimborso presente nel database dei rimborsi\n";
        std::cout << "\t [5]  Mostrare i rimborsi presenti nel database dei rimborsi\n";
        std::cout << "\t [6]  Salvataggio modifiche";
        if (modDaSalvare)
            std::cout << "  [RILEVATE MODIFICHE NON SALVATE]";
        std::cout << "\n\t [7]  ESC\n";

        do {
            std::cout << "\n n scelta: ";
            std::cin >> scelta;
        } while (scelta < 1 || scelta > 7);

        switch(scelta)
        {
        case 1:
            inserimentoDati(listaDati, modDaSalvare);
            break;
        case 2:
            std::cout << "Inserisci l'ID dell'auto che vuoi cercare:  ";
            std::cin >> IDcercato;
            IDtrovato = ricercaIdAuto(listaDati, IDcercato);
            if (IDtrovato!=-1)
                mostra_per_IDAuto(listaDati,IDtrovato);
            else
                std::cout << "[!] ID non presente\n";
            break;
        case 3:
            std::cout << "Inserisci l'ID della persona che vuoi cercare:  ";
            std::cin >> IDcercato;
            IDtrovato = ricercaIdPersona(listaDati, IDcercato);
            if (IDtrovato!=-1)
                mostra_per_IDPersona(listaDati,IDtrovato);
            else
                std::cout << "[!] ID non presente\n";
            break;
        case 4:
            std::cout << "Inserisci l'ID dell'auto di cui vuoi eliminare il rimborso:  ";
            std::cin >> IDcercato;
            IDtrovato = ricercaIdAuto(listaDati, IDcercato);
            if (IDtrovato!=-1) 
                cancellaRimborso(listaDati, IDtrovato, modDaSalvare);
            else
                std::cout << "[!] ID non presente\n";
            break;
        case 5:
            mostraDati(listaDati);
            break;
        case 6:
            fileDati.close();
            fileDati.open("DATIRIMBORSO.csv", std::fstream::out);
            salvaDati(listaDati, fileDati);
            modDaSalvare = false;
            fileDati.close();
            fileDati.open("DATIRIMBORSO.csv", std::fstream::in);
            break;
        case 7:
            return;
            fineProgramma = true;
        }
        system("pause");
        system("cls");
        if (fineProgramma) {
            break;
        }
    }
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

void salvaDati(std::vector<datiRimborso> &listaDati, std::fstream &fileDati) {
    // Questa funzione salva i dati presenti nel vettore listaDati nel file di database

    int vectLength = listaDati.size();
    for (int i = 0; i < vectLength; i++) {
        fileDati << listaDati[i].idPersona << ";";
        fileDati << listaDati[i].idAuto << ";";
        fileDati << listaDati[i].targa_Auto << ";";
        fileDati << listaDati[i].costo_km_auto << ";";
        fileDati << listaDati[i].AnnoRimb << ";";
        fileDati << listaDati[i].MeseRimb << ";";
        fileDati << listaDati[i].km_rimborso << ";";
        fileDati << listaDati[i].des_auto << "\n";
    }
}

void inserimentoDati(std::vector<datiRimborso>& listaDati, bool &modDaSalvare) {
    /* Questa funzione chiede all'utente tutti i dati di una nuova struct da inserire nei rimborsi, e poi la inserisce nel vettore ordinatamente
    Poichè il campo idAuto deve essere un numero che identifica univocamente un'auto, nel caso in cui l'utente ne inserisca uno già
    esistente, egli può decidere se eliminare l'attuale inserimento o sovrascrivere il vecchio rimborso. Inoltre, la funzione modifica la variabile
    modDaSalvare, in maniera che il prossimo menu avvisi l'utente che ci sono delle modifiche non salvate nel file */

    setlocale(LC_ALL, "");
    const int CARATTERI_TARGA = 7;
    datiRimborso datiInseriti;
    int nRimborsi = listaDati.size();
    int buffer_int;
    std::string buffer_string;
    double buffer_double;
    char buffer_char;
    int indiceAutoPresente = -1;
    bool sovrascrittura = false;
    modDaSalvare = false;

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
            std::cout << "Verrà sovrascritto il rimborso dell'auto di ID " << buffer_int << ". Targa e descrizione non verranno modificati\n\n";
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
            std::cout << "Descrizione auto (generalmente è il produttore): ";
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
    modDaSalvare = true;
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
    std::string tempStr;
    while (!inputFile.eof())
    {
        getline(inputFile, tempStr, ';');
        /* Dopo aver preso i valori dell'ultima riga, il ciclo si ripete un'ultima volta. Controllo se ho raggiunto l'EOF dopo aver preso il primo dato, 
        in modo da interrompermi se mi trovo in quel caso, così evito di avere un rimborso "sporco" come ultimo rimborso nella listaDati */
        if (inputFile.eof())
            break;
        temporaneo.idPersona = stringToInt(tempStr);

        getline(inputFile, tempStr, ';');
        temporaneo.idAuto = stringToInt(tempStr);

        getline(inputFile, temporaneo.targa_Auto, ';');

        getline(inputFile, tempStr, ';');
        temporaneo.costo_km_auto = stringToDouble(tempStr);

        getline(inputFile, tempStr, ';');
        temporaneo.AnnoRimb = stringToInt(tempStr);

        getline(inputFile, tempStr, ';');
        temporaneo.MeseRimb = stringToInt(tempStr);

        getline(inputFile, tempStr, ';');
        temporaneo.km_rimborso = stringToDouble(tempStr);

        getline(inputFile, temporaneo.des_auto);

        listaDati.push_back(temporaneo);
    }

    ordinamentoDati(listaDati);

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

int ricercaIdAuto(std::vector<datiRimborso> listaDati, const int idRicercato) //ricerca secondo IDAuto
{
    int vectSize;

    vectSize = listaDati.size();
    for (int i = 0; i < vectSize; i++) {
        if (listaDati[i].idAuto == idRicercato)
            return i;
    }
    std::cout << "[!] ID non presente\n";
    return -1; 
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

void cancellaRimborso(std::vector<datiRimborso> &listaDati, const int idDaEliminare, bool &modDaSalvare) {
    /* Questa funzione elimina dal vettore listaDati il rimborso che ha come idAuto idDaEliminare. Modifica, inoltre,
    la variabile modDaSalvare, in maniera che il prossimo menu avvisi l'utente che ci sono delle modifiche non salvate nel file */
    int vectSize;
    
    vectSize = listaDati.size();
    for (int i = idDaEliminare; i < vectSize; i++) {
        listaDati[i] = listaDati[i+1];
    }
    listaDati.pop_back();
    modDaSalvare = true;
}