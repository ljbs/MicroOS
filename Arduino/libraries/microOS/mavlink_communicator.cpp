#include "mavlink_communicator.h"

MavlinkCommunicator::MavlinkCommunicator(const uint8_t id, const uint8_t type, HALBase *hal) : _hal(hal), _id(id), _type(type),
#ifdef SINGLE_CHANNEL
  _channels({Channel(hal->getPrimarySerial(), new MavlinkProtocol)})
#else
  _channels({Channel(hal->getPrimarySerial(), new MavlinkProtocol),
         Channel(hal->getSecondarySerial(), new MavlinkProtocol)})
#endif
{
  //do nothing
}

void MavlinkCommunicator::init() {
  for(uint8_t k=0;k<NUMBER_OF_CHANNELS;k++){
    _channels[k].start();
  }
}

void MavlinkCommunicator::receive() {
  for(uint8_t k=0;k<NUMBER_OF_CHANNELS;k++){
    while(_channels[k].receive()){
      handleMessage(*reinterpret_cast<mavlink_message_t*>(_channels[k].getMessage()));
    }
  }
}

void MavlinkCommunicator::sendMessage(mavlink_message_t &msg) {
  for(uint8_t k=0;k<NUMBER_OF_CHANNELS;k++){
    _channels[k].send(&msg);
  }
}

void MavlinkCommunicator::sendHeartbeat() {
  mavlink_message_t msg;
  uint8_t data[8];
  mavlink_msg_heartbeat_pack(_id, 0, &msg, _type, millis(), data);

  sendMessage(msg);
}

void MavlinkCommunicator::sendThreadInfo(uint8_t ID, uint8_t priority, uint32_t duration, uint32_t latency, uint32_t total_duration, uint32_t total_latency, uint32_t number_of_executions) {
  mavlink_message_t msg;
  mavlink_msg_thread_info_pack(_id, 0, &msg, millis(), ID, priority, duration, latency, total_duration, total_latency, number_of_executions);

  sendMessage(msg);
}

#ifdef MICROOS_SLIM
void MavlinkCommunicator::transmit() {
  sendSlimIO();
}

void MavlinkCommunicator::sendSlimIO() {
  mavlink_message_t msg;
  mavlink_slim_io_t slim;

  unsigned int k;
  slim.time = millis();
  for(k=0; k<4; k++) slim.io[k] = System.getGPoutFloat(k);

  mavlink_msg_slim_io_encode(_id, 0, &msg, &slim);

  sendMessage(msg);
}
#else
void MavlinkCommunicator::transmit() {
  sendGPIO();
}

void MavlinkCommunicator::sendGPIO() {
  mavlink_message_t msg;
  mavlink_gpio_t gpio;

  unsigned int k;
  gpio.time = millis();
  for(k=0;k<4;k++)
    gpio.gpio_int[k] = System.getGPoutInt(k);
  for(k=0;k<8;k++)
    gpio.gpio_float[k] = System.getGPoutFloat(k);

  mavlink_msg_gpio_encode(_id, 0, &msg, &gpio);

  sendMessage(msg);
}

void MavlinkCommunicator::sendEvent(uint16_t event) {
  mavlink_message_t msg;
  mavlink_msg_event_pack(_id, 0, &msg,  event);

  sendMessage(msg);
}

void MavlinkCommunicator::handleEvent(uint16_t event) {
  //put some microOS related events here
  switch(event) {
      case 100: {
            System.sendAllParameters();
            break; }
        case 101: {
            System.storeAllParameters();
            break; }
  }
}

void MavlinkCommunicator::handlePartition(const mavlink_partition_t &partition) {
  //System.println("Partition message decoded.");
}

void MavlinkCommunicator::sendPrint(const char *text) {
  mavlink_message_t msg;
  mavlink_msg_print_pack(_id, 0, &msg, text);

  sendMessage(msg);
}

void MavlinkCommunicator::sendIntParam(const String& name, const uint16_t offset, const int32_t value) {
    mavlink_message_t msg;
    char name_[8];
    name.toCharArray(name_,8);
    mavlink_msg_param_int_pack(_id, 0, &msg, 0, offset, name_, value);

    sendMessage(msg);
}

void MavlinkCommunicator::sendFloatParam(const String& name, const uint16_t offset, const float value) {
    mavlink_message_t msg;
    char name_[8];
    name.toCharArray(name_,8);
    mavlink_msg_param_float_pack(_id, 0, &msg, 0, offset, name_, value);

    sendMessage(msg);
}
#endif

bool MavlinkCommunicator::handleMessage(mavlink_message_t &msg) {
  //System.println(msg.msgid);
#ifdef MICROOS_SLIM
  switch(msg.msgid) {
    case MAVLINK_MSG_ID_SLIM_IO: {
      mavlink_slim_io_t slim;
      mavlink_msg_slim_io_decode(&msg, &slim);
      for(size_t k = 0; k < 4; k++) System.setGPinFloat(k, slim.io[k]);
      break;
    }
    default:
      return false;
  }
#else
  switch(msg.msgid) {
    case MAVLINK_MSG_ID_GPIO:{
      mavlink_gpio_t gpio;
      mavlink_msg_gpio_decode(&msg,&gpio);

      unsigned int k;
      for(k=0;k<4;k++)
        System.setGPinInt(k,gpio.gpio_int[k]);
      for(k=0;k<8;k++)
        System.setGPinFloat(k,gpio.gpio_float[k]);
      //memcpy(System.getGPinInt(),gpio.gpio_int,16); //4*4bytes
      //memcpy(System.getGPinFloat(),gpio.gpio_float,32); //4*4bytes

      //System.println("Received gpio message.");
      break;}

    case MAVLINK_MSG_ID_EVENT:{
      mavlink_event_t event;
      mavlink_msg_event_decode(&msg,&event);

      handleEvent(event.type);
      break;}

    case MAVLINK_MSG_ID_PARTITION:{
      mavlink_partition_t partition;
      mavlink_msg_partition_decode(&msg,&partition);

      handlePartition(partition);
      break;}

        case MAVLINK_MSG_ID_PARAM_INT:{
            mavlink_param_int_t param_int;
            mavlink_msg_param_int_decode(&msg,&param_int);
            System.intStorage()->setValue(param_int.name, param_int.value);
            break;}

        case MAVLINK_MSG_ID_PARAM_FLOAT:{
            mavlink_param_float_t param_float;
            mavlink_msg_param_float_decode(&msg,&param_float);
            System.floatStorage()->setValue(param_float.name, param_float.value);
            break;}

    /*case INTERESTING_MSG_ID:{
      //do something with the message
      break; }

    case LESS_INTERESTING_MSG_ID:{
      //do something with the message
      break; }*/

    default:
      return false;
  }
#endif

  return true;
}
