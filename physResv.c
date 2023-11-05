#include "struct.h"
struct Treservation physToresv(struct TresvPhys resvPhys){
    struct Treservation resv;
    resv.client=getClient(resvPhys.cId);
    resv.depDate=resvPhys.depDate;
    resv.arvDate=resvPhys.arvDate;
    resv.roomNbr=resvPhys.roomNbr;
    return resv;
}
struct TresvPhys resvToPhys(struct Treservation resv){
    struct TresvPhys resvPhys;
    resvPhys.cId=resv.client.id;
    resvPhys.arvDate=resv.arvDate;
    resvPhys.depDate=resv.depDate;
    resvPhys.roomNbr=resv.roomNbr;
    resvPhys.id=resv.id;
    return resvPhys;

}