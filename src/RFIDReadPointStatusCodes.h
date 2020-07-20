/*
 * Project:     serial RFID Library for linux
 * File:        RFIDReadPointStatusCodes.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDREADPOINTSTATUSCODES_H
#define RFIDREADPOINTSTATUSCODES_H

/*!
 * \class RFIDReadPointStatusCodes
 * \brief The RFIDReadPointStatusCodes class is an auxiliary class created to simplify the work of the programmer.
 *
 * \brief The RFIDReadPointStatusCodes class is an auxiliary class with the read point status codes received from the RFID reader.

 */
class RFIDReadPointStatusCodes
{
public:
    static const unsigned int GOOD = 0x00000000;
    static const unsigned int POOR = 0x00000001;
    static const unsigned int BAD = 0x00000002;
    static const unsigned int INVALID_READ_POINT = 0x00005F33;
};
#endif //RFIDREADPOINTSTATUSCODES_H
