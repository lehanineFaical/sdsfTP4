#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "file.h"
struct LOF openFile(char* str,char opt){
    struct LOF file;
    switch (opt){
        case 'n':
            file.pt=fopen(str,"w+b");
            file.head=createHeader();
            break;
        case 'a':
            file.pt=fopen(str,"r+b");
            if(file.pt) fread(&file.head,sizeof(struct header),1,file.pt);
            break;
        default :
            file.pt=NULL;
    }
    return file;
}
struct header createHeader(){
    struct header head;
    head.nbrBlocs=0;
    head.firstIndex=-1;
    return head;
}
void closeFile(struct LOF file){
    fseek(file.pt,0,SEEK_SET);
    fwrite(&file.head,sizeof(struct header),1,file.pt);
    fclose(file.pt);
}
