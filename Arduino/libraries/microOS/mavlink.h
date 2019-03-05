#define MAVLINK_MAX_PAYLOAD_LEN		128
#define MAVLINK_COMM_NUM_BUFFERS	1

#ifdef MICROOS_LIGHT

#else
#include "./mavlink/microos_messages/mavlink.h"
#end
