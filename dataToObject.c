#include "struct.h"
#include <string.h>
struct Tclient creerClient(char nom[],char prenom[],char adresse[],int id){
    struct Tclient client;
    strcpy(client.nom,nom);
    strcpy(client.prenom,prenom);
    strcpy(client.adresse,adresse);
    client.id=id;
    return client;
}
/*struct Treservation creerResevation(int id,struct Tdate arvDate,struct Tdate depDate,int roomNbr,int clientId){
    struct Treservation resv;
    resv.client=getClient(clientId);
    resv.id=id;
    resv.arvDate=arvDate;
    resv.depDate=depDate;
    resv.roomNbr=roomNbr;
    return resv;
}*/
struct Tdate creerDate(int DD,int MM,int YY){
    struct Tdate date;
    date.DD=DD;
    date.MM=MM;
    date.YY=YY;
    return date;
}
