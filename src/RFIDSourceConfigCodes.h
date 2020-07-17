/*
 * Project:     serial RFID Library for linux
 * File:        RFIDSourceConfigCodes.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDSOURCECONFIGCODES_H
#define RFIDSOURCECONFIGCODES_H

/*!
 * \class RFIDSourceConfigCodes
 * \brief The RFIDSourceConfigCodes class is an auxiliary class created to simplify the work of the programmer.
 *
 * \brief The RFIDSourceConfigCodes class is an auxiliary class with the source parameter values can be sent to the RFID reader.

 */
class RFIDSourceConfigCodes
{
public:
    static const unsigned int SESSION_0 = 0x0000;
    static const unsigned int Q_3 = 0x0003;
};

#endif //RFIDSOURCECONFIGCODES_H