/*
 * Project:     serial RFID Library for linux
 * File:        RFIDMessage.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDMESSAGE_H
#define RFIDMESSAGE_H

#include "RFIDAttributeTypes.h"
#include "RFIDCommandsCodes.h"
#include "RFIDSourceConfigTypes.h"
#include "RFIDSourceConfigCodes.h"

#include "MessageRFIDBody.h"
#include "RFID.h"

#include <vector>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>

#define HEAD_START 0
#define MESSAGE_ID 2
#define VENDOR_ID 4
#define MSG_LENGTH 8

using namespace std;

/*!
 * \class RFIDMessage
 * \brief The RFIDMessage class is a container for the RFID messages.
 *
 * The RFIDMessage class is used to store the information for and from the RFID reader.
 * This class is based on the Attribute-Value Pair structure used by the protocol easy2read.
 * Every message is composed by an header followed by a list of frames, used to describe commands, values and operations.
 *
 * Every object of this type is a message sent to the reader or recieved from it.
 *
 * This class offers methods to build a complete message, but offers only methods to test if the response is a success response and to recovery the RFID code.
 * Others operations must be implemented.
 */
class RFIDMessage
{
public:
    RFIDMessage();
    RFIDMessage(unsigned short id);
    RFIDMessage(unsigned char *buffer, unsigned int messageLength);
    virtual ~RFIDMessage();

    int addCommand(unsigned short type, unsigned short value);
    int addCommand(unsigned short type, unsigned int value);
    int addCommand(unsigned short type, unsigned long value, unsigned short len);
    int addCommand(unsigned short type, unsigned char *value, unsigned short len);

    int getBuffer(unsigned char *buffer);
    unsigned short getLength();
    int initFromBuffer(unsigned char *buffer, unsigned int messageLength);
    bool isValid();

    void getRFIDs(vector<RFID> *founds);
    bool success();

    void print();

private:
    /* header */
    unsigned short version;     // 2 bytes
    unsigned short messageId;   // 2 bytes
    unsigned int   vendor;      // 4 bytes
    unsigned short length;      // 2 bytes
    bool valid;

    std::vector<MessageRFIDBody> body;

    void shortToBuffer(unsigned short s, unsigned char *converted);
    void intToBuffer(unsigned int i, unsigned char *converted);
    void longToBuffer(unsigned long l, unsigned char *converted, unsigned short len);

    unsigned short bufferToShort(unsigned char *buffer);
    short bufferToSignedShort(unsigned char *buffer);
    unsigned int bufferToInt(unsigned char *buffer);
};

#endif // RFIDMESSAGE_H
