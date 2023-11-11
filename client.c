#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "client.h"
#include "file.c"
struct listClient* loadAllBlocsClient(struct LOF file){//note: maybe should be deleted. should work
    int i,j;
    struct TclientBlocPhys tab[file.head.nbrBlocs];
    fseek(file.pt,0,sizeof(struct header));
    fread(&tab,sizeof(struct TclientBlocPhys),file.head.nbrBlocs,file.pt);
    struct listClient *tmp,*e,*tete=NULL;
    for(i=0;i<file.head.nbrBlocs;i++){
        for(j=0;j<tab[i].taille;j++){
            e=(struct listClient*)malloc(sizeof(struct listClient));
            e->client=tab[i].clientTab[j];
            e->svt=NULL;
            if(!tete){
                tete=e;
            }else{
                tmp=tete;
                while(tmp->svt) tmp=tmp->svt;
                tmp->svt=e;
            }
        }
    }
    return tete;
}
struct listClient* loadBlocClient(struct LOF file,int *i){//should work
   int j;
   struct TclientBlocPhys bloc;
   fseek(file.pt,sizeof(struct header)+(*i)*sizeof(struct TclientBlocPhys),SEEK_SET);
   fread(&bloc,sizeof(struct TclientBlocPhys),1,file.pt);
   *i=bloc.svt;
   struct listClient *tmp,*e,*tete=NULL;
   for(j=0;j<bloc.taille;j++){
       e=(struct listClient*)malloc(sizeof(struct listClient));
        e->client =bloc.clientTab[j];
        e->svt=NULL;
        if(!tete){
            tete=e;
        }else{
            tmp=tete;
            while(tmp->svt) tmp=tmp->svt;
            tmp->svt=e;
        }
   }
   return tete;
}
void saveListClient(struct LOF *file,struct listClient* input){
    struct listClient *bloc,*e,*tmp;
    struct TclientBlocPhys output,blocTab[10];
    int i,flag,n,cur,svt=file->head.firstIndex;
    if(!file->head.nbrBlocs){
        n=listToBloc(&input,blocTab);
        saveBlocs(file,blocTab,n,-1,-1);
    }
    for(i=0;i<file->head.nbrBlocs&&input;i++){//loops throught all of the blocks or until the list is umpty
        flag=0;
        cur=svt;
        bloc=loadBloc(*file,&svt);
        for(tmp=bloc;tmp->svt;tmp=tmp->svt);
        //checks if the element should be insterted in this block;
        while((tmp->client.id>input->client.id)||(i==file->head.nbrBlocs-1)){
            flag=1;
            insertOrdClient(&bloc,input->client);
            e=input;
            input=input->svt;
            free(e);
            if(!input) break;
        }
        //convetrs the new list to a block and saves it;
        if(flag){
            n=listToBloc(&bloc,blocTab);
            saveBlocs(file,blocTab,n,cur,svt);
        }
    }
}
void saveBlocsClient(struct LOF *file,struct TclientBlocPhys input[],int n,int insert,int svt){
    int i;
    input[n-1].svt=svt;
    for(i=n-1;i>0;i--){
        input[i-1].svt=-1;
        saveBloc(file,input[i],&input[i-1].svt);
    }
    saveBloc(file,input[0],&insert);
}
void saveBlocClient(struct LOF *file,struct TclientBlocPhys bloc,int *i){
    if(!file->head.nbrBlocs){
        *i=file->head.nbrBlocs++;
        file->head.firstIndex=*i;
    }
    if(*i<0) *i=file->head.nbrBlocs++;
    fseek(file->pt,sizeof(struct header)+(*i)*sizeof(struct TclientBlocPhys),SEEK_SET);
    fwrite(&bloc,sizeof(struct TclientBlocPhys),1,file->pt);
    file->head.tailleBloc[*i]=bloc.taille;
}
struct Tclient* fGetClient(struct LOF file,int id){
    struct Tclient *client;
    struct listClient *bloc,*tmp;
    int i,svt=file.head.firstIndex;
    for(i=0;i<file.head.nbrBlocs;i++){//loops throught all of the blocks or until the list is umpty
        bloc=loadBloc(file,&svt);
        tmp=bloc;
        if(bloc->client.id>id) return NULL;
        client=getClient(bloc,id);
        if(client) return client;
    }
    return NULL;
}
int listToBlocClient(struct listClient** list,struct TclientBlocPhys blocTab[]){
    int i=0,j=0;
    struct listClient *e;
    while(*list){
        blocTab[i].clientTab[j++]=(*list)->client;
        e=*list;
        *list=(*list)->svt;
        free(e);
        if(j>=TailleBloc){
            blocTab[i++].taille=TailleBloc;
            j=0;
        }
    }
    blocTab[i].taille=j;
    return i+1;
}
int fDeleteClient(struct LOF *file,int id){
    struct TclientBlocPhys blocPhysTab[3];
    struct listClient *bloc;
    int i,cur,svt=file->head.firstIndex;
    for(i=0;i<file->head.nbrBlocs;i++){//loops throught all of the blocks or until the l ist is umpty
        cur=svt;
        bloc=loadBloc(*file,&svt);
        if(bloc->client.id>id) return 1;
        if(!deleteClient(&bloc,id)){
            listToBloc(&bloc,blocPhysTab);
            blocPhysTab[0].svt=svt;
            saveBloc(file,blocPhysTab[0],&cur);
            return 0;
        }
    }
    return 1;
}
