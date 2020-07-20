#include "RFIDMessage.h"

/*!
 * \fn RFIDMessage::RFIDMessage
 *
 * Constructs an invalid empty message which could be later populated with data. Used for memory allocation purposes.
 *
 */
RFIDMessage::RFIDMessage()
{
    version = 0;
    messageId = 0;
    vendor = 0;
    length = 10; // 10 header
    valid = false;
}

/*!
 * \fn RFIDMessage::RFIDMessage
 *
 * Constructs a void command message (version = 0x8001) wich need to be populated with the method RFIDMessage::addCommand.
 *
 * \param id id of the message
 */
RFIDMessage::RFIDMessage(unsigned short id)
{
    version = 0x8001;
    messageId = id;
    vendor = 0x00005358;
    length = 10;            // 10 header
    valid = true;
}

/*!
 * \fn RFIDMessage::RFIDMessage
 *
 * Constructs a message from a buffer. The buffer is the response via serial device of the reader.
 *
 * \param buffer the buffer of data recieved from the reader.
 * \param messageLength the lenght of the buffer.
 */
RFIDMessage::RFIDMessage(unsigned char *buffer, unsigned int message_length)
{
    valid = false;
    initFromBuffer(buffer, message_length);
}

/*!
 * \fn RFIDMessage::initFromBuffer
 *
 * Clears the current content from the message and then initializes it with data received from the reader;
 *
 * \param buffer the buffer of data recieved from the reader.
 * \param messageLength the lenght of the buffer.
 * \return a result code. 0 = OK.
 */
int RFIDMessage::initFromBuffer(unsigned char *buffer, unsigned int message_length)
{
    //in case if this is a re-init
    valid = false;
    body.clear();

    if(message_length < 10)
    {
        return -1;
    }

    version = bufferToShort(&buffer[HEAD_START]);
    messageId = bufferToShort(&buffer[MESSAGE_ID]);
    vendor = bufferToInt(&buffer[VENDOR_ID]);
    length = bufferToShort(&buffer[MSG_LENGTH]);

    unsigned int position = 10;

    while (position < message_length)
    {
        short reserved = bufferToShort(&buffer[position]);
        short length = bufferToShort(&buffer[position + 2]);
        short attributeType = bufferToShort(&buffer[position + 4]);
        body.emplace_back(reserved, attributeType, &buffer[position + 6], length);
        position += length;
    }

    valid = (position == length);
    return 0;
}

/*!
 * \fn RFIDMessage::~RFIDMessage
 *
 * Destructs a message.
 */
RFIDMessage::~RFIDMessage()
{
}

/*!
 * \fn RFIDMessage::addCommand
 *
 * The method RFIDMessage::addCommand add a new command frame to the message.
 * This version is used with 2 bytes value.
 *
 * \param type use RFIDAttributeTypes entries to simplify the work.
 * \param value use RFIDCommandsCodes entries to simplify the work.
 * \return 0 if success, otherwise -1.
 */
int RFIDMessage::addCommand(unsigned short type, unsigned short value)
{
    unsigned char *temp = new unsigned char[2]();
    shortToBuffer(value,temp);
    int rc = addCommand(type,temp,2);
    delete[] temp;
    return rc;
}

/*!
 * \fn RFIDMessage::addCommand
 *
 * The method RFIDMessage::addCommand add a new command frame to the message.
 * This version is used with 4 bytes value.
 *
 * \param type use RFIDAttributeTypes entries to simplify the work.
 * \param value use RFIDCommandsCodes entries to simplify the work.
 * \return 0 if success, otherwise -1.
 */
int RFIDMessage::addCommand(unsigned short type, unsigned int value)
{
    unsigned char *temp = new unsigned char[4]();
    intToBuffer(value,temp);
    int rc = addCommand(type,temp,4);
    delete[] temp;
    return rc;
}

/*!
 * \fn RFIDMessage::addCommand
 *
 * The method RFIDMessage::addCommand add a new command frame to the message.
 * This version is used with an arbitrary numbers of bytes in value.
 *
 * \param type use RFIDAttributeTypes entries to simplify the work.
 * \param value use RFIDCommandsCodes entries to simplify the work.
 * \param lenlength in bytes of the value \a value parameter.
 * \return 0 if success, otherwise -1.
 */
