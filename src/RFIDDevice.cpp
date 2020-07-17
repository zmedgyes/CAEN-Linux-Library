#include "RFIDDevice.h"

/*!
 * \fn RFIDDevice::RFIDDevice
 *
 * Constructs the RFIDDevice based on a serialDevice and a configurazion file.
 *
 * \param device the serialDevice used to contact the reader.
 */
RFIDDevice::RFIDDevice(SerialDevice *device)
{
    serialDevice = device;
    this->id = 0;
}

/*!
 * \fn RFIDDevice::~RFIDDevice
 *
 * Destructs the module.
 */
RFIDDevice::~RFIDDevice()
{}

/*!
 * \fn RFIDDevice::sendAndRecieve
 *
 * The method RFIDDevice::sendAndRecieve is used to send a message to the reader and waiting for the response.
 *
 * \param tosend the message with all the commands to send to the reader.
 * \param result the message sent from the reader with the response.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::sendAndRecieve(RFIDMessage* tosend, RFIDMessage* result)
{
    unsigned int bytesRead;
    bool messagePending = true;
    unsigned int pointer = 0;
    unsigned char header[10];
    unsigned char *received;
    unsigned short receivedLength;
    RFIDMessage *tmpMessage;

    unsigned short sendLength = tosend->getLength();
    unsigned char *send = new unsigned char[sendLength]; 
    tosend->getBuffer(send);
    
    serialDevice->send(send, sendLength);
    delete[] send;
    
    while(messagePending){
        if(pointer < 10){
            //printf("Header remaining: %d\n", (10-pointer));
            bytesRead = serialDevice->receive(&(header[pointer]), (10-pointer));
            pointer += bytesRead;
            if(pointer == 10){
                tmpMessage = new RFIDMessage(header,pointer);
                receivedLength = tmpMessage->getLength();
                received = new unsigned char[receivedLength];
                memcpy(received,header,pointer);
                delete tmpMessage;
            }
        }
        else{
            //printf("Data remaining: %d\n", (receivedLength - pointer));
            bytesRead = serialDevice->receive(&(received[pointer]),(receivedLength - pointer));
            pointer += bytesRead;
            if(pointer >= receivedLength){
                messagePending = false;
            }
        }
    }
    result->initFromBuffer(received,receivedLength);
    delete[] received;

    return 0;    
}

/*!
 * \fn RFIDDevice::getNextId
 *
 * The method RFIDDevice::getNextId gives back an auto-incremental message ID.
 *
 * \return a message id
 */
unsigned short RFIDDevice::getNextId()
{
    return id++;
}

/*!
 * \fn RFIDDevice::getSourceStatus
 *
 * The method RFIDDevice::getSourceStatus requests the status of the \a source antenna.
 *
 * \param result a message where the antenna status will be written into.
 * \param source the name of the antenna.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::getSourceStatus(RFIDMessage* result, string* source)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::CHECK_READ_POINT_STATUS);
    msgCommand.addCommand(RFIDAttributeTypes::READ_POINT_NAME, (unsigned char *)source->c_str(), source->size() + 1);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::getPower
 *
 * The method RFIDDevice::getPower returns the current power level of the reader (mW).
 *
 * \param result a message where the current power level will be written into.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::getPower(RFIDMessage* result)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::GET_POWER);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::setPower
 *
 * The method RFIDDevice::setPower changes the power level of the reader to a new value (mW).
 *
 * \param result a message where the success status will be written into.
 * \param power_level the new power level (mW).
 * \return a result code. 0 = OK.
 */
int RFIDDevice::setPower(RFIDMessage* result, unsigned int power_level)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::SET_POWER);
    msgCommand.addCommand(RFIDAttributeTypes::POWER_SET, power_level);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::setProtocol
 *
 * The method RFIDDevice::setProtocol changes the communication protocol.
 *
 * \param result a message where the success status will be written into.
 * \param protocol the new protocol.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::setProtocol(RFIDMessage* result, unsigned int protocol)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::SET_PROTOCOL);
    msgCommand.addCommand(RFIDAttributeTypes::PROTOCOL, protocol);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::getProtocol
 *
 * The method RFIDDevice::getProtocol returns the currently used protocol.
 *
 * \param result a message where the currently used protocol code will be written into.
 * \param source name of the source.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::getProtocol(RFIDMessage* result)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::GET_PROTOCOL);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::inventory
 *
 * The method RFIDDevice::inventory performs an inventory scan and returns all the found RFID tags.
 *
 * \param result a message where the infos of the found RFID tags will be written into.
 * \param source name of the source.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::inventory(RFIDMessage* result, string* source)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::INVENTORY_TAG);
    msgCommand.addCommand(RFIDAttributeTypes::SOURCE_NAME, (unsigned char *)source->c_str(), source->size() + 1);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::inventory
 *
 * The method RFIDDevice::inventory performs an inventory scan and returns all the found RFID tags.
 *
 * \param result a message where the infos of the found RFID tags will be written into.
 * \param source name of the source.
 * \param mask the bitmask to be used for filtering the tag IDs.
 * \param mask_pos the position where the mask should start the filtering.
 * \param flags flags describing which information should be included in the tag response.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::inventory(RFIDMessage* result, string* source, string* mask, unsigned short mask_pos, unsigned short flags)
{
    unsigned short local_flags = (flags & 0xFFD9); //disable continous reading features
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::INVENTORY_TAG);
    msgCommand.addCommand(RFIDAttributeTypes::SOURCE_NAME, (unsigned char *)source->c_str(), source->size() + 1);
    msgCommand.addCommand(RFIDAttributeTypes::LENGTH, mask->size());
    msgCommand.addCommand(RFIDAttributeTypes::TAG_ID_MASK, (unsigned char *)mask->data(), mask->size());
    msgCommand.addCommand(RFIDAttributeTypes::TAG_ID_MASK_POS, mask_pos);
    msgCommand.addCommand(RFIDAttributeTypes::INVENTORY_FLAGS, local_flags);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::setSourceConfig
 *
 * The method RFIDDevice::setSourceConfig sets a configuration parameter of the source to a presented value
 *
 * \param result a message where the success status will be written into.
 * \param source name of the source.
 * \param param_id ID of the parameter to be set.
 * \param param_value new parameter value.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::setSourceConfig(RFIDMessage* result, string* source, unsigned int param_id, unsigned int param_value)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::SET_SOURCE_CONFIG);
    msgCommand.addCommand(RFIDAttributeTypes::SOURCE_NAME, (unsigned char *)source->c_str(), source->size() + 1);
    msgCommand.addCommand(RFIDAttributeTypes::CONFIG_PARAMETER, param_id);
    msgCommand.addCommand(RFIDAttributeTypes::CONFIG_VALUE, param_value);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::setSourceQ
 *
 * The method RFIDDevice::setSourceQ sets the Q anti-collision parameter of the source (related to the approximated number of tags to be read).
 *
 * \param result a message where the success status will be written into.
 * \param source name of the source.
 * \param value new Q value.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::setSourceQ(RFIDMessage* result, string* source, unsigned int value)
{
    return setSourceConfig(result, source, RFIDSourceConfigTypes::Q, value);
}

/*!
 * \fn RFIDDevice::setSourceSession
 *
 * The method RFIDDevice::setSourceSession sets the session mode of the source in which it should perform the reading cycles.
 *
 * \param result a message where the success status will be written into.
 * \param source name of the source.
 * \param value new session mode.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::setSourceSession(RFIDMessage* result, string* source, unsigned int value)
{
    return setSourceConfig(result, source, RFIDSourceConfigTypes::SESSION, value);
}
