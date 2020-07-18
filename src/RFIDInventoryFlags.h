/*
 * Project:     serial RFID Library for linux
 * File:        RFIDInventoryFlags.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDINVENTORYFLAGS_H
#define RFIDINVENTORYFLAGS_H

/*!
 * \class RFIDInventoryFlags
 * \brief The RFIDInventoryFlags class is an auxiliary class created to simplify the work of the programmer.
 *
 * \brief The RFIDInventoryFlags class is an auxiliary class with the inventory settings flags can be sent to the RFID reader.

 */
class RFIDInventoryFlags
{
public:
    static const unsigned short RSSI            = 0x0001;
    static const unsigned short FRAMED          = 0x0002;
    static const unsigned short CONTINOUS       = 0x0004;
    static const unsigned short COMPACT         = 0x0008;
    static const unsigned short TID_READING     = 0x0010;
    static const unsigned short EVENT_TRIGGER   = 0x0020;
    static const unsigned short XPC             = 0x0040;
    static const unsigned short MATCH_TAG       = 0x0080;
    static const unsigned short PC              = 0x0100;
};

#endif //RFIDINVENTORYFLAGS_H