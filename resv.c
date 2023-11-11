#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "resv.h"
#include "file.c"
struct TresvPhys resvToPhys(struct Treservation input){
    struct TresvPhys output;
    output.cId=input.client.id;
    output.arvDate=input.arvDate;
    output.depDate=input.depDate;
    output.roomNbr=input.roomNbr;
    output.id=input.id;
    return output;
}
struct Tresarvation physToResv(struct TresvPhys input){
    struct Tresarvation
    output.client=fGetClient(input.cId);
    output.arvDate=input.arvDate;
    output.depDate=input.depDate;
    output.roomNbr=input.roomNbr;
    output.id=input.id;
    return output;
}

struct listResv* loadAllBlocsResv(struct LOF file){//note: maybe should be deleted. should work
    int i,j;
    struct TresvBlocPhys tab[file.head.nbrBlocs];
    fseek(file.pt,0,sizeof(struct header));
    fread(&tab,sizeof(struct TresvBlocPhys),file.head.nbrBlocs,file.pt);
    struct listResv *tmp,*e,*tete=NULL;
    for(i=0;i<file.head.nbrBlocs;i++){
        for(j=0;j<tab[i].taille;j++){
            e=(struct listResv*)malloc(sizeof(struct listResv));
            e->resv=physToResv(tab[i].resvTab[j]);
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
struct listResv* loadBlocResv(struct LOF file,int *i){//should work
   int j;
   struct TresvBlocPhys bloc;
   fseek(file.pt,sizeof(struct header)+(*i)*sizeof(struct TresvBlocPhys),SEEK_SET);
   fread(&bloc,sizeof(struct TresvBlocPhys),1,file.pt);
   *i=bloc.svt;
   struct listResv *tmp,*e,*tete=NULL;
   for(j=0;j<bloc.taille;j++){
       e=(struct listResv*)malloc(sizeof(struct listResv));
        e->resv =physToResv(bloc.resvTab[j]);
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
void saveListResv(struct LOF *file,struct listResv* input){
    struct listResv *bloc,*e,*tmp;
    struct TresvBlocPhys output,blocTab[10];
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
        while((tmp->resv.id>input->resv.id)||(i==file->head.nbrBlocs-1)){
            flag=1;
            insertOrdResv(&bloc,input->resv);
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
void saveBlocsResv(struct LOF *file,struct TresvBlocPhys input[],int n,int insert,int svt){
    int i;
    input[n-1].svt=svt;
    for(i=n-1;i>0;i--){
        input[i-1].svt=-1;
        saveBloc(file,input[i],&input[i-1].svt);
    }
    saveBloc(file,input[0],&insert);
}
void saveBlocRevs(struct LOF *file,struct TclientBlocPhys bloc,int *i){
    if(!file->head.nbrBlocs){
        *i=file->head.nbrBlocs++;
        file->head.firstIndex=*i;
    }
    if(*i<0) *i=file->head.nbrBlocs++;
    fseek(file->pt,sizeof(struct header)+(*i)*sizeof(struct TclientBlocPhys),SEEK_SET);
    fwrite(&bloc,sizeof(struct TclientBlocPhys),1,file->pt);
    file->head.tailleBloc[*i]=bloc.taille;
}
struct Tresv* fGetResv(struct LOF file,int id){
    struct Treservation *resv;
    struct listResv *bloc,*tmp;
    int i,svt=file.head.firstIndex;
    for(i=0;i<file.head.nbrBlocs;i++){//loops throught all of the blocks or until the list is umpty
        bloc=loadBloc(file,&svt);
        tmp=bloc;
        if(bloc->resv.id>id) return NULL;
        resv=getResv(bloc,id);
        if(resv) return resv;
    }
    return NULL;
}
int listToBlocResv(struct listResv** list,struct TresvBlocPhys blocTab[]){
    int i=0,j=0;
    struct listResv *e;
    while(*list){
        blocTab[i].resvTab[j++]=resvToPhys((*list)->resv);
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
int fDeleteResv(struct LOF *file,int id){
    struct TresvBlocPhys blocPhysTab[3];
    struct listResv *bloc;
    int i,cur,svt=file->head.firstIndex;
    for(i=0;i<file->head.nbrBlocs;i++){//loops throught all of the blocks or until the l ist is umpty
        cur=svt;
        bloc=loadBloc(*file,&svt);
        if(bloc->resv.id>id) return 1;
        if(!deleteResv(&bloc,id)){
            listToBloc(&bloc,blocPhysTab);
            blocPhysTab[0].svt=svt;
            saveBloc(file,blocPhysTab[0],&cur);
            return 0;
        }
    }
    return 1;
}
