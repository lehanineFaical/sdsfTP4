#include <stdio.h>
#ifndef STRUCT_H
#define STRUCT_H
#define TailleBloc 4
struct Tdate{
    int DD,MM,YY;
};
struct Tclient{
    char nom[10],prenom[10],adresse[20];
    int id;
};
struct Treservation{   
    struct Tclient client;
    struct Tdate arvDate;
    struct Tdate depDate;
    int roomNbr,id;
};
struct TresvPhys{   
    int cId;
    struct Tdate arvDate;
    struct Tdate depDate;
    int roomNbr,id;
};
struct listClient{
    struct Tclient client;
    struct listClient* svt;
};
struct listResv{
    struct Treservation resv;
    struct listResv *svt;
};
struct header{
    int nbrBlocs,tailleBloc[10];

};
struct LOF{
    FILE* file;
    struct header head;
};
#endif
