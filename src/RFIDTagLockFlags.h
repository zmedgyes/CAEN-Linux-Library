/*
 * Project:     serial RFID Library for linux
 * File:        RFIDTagLockFlags.h
 * Author:      Zsolt Medgyesi
 * Date:        july 2020
 * Version:     1.1
 *
 */
#ifndef RFIDTAGLOCKFLAGS_H
#define RFIDTAGLOCKFLAGS_H

/*!
 * \class RFIDTagLockFlags
 * \brief The RFIDTagLockFlags class is an auxiliary class created to simplify the work of the programmer.
 *
 * \brief The RFIDTagLockFlags class is an auxiliary class with the tag lock option flags can be sent to the RFID reader.

 */
class RFIDTagLockFlags
{
public:
    static const unsigned int USER_OPEN             = 0x00000000;
    static const unsigned int USER_PERMAOPEN        = 0x00000001;
    static const unsigned int USER_LOCK             = 0x00000002;
    static const unsigned int USER_PERMALOCK        = 0x00000003;

    static const unsigned int TID_OPEN              = 0x00000000;
    static const unsigned int TID_PERMAOPEN         = 0x00000004;
    static const unsigned int TID_LOCK              = 0x00000008;
    static const unsigned int TID_PERMALOCK         = 0x0000000C;

    static const unsigned int EPC_OPEN              = 0x00000000;
    static const unsigned int EPC_PERMAOPEN         = 0x00000010;
    static const unsigned int EPC_LOCK              = 0x00000020;
    static const unsigned int EPC_PERMALOCK         = 0x00000030;

    static const unsigned int ACCESSPWD_OPEN        = 0x00000000;
    static const unsigned int ACCESSPWD_PERMAOPEN   = 0x00000040;
    static const unsigned int ACCESSPWD_LOCK        = 0x00000080;
    static const unsigned int ACCESSPWD_PERMALOCK   = 0x000000C0;

    static const unsigned int KILLPWD_OPEN          = 0x00000000;
    static const unsigned int KILLPWD_PERMAOPEN     = 0x00000100;
    static const unsigned int KILLPWD_LOCK          = 0x00000200;
    static const unsigned int KILLPWD_PERMALOCK     = 0x00000300;

    static const unsigned int USER_MASK             = 0x00000C00;
    static const unsigned int TID_MASK              = 0x00003000;
    static const unsigned int EPC_MASK              = 0x0000C000;
    static const unsigned int ACCESSPWD_MASK        = 0x00030000;
    static const unsigned int KILLPWD_MASK          = 0x000C0000;
};

#endif //RFIDTAGLOCKFLAGS_H