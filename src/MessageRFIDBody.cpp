#include "MessageRFIDBody.h"

/*!
 * \fn MessageRFIDBody::MessageRFIDBody
 *
 * Constructs a messsage body item from received data sent by the reader.
 *
 * \param reserved a reserved field
 * \param type the type of the item. Described in RFIDAttributeTypes.h
 * \param value the value content of the item.
 * \param len the complete(!!!) size of the item. (reserved+type+len+value included = 6byte + value length)
 */
MessageRFIDBody::MessageRFIDBody(unsigned short reserved, unsigned short type, unsigned char *value, unsigned short len)
    : reserved(reserved), length(len), attributeType(type), attributeValue((char *)value, (len - 6))
{
}

/*!
 * \fn MessageRFIDBody::MessageRFIDBody
 *
 * Constructs a messsage body item for a command to be sent.
 *
 * \param type the type of the item. Described in RFIDAttributeTypes.h
 * \param value the value content of the item.
 * \param len the length of the value(!!!) content only.
 */
MessageRFIDBody::MessageRFIDBody(unsigned short type, unsigned char *value, unsigned short len)
    : MessageRFIDBody(0x0000,type,value, len+6)
{
}