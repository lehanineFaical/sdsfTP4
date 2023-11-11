#include "struct.h"
#include <stdlib.h>
void insertClient(struct listClient **tete,struct Tclient client){
    struct listClient *tmp,*e=malloc(sizeof(struct listClient));
    e->client=client;
    e->svt=*tete;
    *tete=e;
}
void insertOrdClient(struct listClient **tete,struct Tclient client){
    struct listClient *tmp,*e=(struct listClient *)malloc(sizeof(struct listClient));
    e->client=client;
    if(!*tete){
        *tete=e;
        (*tete)->svt=NULL;
        return;
    }
    if((*tete)->client.id>e->client.id){
        e->svt=*tete;
        *tete=e;
        return;
    }
    tmp=*tete;
    while(tmp->svt){
        if(tmp->svt->client.id>e->client.id) break;
        tmp=tmp->svt;
    }
    e->svt=tmp->svt;
    tmp->svt=e;
}
struct Tclient* getClient(struct listClient *tete,int id){
    if(!tete) return NULL;
    while(tete->svt){
        if(tete->client.id==id) return &tete->client;
        tete=tete->svt;
    }
    if(tete->client.id==id) return &tete->client;
    return NULL;

}
void freeListClient(struct listClient *list){
    struct listClient *e;
    while(list){
        e=list;
        list=list->svt;
        free(e);
    }
}
