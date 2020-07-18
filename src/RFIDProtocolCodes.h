/*
 * Project:     serial RFID Library for linux
 * File:        RFIDProtocolCodes.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDPROTOCOLCODES_H
#define RFIDPROTOCOLCODES_H

/*!
 * \class RFIDProtocolCodes
 * \brief The RFIDProtocolCodes class is an auxiliary class created to simplify the work of the programmer.
 *
 * \brief The RFIDProtocolCodes class is an auxiliary class with the protocol profiles can be sent to the RFID reader.

 */
class RFIDProtocolCodes
{
public:
    static const unsigned int ISO18000_6B       = 0x00000000;
    static const unsigned int EPC_C1G1          = 0x00000001;
    static const unsigned int ISO18000_6A       = 0x00000002;
    static const unsigned int EPC_C1G2          = 0x00000003;
    static const unsigned int MULTIPROTOCOL     = 0x00000004;
    static const unsigned int EPC119            = 0x00000005;
};
#endif //RFIDPROTOCOLCODES_H
