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

    string source("Source_0");
    string read_point("Ant0");

    //these values are for a Proton R4320P Reader
    unsigned int powerMax = 1400;
    unsigned int powerDefault = 800;
    unsigned int powerMin = 14;

    unsigned int powerCurrent;
    unsigned int protocolCurrent;
    bool currentInStatus;
    string info;

    /*double gain = 8.0;
    double loss = 1.5;
    double ERPPower = 2000.0;*/

    RFIDMessage msgIn;

    //Get reader info
    printf("GET READER INFO\n");
    rfid.getReaderInfo(&msgIn);
    msgIn.print();
    if (msgIn.success())
    {
        msgIn.getReaderInfo(&info);
        printf("Reader: %s\n", info.c_str());
    }
    printf("GET READER INFO COMPLETE\n");
    getc(stdin);

    //Get firmware version
    printf("GET FIRMWARE VERSION\n");
    rfid.getFirmwareVersion(&msgIn);
    msgIn.print();
    if (msgIn.success())
    {
        msgIn.getFirmwareVersion(&info);
        printf("Firmware: %s\n", info.c_str());
    }
    printf("GET FIRMWARE VERSION COMPLETE\n");
    getc(stdin);

    //Get Protocol
    printf("GET PROTOCOL\n");
    rfid.getProtocol(&msgIn);
    msgIn.print();
    if(msgIn.success())
    {
        msgIn.getProtocol(&protocolCurrent);
        printf("Current protocol: %d\n", protocolCurrent);
    }
    printf("GET PROTOCOL COMPLETE\n");
    getc(stdin);

    //Set Protocol
    printf("SET PROTOCOL\n");
    rfid.setProtocol(&msgIn, RFIDProtocolCodes::EPC_C1G2);
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
    rfid.setSourceSession(&msgIn, &source, RFIDSourceConfigCodes::SESSION_S0);
    msgIn.print();
    printf("SET SESSION COMPLETE\n");
    getc(stdin);

    //Check read-point in source
    printf("CHECK READ_POINT IN SOURCE\n");
    rfid.checkReadPointInSource(&msgIn, &read_point, &source);
    msgIn.print();
    if(msgIn.success())
    {
        msgIn.isReadPointInSource(&currentInStatus);
        printf("InStatus: %s\n", currentInStatus ? "true" : "false");
    }
    printf("CHECK READ_POINT IN SOURCE\n");
    getc(stdin);


    //Get Power
    printf("GET POWER\n");
    rfid.getPower(&msgIn);
    msgIn.print();
    if(msgIn.success())
    {
        msgIn.getPower(&powerCurrent);
        printf("Current power: %d\n", powerCurrent);
    }
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
    if(msgIn.success())
    {
        msgIn.getPower(&powerCurrent);
        printf("Current power: %d\n", powerCurrent);
    }
    printf("GET POWER COMPLETE\n");
    getc(stdin);

    //Antenna status
    printf("GET ANTENNA STATUS\n");
    rfid.getReadPointStatus(&msgIn, &read_point);
    msgIn.print();
    printf("GET ANTENNA STATUS COMPLETE\n");
    getc(stdin);

    printf("START INVENTORY\n");

    //Inventory
    //NOTE: the first couple of inventory calls could be as slow as 10-20sec. Be patient.
    printf("\n");
    vector<RFID> founds;
    string mask;
    unsigned short flags = (RFIDInventoryFlags::RSSI | RFIDInventoryFlags::TID_READING);
    for(;;) {
        founds.clear();
        printf("INVENTORY\n");

        int k=0;
        auto start = std::chrono::high_resolution_clock::now();
        rfid.inventory(&msgIn, &source, &mask, 0, flags);
        auto stop = std::chrono::high_resolution_clock::now();

        msgIn.getRFIDs(&founds);

        for (RFID& tag : founds)
        {
            tag.print();
            k++;
        }
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        printf("Tags found: %d , runtime: %lld ms\n", k, duration.count());

        sleep(1);
    }

    return 0;
}

