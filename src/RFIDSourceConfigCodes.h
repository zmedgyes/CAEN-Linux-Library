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
    static const unsigned int SESSION_S0            = 0x00000000;
    static const unsigned int SESSION_S1            = 0x00000001;
    static const unsigned int SESSION_S2            = 0x00000002;
    static const unsigned int SESSION_S3            = 0x00000003;
    static const unsigned int Q_0                   = 0x00000000;   //1
    static const unsigned int Q_1                   = 0x00000001;   //2
    static const unsigned int Q_2                   = 0x00000002;   //3-6
    static const unsigned int Q_3                   = 0x00000003;   //7-15
    static const unsigned int Q_4                   = 0x00000004;   //16-30
    static const unsigned int Q_5                   = 0x00000005;   //30-50
    static const unsigned int Q_6                   = 0x00000006;   //50-100
    static const unsigned int Q_7                   = 0x00000007;   //100-200
    static const unsigned int TARGET_A              = 0x00000000;
    static const unsigned int TARGET_B              = 0x00000001;
    static const unsigned int SELECTED_YES          = 0x00000003;
    static const unsigned int SELECTED_NO           = 0x00000002;
    static const unsigned int ALL_SELECTED          = 0x00000000;
    static const unsigned int ISO18006B_DESB_ON     = 0x00000001;
    static const unsigned int ISO18006B_DESB_OFF    = 0x00000000;
};

#endif //RFIDSOURCECONFIGCODES_H