#include "RFID.h"

RFID::RFID(unsigned char *value, unsigned short length)
{
    this->length = length;
    this->rfid = new unsigned char[length];
    memcpy(this->rfid, value, length);
}

RFID::~RFID()
{
    delete[] this->rfid;
}