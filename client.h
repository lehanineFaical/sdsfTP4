#ifndef CLIENT_C
#define CLIENT_C
#include "struct.h"
struct listClient* loadAllBlocsClient(struct LOF file);//tested
struct listClient* loadBlocClient(struct LOF file,int *i);//tested
void saveListClient(struct LOF *file,struct listClient* input);//tested
void saveBlocsClient(struct LOF *file,struct TclientBlocPhys input[],int n,int insert,int svt);//tested
void saveBlocClient(struct LOF *file,struct TclientBlocPhys bloc,int *i);//tested
struct Tclient* fGetClient(struct LOF file,int id);//tested
int listToBlocClient(struct listClient** list,struct TclientBlocPhys blocTab[]);//tested

int fDeleteClient(struct LOF *file,int id);//tested
#endif
