/*
 * Project:     serial RFID Library for linux
 * File:        RFID.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */

#ifndef RFID_H
#define RFID_H

#include <cstring>
#include <cstdlib>

/*!
 * \class RFID
 * \brief The class RFID represents a single RFID code.
 */
class RFID
{
    public:
        unsigned short length;
        unsigned char *rfid;
        short rssi;

        RFID(unsigned char *value, unsigned short length);
        ~RFID();
};

#endif