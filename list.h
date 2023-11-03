#ifndef LIST_H
#define LIST_H
#include "list.c"
void insertClient(struct listClient **tete,struct Tclient client);
void insertResv(struct listResv **tete,struct Treservation resv);
struct Tclient* getClient(struct listClient *tete,int id);
struct Treservation* getResv(struct listResv *tete,int id);
int deleteClient(struct listClient **tete,int id);
int deleteResv(struct listResv **tete,int id);
#endif
