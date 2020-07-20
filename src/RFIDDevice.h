/*
 * Project:     serial RFID Library for linux
 * File:        RFIDDevice.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDDevice_H
#define RFIDDevice_H

#include "RFIDMessage.h"
#include "RFIDInventoryFlags.h"
#include "RFIDMemoryBankCodes.h"
#include "SerialDevice.h"

#include <string>

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

    int getReaderInfo(RFIDMessage *result);
    int getFirmwareVersion(RFIDMessage *result);
    int getReadPointStatus(RFIDMessage* result, string* read_point);
    int getPower(RFIDMessage* result);
    int setPower(RFIDMessage* result, unsigned int power_level);
    int setProtocol(RFIDMessage* result, unsigned int protocol);
    int getProtocol(RFIDMessage* result);
    int setSourceQ(RFIDMessage* result, string* source, unsigned int value);
    int setSourceSession(RFIDMessage* result, string* source, unsigned int value);
    int setSourceTarget(RFIDMessage *result, string *source, unsigned int value);
    int inventory(RFIDMessage* result, string* source);
    int inventory(RFIDMessage* result, string* source, string* mask, unsigned short mask_pos, unsigned short flags);
    int readTagMemory(RFIDMessage *result, string *source, string *tagId, unsigned short memory_bank, unsigned short address, unsigned short length);
    int writeTagMemory(RFIDMessage *result, string *source, string *tagId, unsigned short memory_bank, unsigned short address, string *value, string *password);
    int setTagId(RFIDMessage *result, string *source, string *oldTagId, string *newTagId, string *password);
    //TODO: lockTag
    //TODO: killTag
    int checkReadPointInSource(RFIDMessage *result, string *read_point, string *source);
    int addReadPointToSource(RFIDMessage *result, string *read_point, string *source);
    int removeReadPointFromSource(RFIDMessage *result, string *read_point, string *source);

private:
    unsigned short id;
    SerialDevice *serialDevice;

    int sendAndRecieve(RFIDMessage* tosend, RFIDMessage* result);
    unsigned short getNextId();

    int setSourceConfig(RFIDMessage* result, string* source, unsigned int param_id, unsigned int param_value);
};

#endif // RFIDDevice_H
