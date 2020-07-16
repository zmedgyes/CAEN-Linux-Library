#include "RFIDMessage.h"

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
RFIDMessage::RFIDMessage(unsigned char *buffer, unsigned int messageLength)
{
    // cut the header
    version = bufferToShort(&buffer[HEAD_START]);
    messageId = bufferToShort(&buffer[MESSAGE_ID]);
    vendor = bufferToInt(&buffer[VENDOR_ID]);
    length = bufferToShort(&buffer[MSG_LENGTH]);
    valid = true;

    unsigned int position = 10;

    // process the bodies
    
    while (position < messageLength){
        short reserved = bufferToShort(&buffer[position]);
        short length = bufferToShort(&buffer[position +2]);
        short attributeType = bufferToShort(&buffer[position +4]);
        body.push_back(make_unique<MessageRFIDBody>(reserved, attributeType, &buffer[position + 6], length));
        position += length;
    }
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
    if (len == 0)
    {
        return -1;
    }

    unique_ptr<MessageRFIDBody> up_mbody = MessageRFIDBody::CreateCommand(type, value, len);

    length += up_mbody->length;

    body.push_back(move(up_mbody));

    return 0;
}

/*!
 * \fn RFIDMessage::getBuffer
 * \return the message in buffer format, ready to be used with the a serial device.
 */
unsigned char *RFIDMessage::getBuffer()
{
    unsigned char *buffer = new unsigned char[length]();
    unsigned int index = 10;

    /* header */
    shortToBuffer(version, &buffer[0]);
    shortToBuffer(messageId, &buffer[2]);
    intToBuffer(vendor, &buffer[4]);
    shortToBuffer(length, &buffer[8]);

    /* body */
    for (auto& temp : body)
    {

        shortToBuffer(temp->reserved, &buffer[index]);
        index += 2;
        shortToBuffer(temp->length, &buffer[index]);
        index += 2;
        shortToBuffer(temp->attributeType, &buffer[index]);
        index += 2;

        for (int i = 0; i < temp->attributeValueLength; i++)
        {
            buffer[index] = temp->attributeValue[i];
            index++;
        }
    }

    return buffer;
}

/*!
 * \fn RFIDMessage::getLength
 * \return the length of the whole message.
 */
unsigned short RFIDMessage::getLength()
{
    return length;
}

bool RFIDMessage::isValid()
{
    return valid;
}

    /*!
 * \fn RFIDMessage::getRFIDs
 * \return all the RFIDs founds in the message.
 */
void RFIDMessage::getRFIDs(vector<unique_ptr<RFID>> *founds)
{
    if(valid){
        this->print();
    }
    for(auto& p_el : body)
    {
        unsigned short tempLength;
        unsigned char *tempValue;
        if (p_el->attributeType == RFIDAttributeTypes::TAG_ID_LEN){
            tempLength = bufferToShort(p_el->attributeValue);
        }
        if (p_el->attributeType == RFIDAttributeTypes::TAG_ID){
            tempValue = p_el->attributeValue;
            founds->push_back(make_unique<RFID>(tempValue, tempLength));
        }
    }
}

/*!
 * \fn RFIDMessage::success
 * \return true if the message is a successfull response message, otherwise false.
 */
bool RFIDMessage::success()
{
    auto pp_last = body.end();
    if ((*pp_last)->attributeType == RFIDAttributeTypes::RESULT_CODE && (*pp_last)->attributeValue == RFIDCommandsCodes::SUCCESS){
        return true;
    }
    return false;
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

    for (auto& p_el : body)
    {
        printf("Reserved   : %04x\n", p_el->reserved);
        printf("Length     : %04x\n", p_el->length);
        printf("Att. Type  : %04x\n", p_el->attributeType);

        printf("Att. Value : ");

        for (int i = 0; i < p_el->attributeValueLength; i++)
        {
            printf("%02x ", p_el->attributeValue[i]);
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

