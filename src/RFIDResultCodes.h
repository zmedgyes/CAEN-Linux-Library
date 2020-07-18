/*
 * Project:     serial RFID Library for linux
 * File:        RFIDResultCodes.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDRESULTCODES_H
#define RFIDRESULTCODES_H

/*!
 * \class RFIDResultCodes
 * \brief The RFIDResultCodes class is an auxiliary class created to simplify the work of the programmer.
 *
 * \brief The RFIDResultCodes class is an auxiliary class with the command result codes sent by the RFID reader.

 */
class RFIDResultCodes
{
public:
    static const unsigned short OK                              = 0x0000;

    //NOTE: error codes are firmware specific. Use them with caution.
    static const unsigned short ERROR_CHANNEL_NAME_EXISTS       = 0x0064;
    static const unsigned short ERROR_ADDRESS_ALREADY_IN_USE    = 0x0065;
    static const unsigned short ERROR_UNKNOWN                   = 0x0066;
    static const unsigned short ERROR_BAD_CHANNEL               = 0x0067;
    static const unsigned short ERROR_INVALID_SOURCE_NAME       = 0x0068;
    static const unsigned short ERROR_INVALID_CHANNEL_NAME      = 0x0069;
    static const unsigned short ERROR_TOO_MANY_CHANNEL          = 0x006A;
    static const unsigned short ERROR_TOO_MANY_SOURCE           = 0x006B;
    static const unsigned short ERROR_SOURCE_NOT_IN_CHANNEL     = 0x006D;
    static const unsigned short ERROR_BAD_TIMER_VALUE           = 0x006E;
    static const unsigned short ERROR_TRIGGER_NAME_EXISTS       = 0x006F;
    static const unsigned short ERROR_TOO_MANY_TRIGGER          = 0x0070;
    static const unsigned short ERROR_BAD_TRIGGER               = 0x0071;
    static const unsigned short ERROR_BAD_ADDRESS               = 0x0072;
    static const unsigned short ERROR_INVALID_PROTOCOL          = 0x0073;
    static const unsigned short ERROR_BAD_PORT_ADDRESS          = 0x0074;
    static const unsigned short ERROR_CANNOT_CONNECT_TO_SERVER  = 0x0075;
    static const unsigned short ERROR_INVALID_TRIGGER_NAME      = 0x0076;
    static const unsigned short ERROR_INVALID_TIME              = 0x0077;
    static const unsigned short ERROR_SOURCE_NOT_FOUND          = 0x0078;
    static const unsigned short ERROR_TRIGGER_NOT_FOUND         = 0x0079;
    static const unsigned short ERROR_CHANNEL_NOT_FOUND         = 0x007A;
    static const unsigned short ERROR_BAD_READ_POINT            = 0x007B;
    static const unsigned short ERROR_CHANNEL_BUSY              = 0x007C;
    static const unsigned short ERROR_TRIGGER_BUSY              = 0x007D;
    static const unsigned short ERROR_INTERNAL_FILESYSTEM       = 0x007E;
    static const unsigned short ERROR_INVALID_COMMAND           = 0x007F;
    static const unsigned short ERROR_BAD_PARAMETER_VALUE       = 0x0080;
    static const unsigned short ERROR_NOTIFY_SERVER_NOT_READY   = 0x0081;
    static const unsigned short ERROR_POWER_VALUE_OUT_OF_RANGE  = 0x00B7;
    static const unsigned short ERROR_INVALID_PARAMETER         = 0x00C8;
    static const unsigned short ERROR_LOGICAL_SOURCE_DISABLED   = 0x00C9;
    static const unsigned short ERROR_TAG_NOT_PRESENT           = 0x00CA;
    static const unsigned short ERROR_WRITING_TAG               = 0x00CB;
    static const unsigned short ERROR_READING_TAG               = 0x00CC;
    static const unsigned short ERROR_BAD_TAG_ADDRESS           = 0x00CD;
    static const unsigned short ERROR_INVALID_FUNCTION          = 0x00CE;
    static const unsigned short ERROR_SELECT_UNSELECT           = 0x00CF;
    static const unsigned short ERROR_TAG_LOCKED                = 0x00D1;
    static const unsigned short ERROR_UNSUPPORTED               = 0x00D2;
    static const unsigned short ERROR_POWER                     = 0x00D3;
    static const unsigned short ERROR_NON_SPECIFIC              = 0x00D4;
    static const unsigned short ERROR_KILL_TAG                  = 0x00D5;
    static const unsigned short ERROR_CHANNELS_FULL             = 0x00D6;
    static const unsigned short ERROR_MATCH_READ_POINT          = 0x00D7;
};
#endif //RFIDRESULTCODES_H