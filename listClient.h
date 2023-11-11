#ifndef LIST_H
#define LIST_H
#include "struct.h"
void insertClient(struct listClient **tete,struct Tclient client);
void insertOrdClient(struct listClient **tete,struct Tclient client);
struct Tclient* getClient(struct listClient *tete,int id);
int deleteClient(struct listClient **tete,int id);
void freeListClient(struct listClient *list);
#endif
