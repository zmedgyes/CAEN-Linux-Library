/*
 * Project:     serial RFID Library for linux
 * File:        RFIDMemoryBankCodes.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDMEMORYBANKCODES_H
#define RFIDMEMORYBANKCODES_H

/*!
 * \class RRFIDMemoryBankCodes
 * \brief The RFIDMemoryBankCodes class is an auxiliary class created to simplify the work of the programmer.
 *
 * \brief The RFIDMemoryBankCodes class is an auxiliary class with the tag memory bank codes can be sent to the RFID reader.

 */
class RFIDMemoryBankCodes
{
public:
    static const unsigned short RESERVED = 0x0000;
    static const unsigned short EPC = 0x0001;
    static const unsigned short TID = 0x0002;
    static const unsigned short USER = 0x0003;
};

#endif //RFIDMEMORYBANKCODES_H