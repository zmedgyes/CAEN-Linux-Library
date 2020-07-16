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
 * \fn RFIDDevice::parseRFID
 *
 * The auxiliary method RFIDDevice::parseRFID is used to parse an RFID object, generating a string.
 *
 * \param rfid the RFID to be parsed.
 * \return the RFID code in string format.
 */
char *RFIDDevice::parseRFID(RFID *rfid)
{
    char *str = new char[1024]();
    for (short i=0; i<rfid->length; i++){
        sprintf(str,"%s%02x:",str,rfid->rfid[i]);
    }
    str[strlen(str)-1] = '\0';
    return str;
}

/*!
 * \fn RFIDDevice::sendAndRecieve
 *
 * The method RFIDDevice::sendAndRecieve is used to send a message to the reader and waiting for the response.
 *
 * \param message the message with all the commands to send to the reader.
 * \return the message sent from the reader with the response.
 */
unique_ptr<RFIDMessage> RFIDDevice::sendAndRecieve(RFIDMessage *message)
{
    unsigned char *send = message->getBuffer();
    unsigned int sendLength = message->getLength();
    
    unsigned int bytesRead;
    bool messagePending = true;
    unsigned int pointer = 0;
    unsigned char header[10];
    unsigned char *received;
    unsigned short receivedLength;
    RFIDMessage *tmpMessage;

    serialDevice->send(send, sendLength);
    
    while(messagePending){
        if(pointer < 10){
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
            bytesRead = serialDevice->receive(&(received[pointer]),(receivedLength - pointer));
            pointer += bytesRead;
            if(pointer >= receivedLength){
                messagePending = false;
            }
        }
    }
    unique_ptr<RFIDMessage> msgOut = make_unique<RFIDMessage>(received, receivedLength);
    delete[] received;

    return move(msgOut);    
}

/*!
 * \fn RFIDDevice::getAntennaStatus
 *
 * The method RFIDDevice::getAntennaStatus requests the status of the \a source antenna.
 *
 * \param source name of the antenna.
 * \param len length of the name.
 * \param id message id.
 * \return a message with the status of the antenna.
 */
unique_ptr<RFIDMessage> RFIDDevice::getAntennaStatus(unsigned char *source, unsigned short len)
{
    RFIDMessage msgCheckAntenna(getNextId());
    msgCheckAntenna.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::CHECK_READ_POINT_STATUS);
    msgCheckAntenna.addCommand(RFIDAttributeTypes::READ_POINT_NAME, source, len);
    return sendAndRecieve(&msgCheckAntenna);
}

/*!
 * \fn RFIDDevice::getPower
 *
 * The method RFIDDevice::getPower returns the acqual power level (19-199) of the reader.
 *
 * \param id message id.
 * \return a message with the acqual value.
 */
unique_ptr<RFIDMessage> RFIDDevice::getPower()
{
    RFIDMessage msgGetPower(getNextId());
    msgGetPower.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::GET_POWER);
    return sendAndRecieve(&msgGetPower);
}

/*!
 * \fn RFIDDevice::setPower
 *
 * The method RFIDDevice::setPower changes the power level of the reader to a new value between 19mW and 199mW.
 *
 * \param powerLevel the new value.
 * \param id message id.
 * \return a message with the success status.
 */
unique_ptr<RFIDMessage> RFIDDevice::setPower(unsigned int powerLevel)
{
    RFIDMessage msgSetPower(getNextId());
    msgSetPower.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::SET_POWER);
    msgSetPower.addCommand(RFIDAttributeTypes::POWER_SET, powerLevel);
    return sendAndRecieve(&msgSetPower);
}

/*!
 * \fn RFIDDevice::setProtocol
 *
 * The method RFIDDevice::setProtocol changes the acqual communication protocol.
 *
 * \param protocol the new protocol.
 * \param id message id.
 * \return a message with the success status.
 */
unique_ptr<RFIDMessage> RFIDDevice::setProtocol(unsigned int protocol)
{
    RFIDMessage msgSetProtocol(getNextId());
    msgSetProtocol.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::SET_PROTOCOL);
    msgSetProtocol.addCommand(RFIDAttributeTypes::PROTOCOL, protocol);
    return sendAndRecieve(&msgSetProtocol);
}

/*!
 * \fn RFIDDevice::getProtocol
 *
 * The method RFIDDevice::getProtocol returns the acquatl used protocl.
 *
 * \param id message id.
 * \return a message with the protocol name.
 */
unique_ptr<RFIDMessage> RFIDDevice::getProtocol()
{
    RFIDMessage msgGetProtocol(getNextId());
    msgGetProtocol.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::GET_PROTOCOL);
    return sendAndRecieve(&msgGetProtocol);
}

/*!
 * \fn RFIDDevice::inventory
 *
 * The method RFIDDevice::inventory performs an inventory scan and returns all the found RFID ids.
 *
 * \param source antenna name to be used.
 * \param len length of \a source param.
 * \param id message id.
 * \return a message with all the founds RFID ids.
 */
unique_ptr<RFIDMessage> RFIDDevice::inventory(unsigned char *source, unsigned short len)
{
    RFIDMessage msgInventory(getNextId());
    msgInventory.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::INVENTORY_TAG);
    msgInventory.addCommand(RFIDAttributeTypes::SOURCE_NAME, source, len);
    return sendAndRecieve(&msgInventory);
}

unique_ptr<RFIDMessage> RFIDDevice::inventory(unsigned char *source, unsigned short source_len, unsigned char *mask, unsigned short mask_len, unsigned short mask_pos, unsigned short flags)
{
    RFIDMessage msgInventory(getNextId());
    msgInventory.addCommand(RFIDAttributeTypes::COMMAND_NAME, RFIDCommandsCodes::INVENTORY_TAG);
    msgInventory.addCommand(RFIDAttributeTypes::SOURCE_NAME, source, source_len);
    msgInventory.addCommand(RFIDAttributeTypes::LENGTH, mask_len);
    msgInventory.addCommand(RFIDAttributeTypes::TAG_ID_MASK, mask, mask_len);
    msgInventory.addCommand(RFIDAttributeTypes::TAG_ID_MASK_POS, mask_pos);
    msgInventory.addCommand(RFIDAttributeTypes::INVENTORY_FLAGS, flags);
    return sendAndRecieve(&msgInventory);
}

unsigned short RFIDDevice::getNextId()
{
    this->id++;
    return this->id;
}
