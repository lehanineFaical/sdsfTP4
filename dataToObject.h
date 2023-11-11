#ifndef DATATOOBJECT_H
#define DATATOOBJECT_H
#include "dataToObject.c"
struct Tclient creerClient(char nom[],char prenom[],char adresse[],int id);//done
struct Treservation creerResevation(int id,struct Tdate arvDate,struct Tdate depDate,int roomNbr,int clientId,struct LOF file);
struct Tdate creerDate(int DD,int MM,int YY);//done
#endif
