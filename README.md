# Compito-realta-BLUE
Compito di realtà

1. Strutture dati:

I dati dei rimborsi vengono presi in input da un file .csv “input.txt” creato con Excel formattato in maniera tale da avere diverse righe: ogni riga contiene, separati da una virgola, i dati di ogni rimborso in ordine seguente: 

IdPersona,IdAuto,targa_auto,costo_km_auto,AnnoRimb,MeseRimb,km_rimborso, des_auto

Questi dati verranno presi da una struttura dati di tipo fstream impostata come “read”, per poi essere caricati da una funzione apposita in diverse struct (una per rimborso), che a loro volta verranno caricate in una variabile di tipo vector dalla stessa funzione.



2. Funzioni:

1) void caricamentoDati (vector<struct> &listaDati, fstream inputFile)

La funzione caricamentoDati prende dal file della stream inputFile i dati necessari, poi li carica nel vector listaDati passato come riferimento.


2) void ordinaDati (vector<struct> &listaDati)

La funzione ordinaDati ordina in ordine crescente secondo il campo idPersona le struct contenute nel vector listaDati passato come riferimento. Se una persona possiede più macchine, le struct verranno ordinate nella memoria in base al campo “targa_auto”.


3) void inserimentoRimborso (vector<struct> &listaDati)

La funzione inserimentoRimborso chiede all’utente i dati sul rimborso che egli desidera aggiungere ad una persona già esistente oppure no, per poi caricarli in una struct che verrà poi caricata nel vector. Successivamente verrà chiamata la funzione “ordinaDati” per ordinare il vector.


4) void ricercaIdAuto (vector<struct> &listaDati)

La funzione ricercaIdAuto chiede all’utente l’id dell’auto che desidera cercare, poi lo cerca nel vector e stampa a video i dati relativi.


5) void ricercaIdPersona (vector<struct> &listaDati)

La funzione ricercaIdPersona chiede all’utente l’id della persona che desidera cercare, poi lo cerca nel vector e stampa a video i dati relativi.


6) void cancellaRimborso (vector<struct> &listaDati)

la funzione cancellaRimborso chiede all’utente il rimborso da eliminare, lo cerca nel vector, lo sposta alla fine di quest’ultimo e poi lo rimuove con la funzione pop_back().


7) void mostraRimborsi (vector<struct> &listaDati)

La funzione mostraRimborsi stampa a video, in una tabella, tutti i dati contenuti nel vector


8) void caricaDati (vector<struct> &listaDati, fstream inputFile)

La funzione caricaDati prende i dati dal vector e li carica nel file .csv aperto dalla fstream.



Tutte le funzioni sono dichiarate nel file .h che verrà incluso nel file cpp principale del programma.
