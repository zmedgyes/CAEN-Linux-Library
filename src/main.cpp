#include <cstdio>

#include "SerialDevice.h"
#include "RFIDDevice.h"
#include "RFIDMessage.h"

#include <chrono>

using namespace std;

int main()
{
    SerialDevice serial("/dev/ttyO1", B115200, 0);
    RFIDDevice rfid(&serial);

    //unsigned char Source_0[9] = {0x53, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x5F, 0x30, 0x00}; //Source_0\0
    string source("Source_0");
    unsigned int protocol     = 0x00000003;

    //these values are for a Proton R4320P Reader
    unsigned int powerMax = 1400;
    unsigned int powerDefault = 800;
    unsigned int powerMin = 14;

    unsigned int powerCurrent;
    unsigned int protocolCurrent;

    /*double gain = 8.0;
    double loss = 1.5;
    double ERPPower = 2000.0;*/

    RFIDMessage msgIn;

    //Get Protocol
    printf("GET PROTOCOL\n");
    rfid.getProtocol(&msgIn);
    msgIn.print();
    msgIn.getProtocol(&protocolCurrent);
    printf("Current protocol: %d\n", protocolCurrent);
    printf("GET PROTOCOL COMPLETE\n");
    getc(stdin);

    //Set Protocol
    printf("SET PROTOCOL\n");
    rfid.setProtocol(&msgIn, protocol);
    msgIn.print();
    printf("SET PROTOCOL COMPLETE\n");
    getc(stdin);

    //Set Q
    printf("SET Q\n");
    rfid.setSourceQ(&msgIn, &source, RFIDSourceConfigCodes::Q_3);
    msgIn.print();
    printf("SET Q COMPLETE\n");
    getc(stdin);

    //Set Session
    printf("SET SESSION\n");
    rfid.setSourceSession(&msgIn, &source, RFIDSourceConfigCodes::SESSION_0);
    msgIn.print();
    printf("SET SESSION COMPLETE\n");
    getc(stdin);

    //Get Power
    printf("GET POWER\n");
    rfid.getPower(&msgIn);
    msgIn.print();
    msgIn.getPower(&powerCurrent);
    printf("Current power: %d\n", powerCurrent);
    printf("GET POWER COMPLETE\n");
    getc(stdin);

    //Set Power
    printf("SET POWER\n");
    rfid.setPower(&msgIn, powerMin);
    msgIn.print();
    printf("SET POWER COMPLETE\n");
    getc(stdin);

    //Get Power
    printf("GET POWER\n");
    rfid.getPower(&msgIn);
    msgIn.print();
    msgIn.getPower(&powerCurrent);
    printf("Current power: %d\n", powerCurrent);
    printf("GET POWER COMPLETE\n");
    getc(stdin);

    //Source status
    printf("GET SOURCE STATUS\n");
    rfid.getSourceStatus(&msgIn, &source);
    msgIn.print();
    printf("GET SOURCE STATUS COMPLETE\n");
    getc(stdin);

    printf("START INVENTORY\n");

    //Inventory
    //NOTE: the first couple of inventory calls could be as slow as ~10sec. Be patient.
    printf("\n");
    vector<RFID> founds;
    string mask;
    for(;;) {
        founds.clear();
        printf("INVENTORY\n");

        int k=0;
        auto start = std::chrono::high_resolution_clock::now();
        rfid.inventory(&msgIn, &source, &mask, 0, 0x0011); //with RSSI and TID
        auto stop = std::chrono::high_resolution_clock::now();

        msgIn.getRFIDs(&founds);

        for (RFID& rfid : founds)
        {
            rfid.print();
            k++;
        }
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        printf("Tags found: %d , runtime: %lld ms\n", k, duration.count());

        sleep(1);
    }

    return 0;
}

