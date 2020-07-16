/*
 * Project:     serial RFID Library for linux
 * File:        MessageRFIDBody.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDMESSAGEBODY_H
#define RFIDMESSAGEBODY_H

#include <cstring>
#include <cstdlib>
#include <memory>

/*!
 * \class MessageRFIDBody
 * \brief MessageRFIDBody represents a single frame of the easy2read commands list.
 */

using namespace std;

class MessageRFIDBody 
{
    public:
        unsigned short reserved;       // 2 bytes
        unsigned short length;         // 2 bytes
        unsigned short attributeType;  // 2 bytes
        unsigned char *attributeValue; // * bytes

        unsigned short attributeValueLength;

        MessageRFIDBody(unsigned short reserved, unsigned short type, unsigned char *value, unsigned short len);
        ~MessageRFIDBody();

        static unique_ptr<MessageRFIDBody> CreateCommand(unsigned short type, unsigned char *value, unsigned short len);
};

#endif