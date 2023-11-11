#include "listClient.h"
#include "file.h"
#include "file.h"
#include "file.h"
#include <stdio.h>
#include "listResv.h"

#include "print.h"
#include "resv.h"
#include "client.h"
#include "dataToObject.h"
#include "struct.h"
#include "pList.h"


#include <string.h>//to be removed
int main(){

    // struct TclientBlocPhys bloc[3];
    // bloc[0].taille=3;
    // bloc[0].clientTab[0].id=30;
    // strcpy(bloc[0].clientTab[0].nom,"a");
    // strcpy(bloc[0].clientTab[0].prenom,"a");
    // strcpy(bloc[0].clientTab[0].adresse,"a");
    //
    // bloc[0].clientTab[1].id=31;
    // strcpy(bloc[0].clientTab[1].nom,"b");
    // strcpy(bloc[0].clientTab[1].prenom,"b");
    // strcpy(bloc[0].clientTab[1].adresse,"b");
    //
    // bloc[0].clientTab[2].id=32;
    // strcpy(bloc[0].clientTab[2].nom,"c");
    // strcpy(bloc[0].clientTab[2].prenom,"c");
    // strcpy(bloc[0].clientTab[2].adresse,"c");
    //
    // bloc[1].taille=3;
    // bloc[1].clientTab[0].id=33;
    // strcpy(bloc[1].clientTab[0].nom,"a");
    // strcpy(bloc[1].clientTab[0].prenom,"a");
    // strcpy(bloc[1].clientTab[0].adresse,"a");
    //
    // bloc[1].clientTab[1].id=34;
    // strcpy(bloc[1].clientTab[1].nom,"b");
    // strcpy(bloc[1].clientTab[1].prenom,"b");
    // strcpy(bloc[1].clientTab[1].adresse,"b");
    //
    // bloc[1].clientTab[2].id=35;
    // strcpy(bloc[1].clientTab[2].nom,"c");
    // strcpy(bloc[1].clientTab[2].prenom,"c");
    // strcpy(bloc[1].clientTab[2].adresse,"c");
    //
    // bloc[2].taille=3;
    // bloc[2].clientTab[0].id=36;
    // strcpy(bloc[2].clientTab[0].nom,"a");
    // strcpy(bloc[2].clientTab[0].prenom,"a");
    // strcpy(bloc[2].clientTab[0].adresse,"a");
    //
    // bloc[2].clientTab[1].id=37;
    // strcpy(bloc[2].clientTab[1].nom,"b");
    // strcpy(bloc[2].clientTab[1].prenom,"b");
    // strcpy(bloc[2].clientTab[1].adresse,"b");
    //
    // bloc[2].clientTab[2].id=38;
    // strcpy(bloc[2].clientTab[2].nom,"c");
    // strcpy(bloc[2].clientTab[2].prenom,"c");
    // strcpy(bloc[2].clientTab[2].adresse,"c");

    struct LOF file=openFile("client.txt",'a');
    if(!file.pt){
        printf("oh no");
        return 1;
    }
    int id,a=1;
    char i;
    char nom[10],prenom[10],adresse[20];
    struct listClient *tete ;
    tete =NULL;
    while(a){
        printf("pick an option:\n");
        printf("  1. insert\n");
        printf("  2. delete\n");
        printf("  3. search\n");
        printf("  4. print\n");
        printf("  5. quit\n");
        scanf("%c",&i);
        switch (i){
            case '1':
                printf("enter id:");
                scanf("%d",&id);
                printf("enter nom:");
                scanf("%s",nom);
                printf("enter prenom:");
                scanf("%s",prenom);
                printf("enter adress:");
                scanf("%s",adresse);
                struct Tclient client = creerClient(nom,prenom,adresse,id);
                insertOrdClient(&tete,client);
                break;
            case '2':
                printf("enter the id:");
                scanf("%d",&id);
                if(deleteClient(&tete,id)){
                    printf("there was no client with that id\n");
                }else{
                    printf("the client %d was deleted",id);
                }
                break;
            case '3':
                printf("enter the id:");
                scanf("%d",&id);
                struct Tclient* clientPt=getClient(tete,id);
                if(!clientPt){
                    printf("theresn't one\n");
                    break;
                }
                printClient(*clientPt);
                break;
            case '4':
                printListClient(tete);
                break;
            case '5':
                a=0;
        }
    }
    saveListClient(&file,tete);
    printFileClient(file);
    closeFile(file);
    return 0;

}
