/*
 * Project:     serial RFID Library for linux
 * File:        RFIDAttributeTypes.h
 * Author:      Claudio "Dna" Bonesana
 * Date:        september 2013
 * Version:     1.0
 *
 */
#ifndef RFIDDevice_H
#define RFIDDevice_H

#include "RFIDMessage.h"
#include "SerialDevice.h"

#include <memory>

using namespace std;

/*!
 * \class RFIDDevice
 * \brief The RFIDDevice class is used to interact with RFID readers.
 *
 * The RFIDDevice class offers a group of methods to work with the RFID readers.
 * This class uses the RFIDMessage nad SerialModule classes to contact the reader and recieve response.
 *
 * This class offers only a limited amount of already implemented commands for the RFID readers.
 * Other commands can be implemented very quickly using the RFIDMessage construction methods.
 */
class RFIDDevice
{
public:
    RFIDDevice(SerialDevice *device);
    ~RFIDDevice();

    static char *parseRFID(RFID *rfid);

    unique_ptr<RFIDMessage> sendAndRecieve(RFIDMessage *message);

    unique_ptr<RFIDMessage> getAntennaStatus(unsigned char *source, unsigned short len);
    unique_ptr<RFIDMessage> getPower();
    unique_ptr<RFIDMessage> setPower(unsigned int powerLevel);
    unique_ptr<RFIDMessage> setProtocol(unsigned int protocol);
    unique_ptr<RFIDMessage> getProtocol();
    unique_ptr<RFIDMessage> inventory(unsigned char *source, unsigned short len);
    unique_ptr<RFIDMessage> inventory(unsigned char *source, unsigned short source_len, unsigned char *mask, unsigned short mask_len, unsigned short mask_pos, unsigned short flags);

private:
    unsigned short id;
    unsigned short getNextId();
    SerialDevice *serialDevice;
};

#endif // RFIDDevice_H
