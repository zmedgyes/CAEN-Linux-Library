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
int RFIDDevice::sendAndRecieve(RFIDMessage *tosend, RFIDMessage *result)
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
 * \fn RFIDDevice::getReaderInfo
 *
 * The method RFIDDevice::getReaderInfo requests product name and serial no. information of the RFID reader.
 *
 * \param result a message where the antenna status will be written into.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::getReaderInfo(RFIDMessage *result)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::GET_READER_INFO);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::getFirmwareVersion
 *
 * The method RFIDDevice::getFirmwareVersion requests the current firmware version of tthe RFID reader.
 *
 * \param result a message where the antenna status will be written into.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::getFirmwareVersion(RFIDMessage *result)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::GET_FIRMWARE_RELEASE);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::getReadPointStatus
 *
 * The method RFIDDevice::getReadPointStatus requests the status of the \a read_point antenna.
 *
 * \param result a message where the antenna status will be written into.
 * \param read_point the name of the antenna.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::getReadPointStatus(RFIDMessage *result, string *read_point)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::CHECK_READ_POINT_STATUS);
    msgCommand.addCommand(RFIDAttributeTypes::READ_POINT_NAME, (unsigned char *)read_point->c_str(), read_point->size() + 1);
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
int RFIDDevice::getPower(RFIDMessage *result)
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
int RFIDDevice::setPower(RFIDMessage *result, unsigned int power_level)
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
int RFIDDevice::setProtocol(RFIDMessage *result, unsigned int protocol)
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
int RFIDDevice::getProtocol(RFIDMessage *result)
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
int RFIDDevice::inventory(RFIDMessage *result, string *source)
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
int RFIDDevice::inventory(RFIDMessage *result, string *source, string *mask, unsigned short mask_pos, unsigned short flags)
{
    unsigned short block_continous_function = ~(RFIDInventoryFlags::FRAMED | RFIDInventoryFlags::CONTINOUS | RFIDInventoryFlags::EVENT_TRIGGER);
    unsigned short local_flags = (flags & block_continous_function); //disable continous reading features
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::INVENTORY_TAG);
    msgCommand.addCommand(RFIDAttributeTypes::SOURCE_NAME, (unsigned char *)source->c_str(), source->size() + 1);
    msgCommand.addCommand(RFIDAttributeTypes::LENGTH, (unsigned short)mask->size());
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
int RFIDDevice::setSourceConfig(RFIDMessage *result, string *source, unsigned int param_id, unsigned int param_value)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::SET_SOURCE_CONFIG);
    msgCommand.addCommand(RFIDAttributeTypes::SOURCE_NAME, (unsigned char *)source->c_str(), source->size() + 1);
    msgCommand.addCommand(RFIDAttributeTypes::CONFIG_PARAMETER, param_id);
    msgCommand.addCommand(RFIDAttributeTypes::CONFIG_VALUE, param_value);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::getSourceConfig
 *
 * The method RFIDDevice::getSourceConfig gets a current value of the source configuration parameter.
 *
 * \param result a message where the success status will be written into.
 * \param source name of the source.
 * \param param_id ID of the parameter.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::getSourceConfig(RFIDMessage *result, string *source, unsigned int param_id)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::GET_SOURCE_CONFIG);
    msgCommand.addCommand(RFIDAttributeTypes::SOURCE_NAME, (unsigned char *)source->c_str(), source->size() + 1);
    msgCommand.addCommand(RFIDAttributeTypes::CONFIG_PARAMETER, param_id);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::getSourceQ
 *
 * The method RFIDDevice::getSourceQ gets current value of the Q anti-collision parameter of the source (related to the approximated number of tags to be read).
 *
 * \param result a message where the success status will be written into.
 * \param source name of the source.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::getSourceQ(RFIDMessage *result, string *source)
{
    return getSourceConfig(result, source, RFIDSourceConfigTypes::Q);
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
int RFIDDevice::setSourceQ(RFIDMessage *result, string *source, unsigned int value)
{
    return setSourceConfig(result, source, RFIDSourceConfigTypes::Q, value);
}

/*!
 * \fn RFIDDevice::getSourceSession
 *
 * The method RFIDDevice::getSourceSession gets the current session mode of the source in which it performs the reading cycles.
 *
 * \param result a message where the success status will be written into.
 * \param source name of the source.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::getSourceSession(RFIDMessage *result, string *source)
{
    return getSourceConfig(result, source, RFIDSourceConfigTypes::SESSION);
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
int RFIDDevice::setSourceSession(RFIDMessage *result, string *source, unsigned int value)
{
    return setSourceConfig(result, source, RFIDSourceConfigTypes::SESSION, value);
}

/*!
 * \fn RFIDDevice::getSourceTarget
 *
 * The method RFIDDevice::getSourceTarget gets the target mode of the source in which it performs the reading cycles.
 *
 * \param result a message where the success status will be written into.
 * \param source name of the source.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::getSourceTarget(RFIDMessage *result, string *source)
{
    return getSourceConfig(result, source, RFIDSourceConfigTypes::TARGET);
}

/*!
 * \fn RFIDDevice::setSourceTarget
 *
 * The method RFIDDevice::setSourceTarget sets the target (A/B) mode of the source in which it should perform the reading cycles.
 *
 * \param result a message where the success status will be written into.
 * \param source name of the source.
 * \param value new target mode.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::setSourceTarget(RFIDMessage *result, string *source, unsigned int value)
{
    return setSourceConfig(result, source, RFIDSourceConfigTypes::TARGET, value);
}

/*!
 * \fn RFIDDevice::readTagMemory
 *
 * The method RFIDDevice::readTagMemory reads the tag memory.
 * \note
 * The tag memory may only be read in words (2byte), but the addressing and datalength need to be given in bytes. Make sure both of the address and the length are even.
 * 
 * \param result a message where the success status will be written into.
 * \param source name of the source.
 * \param tagId the id of the target tag.
 * \param memory_bank the code of the target memory bank on the tag.
 * \param address the start position in the memory bank, where the new data will be read from.
 * \param length the length of the value to be read.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::readTagMemory(RFIDMessage *result, string *source, string *tagId, unsigned short memory_bank, unsigned short address, unsigned short length)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::READ_TAG_DATA_EPC_C1G2);
    msgCommand.addCommand(RFIDAttributeTypes::SOURCE_NAME, (unsigned char *)source->c_str(), source->size() + 1);
    msgCommand.addCommand(RFIDAttributeTypes::TAG_ID_LEN, (unsigned short)tagId->size());
    msgCommand.addCommand(RFIDAttributeTypes::TAG_ID, (unsigned char *)tagId->data(), tagId->size());
    msgCommand.addCommand(RFIDAttributeTypes::MEMORY_BANK, memory_bank);
    msgCommand.addCommand(RFIDAttributeTypes::TAG_ADDRESS, address);
    msgCommand.addCommand(RFIDAttributeTypes::LENGTH, length);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::writeTagMemory
 *
 * The method RFIDDevice::writeTagMemory writes the tag memory.
 * \note
 * The tag memory may only be written in words (2byte), but the addressing and datalength need to be given in bytes. Make sure both of the address and the length of the value are even.
 *
 * \param result a message where the success status will be written into.
 * \param source name of the source.
 * \param tagId the id of the target tag.
 * \param memory_bank the code of the target memory bank on the tag.
 * \param address the start position in the memory bank, where the new data will be written into.
 * \param value the new value to be set.
 * \param password the password of the tag 
 * \return a result code. 0 = OK.
 */
int RFIDDevice::writeTagMemory(RFIDMessage *result, string *source, string *tagId, unsigned short memory_bank, unsigned short address, string *value, string *password)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::WRITE_TAG_DATA_EPC_C1G2);
    msgCommand.addCommand(RFIDAttributeTypes::SOURCE_NAME, (unsigned char *)source->c_str(),source->size()+1);
    msgCommand.addCommand(RFIDAttributeTypes::TAG_ID_LEN,(unsigned short)tagId->size());
    msgCommand.addCommand(RFIDAttributeTypes::TAG_ID, (unsigned char *)tagId->data(), tagId->size());
    msgCommand.addCommand(RFIDAttributeTypes::MEMORY_BANK, memory_bank);
    msgCommand.addCommand(RFIDAttributeTypes::TAG_ADDRESS, address);
    msgCommand.addCommand(RFIDAttributeTypes::LENGTH,(unsigned short)value->size());
    msgCommand.addCommand(RFIDAttributeTypes::TAG_VALUE, (unsigned char *)value->data(), value->size());
    msgCommand.addCommand(RFIDAttributeTypes::G2_PASSWORD, (unsigned char *)password->data(), password->size());
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::setTagId
 *
 * The method RFIDDevice::setTagId sets a new Id to the tag memory.
 * \note
 * The tag memory may only be written in words (2byte), but the addressing and datalength need to be given in bytes. Make sure the length of the new tagId is even.
 *
 * \param result a message where the success status will be written into.
 * \param source name of the source.
 * \param oldTagId the current id of the target tag.
 * \param newTagId the new id of the target tag.
 * \param password the password of the tag 
 * \return a result code. 0 = OK.
 */
