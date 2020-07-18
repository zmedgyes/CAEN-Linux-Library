/*
 * Project:     serial RFID Library for linux
 * File:        RFIDBitRateCodes.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDBITRATECODES_H
#define RFIDBITRATECODES_H

/*!
 * \class RFIDBitRateCodes
 * \brief The RFIDBitRateCodes class is an auxiliary class created to simplify the work of the programmer.
 *
 * \brief The RFIDBitRateCodes class is an auxiliary class with the bit rate settings can be sent to the RFID reader.

 */
class RFIDBitRateCodes
{
public:
    static const unsigned short DSB_ASK_FM0_TX10RX40    = 0x0001;
    static const unsigned short DSB_ASK_FM0_TX40RX40    = 0x0002;
    static const unsigned short DSB_ASK_FM0_TX40RX160   = 0x0003;
    static const unsigned short DSB_ASK_FM0_TX160RX400  = 0x0004;
    static const unsigned short DSB_ASK_M2_TX40RX160    = 0x0005;
    static const unsigned short PR_ASK_M4_TX40RX250     = 0x0006;
    static const unsigned short PR_ASK_M4_TX40RX300     = 0x0007;
    static const unsigned short PR_ASK_M2_TX40RX250     = 0x0008;
    static const unsigned short DSB_ASK_M4_TX40RX256    = 0x000A;
    static const unsigned short PR_ASK_M4_TX40RX320     = 0x000B;
    static const unsigned short PR_ASK_FM0_TX40RX640    = 0x000C;
    static const unsigned short PR_ASK_M4_TX80RX320     = 0x000D;
    static const unsigned short PR_ASK_M4_TX40RX256     = 0x000E;
    static const unsigned short PR_ASK_M8_TX40RX256     = 0x000F;
};
#endif //RFIDBITRATECODES_H