int RFIDMessage::addCommand(unsigned short type, unsigned long value, unsigned short len)
{
    unsigned char *temp = new unsigned char[len];
    longToBuffer(value,temp,len);
    int rc = addCommand(type, temp, len);
    delete [] temp;
    return rc;
}

/*!
 * \fn RFIDMessage::addCommand
 *
 * The method RFIDMessage::addCommand add a new command frame to the message.
 * This version is used with an arbitrary numbers of bytes in value.
 *
 * \param type use RFIDAttributeTypes entries to simplify the work.
 * \param value use RFIDCommandsCodes entries to simplify the work.
 * \param len in bytes of the value \a value parameter.
 * \return 0 if success, otherwise -1.
 */
int RFIDMessage::addCommand(unsigned short type, unsigned char *value, unsigned short len)
{
    body.emplace_back(type, value, len);
    length += body.back().length;

    return 0;
}

/*!
 * \fn RFIDMessage::getBuffer
 * 
 * Serializes the content of the message in buffer format, ready to be used with the a serial device.
 * 
 * \param buffer buffer where the content should be serialized into.
 * \return a result code. 0 = OK.
 */
int RFIDMessage::getBuffer(unsigned char *buffer)
{
    unsigned int index = 10;

    /* header */
    shortToBuffer(version, &buffer[0]);
    shortToBuffer(messageId, &buffer[2]);
    intToBuffer(vendor, &buffer[4]);
    shortToBuffer(length, &buffer[8]);

    /* body */
    for (auto& temp : body)
    {

        shortToBuffer(temp.reserved, &buffer[index]);
        index += 2;
        shortToBuffer(temp.length, &buffer[index]);
        index += 2;
        shortToBuffer(temp.attributeType, &buffer[index]);
        index += 2;

        for (size_t i = 0; i < temp.attributeValue.size(); i++)
        {
            buffer[index] = temp.attributeValue[i];
            index++;
        }
    }

    return 0;
}

/*!
 * \fn RFIDMessage::getLength
 * \return the length of the whole message.
 */
unsigned short RFIDMessage::getLength()
{
    return length;
}

/*!
 * \fn RFIDMessage::isValid
 * \return if the message has a valid (full, consistent, serializable) content.
 */
bool RFIDMessage::isValid()
{
    return valid;
}

/*!
 * \fn RFIDMessage::getRFIDs
 * \param founds a vector, where the found tags will be written into.
 * \return a result code. 0 = OK.
 */
int  RFIDMessage::getRFIDs(vector<RFID> *founds)
{
    MessageRFIDBody *last_source = nullptr;
    MessageRFIDBody *last_read_point = nullptr;
    MessageRFIDBody *last_type = nullptr;
    MessageRFIDBody *last_timestamp = nullptr;

    //NOTE: some fields like TAG_ID or TAG_TID have a separate designated message item, which describe their length.
    //As far my experiences goes, these information is also contained in the message items, in which the said fields are received.
    //If someone knows, why duplicate inforamtion is sent in these cases, please enlighten me. - zmedgyes
    //Here is an example to cross-check these informations
    /*
    MessageRFIDBody *last_tag_length;
    for (MessageRFIDBody &temp : body)
    {
        if (temp.attributeType == RFIDAttributeTypes::TAG_ID_LEN)
        {
            last_tag_length = &(temp);
        }
        if (temp.attributeType == RFIDAttributeTypes::TAG_ID)
        {
            unsigned short receivedTagIDLength = bufferToShort((unsigned char *)last_tag_length->attributeValue.data());
            unsigned short itemTagIDLength = (unsigned short)temp.attributeValue.size();
            if (receivedTagIDLength == itemTagIDLength)
            {
                founds->emplace_back(temp.attributeValue);
            }
        }
    }
    */

    for(MessageRFIDBody& el : body)
    {
        if (el.attributeType == RFIDAttributeTypes::SOURCE_NAME)
        {
            last_source = &el;
        }
        else if (el.attributeType == RFIDAttributeTypes::READ_POINT_NAME)
        {
            last_read_point = &el;
        }
        else if (el.attributeType == RFIDAttributeTypes::TAG_TYPE)
        {
            last_type = &el;
        }
        else if (el.attributeType == RFIDAttributeTypes::TIME_STAMP)
        {
            last_timestamp = &el;
        }
        else if (el.attributeType == RFIDAttributeTypes::TAG_ID)
        {
            founds->emplace_back(el.attributeValue);
            founds->back().setSource(last_source->attributeValue);
            founds->back().setReadPoint(last_read_point->attributeValue);
            founds->back().setType(bufferToShort((unsigned char *)last_type->attributeValue.data()));
            founds->back().setTimestamp(last_timestamp->attributeValue);
        }
        else if (el.attributeType == RFIDAttributeTypes::TAG_TID)
        {
            founds->back().setTID(el.attributeValue);
        }
        else if (el.attributeType == RFIDAttributeTypes::RSSI)
        {
            founds->back().setRSSI(bufferToSignedShort((unsigned char*)el.attributeValue.data()));
        }
    }
    return 0;
}

