#include "struct.h"
void printClient(struct Tclient client){
    printf("%d\t%s\t%s\t%s\n",client.id,client.nom,client.prenom,client.adresse);
}
void printResv(struct Treservation resv){
    printf("%d\t%d\t%d\t%s\t%s\t%s\t%d/%d/%d\t%d/%d/%d\n",
        resv.id,
        resv.roomNbr,
        resv.client.id,resv.client.nom,resv.client.prenom,resv.client.adresse,
        resv.arvDate.DD,resv.arvDate.MM,resv.arvDate.YY,
        resv.depDate.DD,resv.depDate.MM,resv.depDate.YY
           );
}
void printListClient(struct listClient *tete){
    if(tete){
        printf("id\tnom\tprenom\tadress\n");
        while(tete){
            printClient(tete->client);
            tete=tete->svt;
        }
    }else{
        printf("the list is empty");
    }
}
void printListResv(struct listResv *tete){
    if(tete){
        printf("id\troomNbr\tclient\tarvDate\tdepDate\n");
        while(tete->svt){
            printResv(tete->resv);
            tete=tete->svt;
        }
    }else{
        printf("the list is empty");
    }
}

