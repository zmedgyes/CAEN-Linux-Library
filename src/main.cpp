#include <cstdio>

#include "SerialDevice.h"
#include "RFIDDevice.h"
#include "RFIDMessage.h"

#include "owasys.h"

using namespace std;

int main()
{
    SerialDevice serial("/dev/ttyO1", B115200, 0);
    RFIDDevice rfid(&serial);

    unsigned char Source_0[9] = {0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5F, 0x30, 0x00}; //Source_0\0
    unsigned int protocol     = 0x00000003;

    unsigned int powerInitial = 199;
    unsigned int powerMiddle  = 80;
    unsigned int powerTesting = 19;

    /*double gain = 8.0;
    double loss = 1.5;
    double ERPPower = 2000.0;*/

    // Set Protocol
    printf("Set Protocol\n");
    rfid.setProtocol(protocol)->print();
    printf("SET PROTOCOL COMPLETE\n");
    getc(stdin);

    // Get Power
    printf("Get Power\n");
    rfid.getPower()->print();
    printf("GET POWER COMPLETE\n");
    getc(stdin);

    // Set Power
    printf("Set Power\n");
    rfid.setPower(powerMiddle)->print();
    printf("SET POWER COMPLETE\n");
    getc(stdin);

    // Get Power
    printf("Get Power\n");
    rfid.getPower()->print();
    printf("GET POWER COMPLETE\n");
    getc(stdin);

    // antenna status
    printf("Get Antenna Status\n");
    rfid.getAntennaStatus(Source_0, 9)->print();
    printf("GET ANTENNA STATUS COMPLETE\n");
    getc(stdin);

    printf("START INVENTORY\n");

    // Inventory
    printf("\n");
    vector<unique_ptr<RFID>> founds;
    for(;;) {
        founds.clear();
        printf("Inventory\n");

        int k=0;

        rfid.inventory(Source_0, 9, nullptr, 0,0,0x0011)->getRFIDs(&founds); //with RSSI and TID

        for (auto &p_el : founds)
        {
            printf("%s \n", RFIDDevice::parseRFID(p_el.get()));
            k++;
        }
        printf("\n");

        sleep(5);
    }

    printf("\n");

    return 0;
}

