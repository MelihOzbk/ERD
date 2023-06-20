#ifndef ERD_H
#define ERD_H
#include <KumandaKontrol.h>
#include <OTA.h>

KumandaKontrol kumanda;
OTA ota;
class ERD
{
private:
    /* data */
public:
    void ERDSetup();
    void ERDLoop();
};



#endif