#include<stdio.h>
#include "list.h"
#include "dataToObject.h"
#include "struct.h"
#include "pList.h"
int main(){
    int id;
    char i;
    char nom[10],prenom[10],adresse[20];
    struct listClient *tete ;
    tete =NULL;
    while(1){
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
                insertClient(&tete,client);
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
                return 0;
        }
    }
}
