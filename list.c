#include "struct.h"
#include <stdlib.h>
void insertClient(struct listClient **tete,struct Tclient client){
    struct listClient *tmp,*e=malloc(sizeof(struct listClient));
    e->client =client;
    e->svt=NULL;
    if(!*tete){
        *tete=e;
        return;
    }
    tmp=*tete;
    while(tmp->svt) tmp=tmp->svt;
    tmp->svt=e;
}
void insertResv(struct listResv **tete,struct Treservation resv){
    struct listResv *tmp,*e=malloc(sizeof(struct listResv));
    e->resv =resv;
    e->svt=NULL;
    if(!*tete) *tete=e;
    tmp=*tete;
    while(tmp->svt) tmp=tmp->svt;
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

struct Treservation* getResv(struct listResv *tete,int id){
    if(!tete) return NULL;
    while(tete->svt){
        if(tete->resv.id==id) return &tete->resv;
        tete=tete->svt;
    }
    return NULL;
}

int deleteClient(struct listClient **tete,int id){
    struct listClient *tmp,*e;
    if(!*tete) return 1;
    if((*tete)->client.id==id){
        e=*tete;
        *tete=(*tete)->svt;
        free(e);
        return 0;
    }
    tmp=*tete;
    while(tmp->svt){
        if(tmp->svt->client.id==id){
            e=tmp->svt;
            tmp->svt=tmp->svt->svt;
            free(e);
            return 0;
        }
        tmp=tmp->svt;
    }
    return 1;
}

int deleteResv(struct listResv **tete,int id){
    struct listResv *tmp,*e;
    if(!*tete) return 1;
    if((*tete)->resv.id==id){
        e=*tete;
        *tete=(*tete)->svt;
        free(e);
        return 0;
    }
    tmp=*tete;
    while(tmp->svt){
        if(tmp->svt->resv.id==id){
            e=tmp->svt;
            tmp->svt=tmp->svt->svt;
            free(e);
            return 0;
        }
        tmp=tmp->svt;
    }
    return 1;
}
