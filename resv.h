#ifndef RESV_C
#define RESV_C
#include "struct.h"
struct listResv* loadAllBlocsResv(struct LOF file);//tested
struct listResv* loadBlocResv(struct LOF file,int *i);//tested
void saveListResv(struct LOF *file,struct listResv* input);//tested
void saveBlocsResv(struct LOF *file,struct TresvBlocPhys input[],int n,int insert,int svt);//tested
void saveBlocResv(struct LOF *file,struct TresvBlocPhys bloc,int *i);//tested
struct Tclient* fGetResv(struct LOF file,int id);//tested
int listToBlocResv(struct listClient** list,struct TresvBlocPhys blocTab[]);//tested

int fDeleteResv(struct LOF *file,int id);//tested
struct TresvPhys resvToPhys(struct Treservation input);
struct Tresarvation physToResv(struct TresvPhys input);
#endif
