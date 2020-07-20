#include "RFID.h"

/*!
 * \fn RFID::RFID
 *
 * Constructs an empty RFID item. Used for memory allocation purposes.
 */
RFID::RFID()
    : id("")
{
}

/*!
 * \fn RFID::RFID
 *
 * Constructs a RFID item containing its ID (EPC).
 * 
 * \param id the ID of the RFID tag. 
 */
RFID::RFID(string &id)
    : id(id) 
{
    this->is_set_rssi = false;
    this->is_set_tid = false;
    this->is_set_source = false;
    this->is_set_read_point = false;
    this->is_set_type = false;
    this->is_set_timestamp = false;
}

/*!
 * \fn RFID::print
 *
 * Prints the ID of the tag.
 */
void RFID::print()
{
    for(size_t i = 0; i < this->id.size(); i++)
    {
        printf("%02X",this->id[i]);
    }
    printf("\n");
}

/*!
 * \fn RFID::setTID
 *
 * Sets the TID (globally unique ID + variable informations) value of the tag.
 * 
 * \param value the current TID of the RFID tag. 
 */
void RFID::setTID(string &value)
{
    this->tid = value;
    this->is_set_tid = true;
}

/*!
 * \fn RFID::hasTID
 *
 * If the TID field of the tag is set.
 * 
 * \return the set status of the TID field. 
 */
bool RFID::hasTID()
{
    return this->is_set_tid;

}

/*!
 * \fn RFID::setRSSI
 *
 * Sets the RSSI (Return Signal Strength Indicator) value of the tag. ~(-400(Good) -> -900(Bad))
 * 
 * \param value the current RSSI of the RFID tag. 
 */
void RFID::setRSSI(short value)
{
    this->rssi = value;
    this->is_set_rssi = true;
}

/*!
 * \fn RFID::hasRSSI
 *
 * If the RSSI field of the tag is set.
 * 
 * \return the set status of the RSSI field. 
 */
bool RFID::hasRSSI()
{
    return this->is_set_rssi;
}

/*!
 * \fn RFID::setSource
 *
 * Sets which logical source was the tag read from.
 * 
 * \param value the source name of the current read. 
 */
void RFID::setSource(string &value)
{
    source = value;
    this->is_set_source = true;
}

/*!
 * \fn RFID::hasSource
 *
 * If the source field of the tag is set.
 * 
 * \return the set status of the source field. 
 */
bool RFID::hasSource()
{
    return this->is_set_source;
}

/*!
 * \fn RFID::setReadPoint
 *
 * Sets which read point (antenna) was the tag read from.
 * 
 * \param value the name of the current read point. 
 */
void RFID::setReadPoint(string &value)
{
    this->read_point = value;
    this->is_set_read_point = true;
}

/*!
 * \fn RFID::hasReadPoint
 *
 * If the read point field of the tag is set.
 * 
 * \return the set status of the read point field. 
 */
bool RFID::hasReadPoint()
{
    return this->is_set_read_point;
}

/*!
 * \fn RFID::setType
 *
 * Sets the air protocol type of the tag.
 * 
 * \param value the air protocol type of the RFID tag. 
 */
void RFID::setType(unsigned short value)
{
    this->type = value;
    this->is_set_type = true;
}

/*!
 * \fn RFID::hasType
 *
 * If the Type field of the tag is set.
 * 
 * \return the set status of the Type field. 
 */
bool RFID::hasType()
{
    return this->is_set_type;
}
/*!
 * \fn RFID::setTimestamp
 *
 * Sets the current read timestamp of the tag.
 * 
 * \param value the current read timestamp of the RFID tag. 
 */
void RFID::setTimestamp(string &value)
{
    this->timestamp = value;
    this->is_set_timestamp = true;
}

/*!
 * \fn RFID::hasTimestamp
 *
 * If the timestamp field of the tag is set.
 * 
 * \return the set status of the timestamp field. 
 */
bool RFID::hasTimestamp()
{
    return this->is_set_timestamp;
}