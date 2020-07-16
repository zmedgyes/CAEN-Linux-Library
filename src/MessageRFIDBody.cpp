#include "MessageRFIDBody.h"

MessageRFIDBody::MessageRFIDBody(unsigned short reserved, unsigned short type, unsigned char *value, unsigned short len)
{
    this->reserved = reserved;
    this->attributeType = type;
    this->length = len;

    this->attributeValueLength = this->length - 6;

    this->attributeValue = new unsigned char[this->attributeValueLength];
    memcpy(this->attributeValue, value, this->attributeValueLength);
}

MessageRFIDBody::~MessageRFIDBody()
{
    delete[] this->attributeValue;
}

unique_ptr<MessageRFIDBody> MessageRFIDBody::CreateCommand(unsigned short type, unsigned char *value, unsigned short len)
{
    return unique_ptr<MessageRFIDBody>(new MessageRFIDBody(0,type,value,len+6));
}