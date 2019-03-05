#ifndef MAVLINK_SELECTOR_H
#define MAVLINK_SELECTOR_H

#define MAVLINK_MAX_PAYLOAD_LEN		128
#define MAVLINK_COMM_NUM_BUFFERS	1

#include "config.h"

#ifdef MICROOS_SLIM
#include "./mavlink/mavlink4matlab_messages/mavlink.h"
#else
#include "./mavlink/microos_messages/mavlink.h"
#endif

#endif // MAVLINK_SELECTOR_H
