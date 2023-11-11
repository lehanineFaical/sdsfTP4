#include "struct.h"
#include <stdlib.h>
void insertResv(struct listResv **tete,struct Treservation resv){
    struct listResv *tmp,*e=malloc(sizeof(struct listResv));
    e->resv=resv;
    e->svt=*tete;
    *tete=e;
}
void insertOrdResv(struct listResv **tete,struct Treservation resv){
    struct listResv *tmp,*e=malloc(sizeof(struct listResv));
    e->resv=resv;
    if(!*tete){
        *tete=e;
        (*tete)->svt=NULL;
        return;
    }
    if((*tete)->resv.id>e->resv.id){
        e->svt=*tete;
        *tete=e;
        return;
    }
    tmp=*tete;
    while(tmp->svt){
        if(tmp->svt->resv.id<e->resv.id) break;
        tmp=tmp->svt;
    }
    e->svt=tmp->svt;
}
struct Treservation* getResv(struct listResv *tete,int id){
    if(!tete) return NULL;
    while(tete->svt){
        if(tete->resv.id==id) return &tete->resv;
        tete=tete->svt;
    }
    return NULL;
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
void freeListResv(struct listResv *list){
    struct listResv *e;
    while(list){
        e=list;
        list=list->svt;
        free(e);
    }
}
