/*
 * Project:     serial RFID Library for linux
 * File:        RFIDRegulationCodes.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDREGULATIONCODES_H
#define RFIDREGULATIONCODES_H

/*!
 * \class RFIDRegulationCodes
 * \brief RFIDRegulationCodes class is an auxiliary class created to simplify the work of the programmer.
 *
 * \brief The RFIDRegulationCodes class is an auxiliary class with the international radio-frequency regulation profiles can be sent to the RFID reader.

 */
class RFIDRegulationCodes
{
public:
    static const unsigned short ETSI_302208     = 0x0000;
    static const unsigned short ETSI_300220     = 0x0001;
    static const unsigned short FCC_US          = 0x0002;
    static const unsigned short MALAYSIA        = 0x0003;
    static const unsigned short KOREA           = 0x0005;
    static const unsigned short AUSTRALIA       = 0x0006;
    static const unsigned short CHINA           = 0x0007;
    static const unsigned short TAIWAN          = 0x0008;
    static const unsigned short SINGAPORE       = 0x0009;
    static const unsigned short BRAZIL          = 0x000A;
    static const unsigned short JAPAN_STD_T106  = 0x000B;
    static const unsigned short JAPAN_STD_T107  = 0x000C;
    static const unsigned short PERU            = 0x000D;
    static const unsigned short SOUTH_AFRICA    = 0x000E;
    static const unsigned short CHILE           = 0x000F;
};
#endif //RFIDREGULATIONCODES_H