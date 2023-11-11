#ifndef LIST_H
#define LIST_H
#include "struct.h"
void insertOrdClient(struct listClient **tete,struct Tclient client);//tested
void insertOrdResv(struct listResv **tete,struct Treservation resv);
struct Treservation* getResv(struct listResv *tete,int id);
int deleteResv(struct listResv **tete,int id);
void freeListResv(struct listResv *list);
#endif