/*!
 * \fn RFIDMessage::getPower
 * \param power a container, where the power level will be written into.
 * \return a result code. 0 = OK.
 */
int RFIDMessage::getPower(unsigned int* power)
{
    for(MessageRFIDBody& el : body)
    {
        if(el.attributeType == RFIDAttributeTypes::POWER_GET)
        {
            (*power) = bufferToInt((unsigned char*)el.attributeValue.data());
            return 0;
        }
    }
    return -1;
}

/*!
 * \fn RFIDMessage::getProtocol
 * \param protocol a container, where the protocol will be written into.
 * \return a result code. 0 = OK.
 */
int RFIDMessage::getProtocol(unsigned int* protocol)
{
    for (MessageRFIDBody &el : body)
    {
        if (el.attributeType == RFIDAttributeTypes::PROTOCOL)
        {
            (*protocol) = bufferToInt((unsigned char *)el.attributeValue.data());
            return 0;
        }
    }
    return -1;
}

/*!
 * \fn RFIDMessage::getReadPointStatus
 * \param status a container, where the read point status will be written into.
 * \return a result code. 0 = OK.
 */
int RFIDMessage::getReadPointStatus(unsigned int *status)
{
    for (MessageRFIDBody &el : body)
    {
        if (el.attributeType == RFIDAttributeTypes::READ_POINT_STATUS)
        {
            (*status) = bufferToInt((unsigned char *)el.attributeValue.data());
            return 0;
        }
    }
    return -1;
}

/*!
 * \fn RFIDMessage::getReaderInfo
 * \param info a container, where the reader info (product name + serial no.) will be written into.
 * \return a result code. 0 = OK.
 */
int RFIDMessage::getReaderInfo(string *info)
{
    for (MessageRFIDBody &el : body)
    {
        if (el.attributeType == RFIDAttributeTypes::READER_INFO)
        {
            info->assign(el.attributeValue);
            return 0;
        }
    }
    return -1;
}

/*!
 * \fn RFIDMessage::getTagReadData
 * \param data a container, where the data received from the tag will be written into.
 * \return a result code. 0 = OK.
 */
int RFIDMessage::getTagReadData(string *data)
{
    for (MessageRFIDBody &el : body)
    {
        if (el.attributeType == RFIDAttributeTypes::TAG_VALUE)
        {
            data->assign(el.attributeValue);
            return 0;
        }
    }
    return -1;
}

/*!
 * \fn RFIDMessage::getFirmwareVersion
 * \param version a container, where the firmware version will be written into.
 * \return a result code. 0 = OK.
 */
int RFIDMessage::getFirmwareVersion(string *version)
{
    for (MessageRFIDBody &el : body)
    {
        if (el.attributeType == RFIDAttributeTypes::FW_RELEASE)
        {
            version->assign(el.attributeValue);
            return 0;
        }
    }
    return -1;
}

/*!
 * \fn RFIDMessage::isReadPointInSource
 * \param status a container, where the check result will be written into.
 * \return a result code. 0 = OK.
 */
int RFIDMessage::isReadPointInSource(bool *status)
{
    for (MessageRFIDBody &el : body)
    {
        if (el.attributeType == RFIDAttributeTypes::BOOLEAN)
        {
            unsigned short boolVal = bufferToShort((unsigned char *)el.attributeValue.data());
            (*status) = (boolVal == 0x0001);
            return 0;
        }
    }
    return -1;
}