int RFIDDevice::setTagId(RFIDMessage *result, string *source, string *oldTagId, string *newTagId, string *password)
{
    int rc = writeTagMemory(result, source, oldTagId, RFIDMemoryBankCodes::EPC, 0x0004, newTagId, password);
    if(rc == 0 && result->success())
    {
        unsigned char set_epc_cmd[2];
        unsigned short epc_activate = 0x3000;
        //epc_activate calculation: (newTagId.size() == 12 => 0x3000)
        //epc_activate = ((newTagId.size() / 2) + (newTagId.size()%2)) << 11;
        RFIDMessage::shortToBuffer(epc_activate, set_epc_cmd);
        string cmd_value((char*) set_epc_cmd,2);
        rc = writeTagMemory(result, source, oldTagId, RFIDMemoryBankCodes::EPC, 0x0002, &cmd_value, password);
    }
    return rc;
}

/*!
 * \fn RFIDDevice::checkReadPointInSource
 *
 * The method RFIDDevice::checkReadPointInSource checks if the given read-point is assigned to the source.
 *
 * \param result a message where the success status will be written into.
 * \param read_point the name of the read-point.
 * \param source the name of the source.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::checkReadPointInSource(RFIDMessage *result, string *read_point, string *source)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::CHECK_READ_POINT_IN_SOURCE);
    msgCommand.addCommand(RFIDAttributeTypes::READ_POINT_NAME, (unsigned char *)read_point->c_str(), read_point->size() + 1);
    msgCommand.addCommand(RFIDAttributeTypes::SOURCE_NAME, (unsigned char *)source->c_str(), source->size() + 1);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::addReadPointToSource
 *
 * The method RFIDDevice::addReadPointToSource adds the read-point to the source.
 *
 * \param result a message where the success status will be written into.
 * \param read_point the name of the read-point.
 * \param source the name of the source.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::addReadPointToSource(RFIDMessage *result, string *read_point, string *source)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::ADD_READ_POINT_TO_SOURCE);
    msgCommand.addCommand(RFIDAttributeTypes::SOURCE_NAME, (unsigned char *)source->c_str(), source->size() + 1);
    msgCommand.addCommand(RFIDAttributeTypes::READ_POINT_NAME, (unsigned char *)read_point->c_str(), read_point->size() + 1);
    return sendAndRecieve(&msgCommand, result);
}

/*!
 * \fn RFIDDevice::removeReadPointFromSource
 *
 * The method RFIDDevice::removeReadPointFromSource removes the read-point from the source.
 *
 * \param result a message where the success status will be written into.
 * \param read_point the name of the read-point.
 * \param source the name of the source.
 * \return a result code. 0 = OK.
 */
int RFIDDevice::removeReadPointFromSource(RFIDMessage *result, string *read_point, string *source)
{
    RFIDMessage msgCommand(getNextId());
    msgCommand.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::REMOVE_READ_POINT_FROM_SOURCE);
    msgCommand.addCommand(RFIDAttributeTypes::SOURCE_NAME, (unsigned char *)source->c_str(), source->size() + 1);
    msgCommand.addCommand(RFIDAttributeTypes::READ_POINT_NAME, (unsigned char *)read_point->c_str(), read_point->size() + 1);
    return sendAndRecieve(&msgCommand, result);
}