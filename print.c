#include <stdio.h>
#include "struct.h"
#include "listClient.h"
#include "listResv.h"
#include "client.h"
#include "resv.h"
#include "pList.h"
void printHeader(struct header head){
    printf("nbr of blocs:%d\n",head.nbrBlocs);
    int i;
    for(i=0;i<head.nbrBlocs;i++){
        printf("\tbloc at the pos %dis has %d elements.\n",i,head.tailleBloc[i]);
    }
    printf("the first bloc is at pos%d\n",head.firstIndex);
}

void printFileClient(struct LOF file){
    struct listClient *list;
    printHeader(file.head);
    printf("\n\n\n");
    int i,svt=file.head.firstIndex;
    for(i=0;i<file.head.nbrBlocs;i++){
        printf("block Nbr %dis at pos%d:\n",i,svt);
        list=loadBlocClient(file,&svt);
        printListClient(list);
        freeListClient(list);
        printf("\n");
    }
}
void printFileResv(struct LOF file){
    struct listResv *list;
    printHeader(file.head);
    printf("\n\n\n");
    int i,svt=file.head.firstIndex;
    for(i=0;i<file.head.nbrBlocs;i++){
        printf("block Nbr %dis at pos%d:\n",i,svt);
        list=loadBlocResv(file,&svt);
        printListResv(list);
        freeListResv(list);
        printf("\n");
    }
}
