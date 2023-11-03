#ifndef STRUCT_H
#define STRUCT_H
struct Tdate{
    int DD,MM,YY;
};
struct Tclient{
    char nom[10],prenom[10],adresse[20];
    int id;
};
struct Treservation{   //id#client#roomNbr#data#date#
    struct Tclient client;
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
#endif
