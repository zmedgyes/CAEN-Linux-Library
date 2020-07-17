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
    static const unsigned int Q = 0x0003;
    static const unsigned int SESSION = 0x0004;
};

#endif //RFIDSOURCECONFIGTYPES_H