/*!
 * \fn RFIDMessage::getSourceConfigValue
 * \param value a container, where the source config value will be written into.
 * \return a result code. 0 = OK.
 */
int RFIDMessage::getSourceConfigValue(unsigned int *value)
{
    for (MessageRFIDBody &el : body)
    {
        if (el.attributeType == RFIDAttributeTypes::CONFIG_VALUE)
        {
            (*value) = bufferToInt((unsigned char *)el.attributeValue.data());
            return 0;
        }
    }
    return -1;
}

/*!
 * \fn RFIDMessage::success
 * \return true if the message is a successfull response message, otherwise false.
 */
bool RFIDMessage::success()
{
    unsigned short value;
    int rc = getResultCode(&value);
    if (rc == 0 && value == RFIDResultCodes::OK)
    {
        return true;
    }
    return false;
}

/*!
 * \fn RFIDMessage::getResultCode
 * \param code a container, where the result code will be written into.
 * \return a result code. 0 = OK.
 */
int RFIDMessage::getResultCode(unsigned short *code)
{
    MessageRFIDBody &last = body.back();
    if(last.attributeType == RFIDAttributeTypes::RESULT_CODE)
    {
        (*code) = bufferToShort((unsigned char *)last.attributeValue.data());
        return 0;
    }
    return -1;
}

/*!
 * \fn RFIDMessage::print
 *
 * The method RFIDMessage::print prints the message structure on the screen. Useful for debug purposes.
 */
void RFIDMessage::print()
{
    printf("HEADER\n");
    printf("Version    : %04x\n", version);
    printf("Message ID : %04x\n", messageId);
    printf("Vendor     : %08x\n", vendor);
    printf("Length     : %04x\n", length);
    printf("\n");

    for (auto& el : body)
    {
        printf("Reserved   : %04x\n", el.reserved);
        printf("Length     : %04x\n", el.length);
        printf("Att. Type  : %04x\n", el.attributeType);

        printf("Att. Value : ");

        for (size_t i = 0; i < el.attributeValue.size(); i++)
        {
            printf("%02x ", el.attributeValue[i]);
            fflush(stdout);
        }

        printf("\n\n");
    }
}

/*!
 * \fn RFIDMessage::shortToBuffer
 * \param s
 * \param converted
 */
void RFIDMessage::shortToBuffer(unsigned short s, unsigned char *converted)
{
    converted[0] = (0xFF00 & s) >> 8;
    converted[1] = (0x00FF & s);
}

/*!
 * \fn RFIDMessage::intToBuffer
 * \param i
 * \param converted
 */
void RFIDMessage::intToBuffer(unsigned int i, unsigned char *converted)
{
    unsigned int mask = 0x000000FF;
    for (int j=0; j<4; j++){
        converted[3-j] = mask & i;
        i >>= 8;
    }
}

/*!
 * \fn RFIDMessage::longToBuffer
 * \param l
 * \param converted
 * \param len
 */
void RFIDMessage::longToBuffer(unsigned long l, unsigned char *converted, unsigned short len)
{
    unsigned long mask = 0xFF;
    for (int i=0; i<len; i++){
        converted[len-i] = mask & l;
        l >>= 8;
    }
}

/*!
 * \fn RFIDMessage::bufferToShort
 * \param buffer
 * \return
 */
unsigned short RFIDMessage::bufferToShort(unsigned char *buffer)
{
    return (buffer[0] << 8) + buffer[1];
}

/*!
 * \fn RFIDMessage::bufferToSignedShort
 * \param buffer
 * \return
 */
short RFIDMessage::bufferToSignedShort(unsigned char *buffer)
{
    return (buffer[0] << 8) + buffer[1];
}

/*!
 * \fn RFIDMessage::bufferToInt
 * \param buffer
 * \return
 */
unsigned int RFIDMessage::bufferToInt(unsigned char *buffer)
{
    unsigned int j=0;
    for (int i=0; i<4; i++){
        j <<= 8;
        j += buffer[i];
    }
    return j;
}

