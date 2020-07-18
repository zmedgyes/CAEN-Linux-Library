/*
 * Project:     serial RFID Library for linux
 * File:        RFIDSourceConfigTypes.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDSOURCECONFIGTYPES_H
#define RFIDSOURCECONFIGTYPES_H

/*!
 * \class RFIDSourceConfigTypes
 * \brief The RFIDSourceConfigTypes class is an auxiliary class created to simplify the work of the programmer.
 *
 * \brief The RFIDSourceConfigTypes class is an auxiliary class with the source parameter types can be sent to the RFID reader.

 */
class RFIDSourceConfigTypes
{
public:
    static const unsigned int READ_CYCLE             = 0x00000000;
    static const unsigned int OBSERVED_THRESHOLD     = 0x00000001;
    static const unsigned int LOST_THRESHOLD         = 0x00000002;
    static const unsigned int Q                      = 0x00000003;
    static const unsigned int SESSION                = 0x00000004;
    static const unsigned int TARGET                 = 0x00000005;
    static const unsigned int SELECTED               = 0x00000006;
    static const unsigned int ISO18006B_DESB         = 0x00000007;
    static const unsigned int DWELL_TIME             = 0x00000008;
    static const unsigned int INV_COUNT              = 0x0000000A;
    static const unsigned int TID_LENGTH             = 0x0000000D;
    static const unsigned int QUIET_TIME             = 0x0000000F;
};
#endif //RFIDSOURCECONFIGTYPES_H
