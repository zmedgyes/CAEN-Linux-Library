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

#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;

/*!
 * \class RFID
 * \brief The class RFID represents a single RFID Tag.
 */
class RFID
{
    public:
        
        string id;
        short rssi;
        string tid;
        string source;
        string read_point;
        unsigned short type;
        string timestamp;

        RFID();
        RFID(string &id);

        void print();

        void setTID(string& value);
        bool hasTID();
        void setRSSI(short value);
        bool hasRSSI();
        void setSource(string& value);
        bool hasSource();
        void setReadPoint(string& value);
        bool hasReadPoint();
        void setType(unsigned short value);
        bool hasType();
        void setTimestamp(string& value);
        bool hasTimestamp();

    private:
        bool is_set_rssi;
        bool is_set_tid;
        bool is_set_source;
        bool is_set_read_point;
        bool is_set_type;
        bool is_set_timestamp;
};

#endif //RFID_H