#pragma once
// MESSAGE SLIM_IO PACKING

#define MAVLINK_MSG_ID_SLIM_IO 2

MAVPACKED(
typedef struct __mavlink_slim_io_t {
 uint32_t time; /*<  Time at which the message was sent.*/
 float io[4]; /*<  4 gpio floating point values.*/
}) mavlink_slim_io_t;

#define MAVLINK_MSG_ID_SLIM_IO_LEN 20
#define MAVLINK_MSG_ID_SLIM_IO_MIN_LEN 20
#define MAVLINK_MSG_ID_2_LEN 20
#define MAVLINK_MSG_ID_2_MIN_LEN 20

#define MAVLINK_MSG_ID_SLIM_IO_CRC 8
#define MAVLINK_MSG_ID_2_CRC 8

#define MAVLINK_MSG_SLIM_IO_FIELD_IO_LEN 4

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SLIM_IO { \
    2, \
    "SLIM_IO", \
    2, \
    {  { "time", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_slim_io_t, time) }, \
         { "io", NULL, MAVLINK_TYPE_FLOAT, 4, 4, offsetof(mavlink_slim_io_t, io) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SLIM_IO { \
    "SLIM_IO", \
    2, \
    {  { "time", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_slim_io_t, time) }, \
         { "io", NULL, MAVLINK_TYPE_FLOAT, 4, 4, offsetof(mavlink_slim_io_t, io) }, \
         } \
}
#endif

/**
 * @brief Pack a slim_io message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param time  Time at which the message was sent.
 * @param io  4 gpio floating point values.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_slim_io_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t time, const float *io)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SLIM_IO_LEN];
    _mav_put_uint32_t(buf, 0, time);
    _mav_put_float_array(buf, 4, io, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SLIM_IO_LEN);
#else
    mavlink_slim_io_t packet;
    packet.time = time;
    mav_array_memcpy(packet.io, io, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SLIM_IO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SLIM_IO;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SLIM_IO_MIN_LEN, MAVLINK_MSG_ID_SLIM_IO_LEN, MAVLINK_MSG_ID_SLIM_IO_CRC);
}

/**
 * @brief Pack a slim_io message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param time  Time at which the message was sent.
 * @param io  4 gpio floating point values.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_slim_io_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t time,const float *io)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SLIM_IO_LEN];
    _mav_put_uint32_t(buf, 0, time);
    _mav_put_float_array(buf, 4, io, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SLIM_IO_LEN);
#else
    mavlink_slim_io_t packet;
    packet.time = time;
    mav_array_memcpy(packet.io, io, sizeof(float)*4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SLIM_IO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SLIM_IO;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SLIM_IO_MIN_LEN, MAVLINK_MSG_ID_SLIM_IO_LEN, MAVLINK_MSG_ID_SLIM_IO_CRC);
}

/**
 * @brief Encode a slim_io struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param slim_io C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_slim_io_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_slim_io_t* slim_io)
{
    return mavlink_msg_slim_io_pack(system_id, component_id, msg, slim_io->time, slim_io->io);
}

/**
 * @brief Encode a slim_io struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param slim_io C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_slim_io_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_slim_io_t* slim_io)
{
    return mavlink_msg_slim_io_pack_chan(system_id, component_id, chan, msg, slim_io->time, slim_io->io);
}

/**
 * @brief Send a slim_io message
 * @param chan MAVLink channel to send the message
 *
 * @param time  Time at which the message was sent.
 * @param io  4 gpio floating point values.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_slim_io_send(mavlink_channel_t chan, uint32_t time, const float *io)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SLIM_IO_LEN];
    _mav_put_uint32_t(buf, 0, time);
    _mav_put_float_array(buf, 4, io, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SLIM_IO, buf, MAVLINK_MSG_ID_SLIM_IO_MIN_LEN, MAVLINK_MSG_ID_SLIM_IO_LEN, MAVLINK_MSG_ID_SLIM_IO_CRC);
#else
    mavlink_slim_io_t packet;
    packet.time = time;
    mav_array_memcpy(packet.io, io, sizeof(float)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SLIM_IO, (const char *)&packet, MAVLINK_MSG_ID_SLIM_IO_MIN_LEN, MAVLINK_MSG_ID_SLIM_IO_LEN, MAVLINK_MSG_ID_SLIM_IO_CRC);
#endif
}

/**
 * @brief Send a slim_io message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_slim_io_send_struct(mavlink_channel_t chan, const mavlink_slim_io_t* slim_io)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_slim_io_send(chan, slim_io->time, slim_io->io);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SLIM_IO, (const char *)slim_io, MAVLINK_MSG_ID_SLIM_IO_MIN_LEN, MAVLINK_MSG_ID_SLIM_IO_LEN, MAVLINK_MSG_ID_SLIM_IO_CRC);
#endif
}

#if MAVLINK_MSG_ID_SLIM_IO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_slim_io_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t time, const float *io)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, time);
    _mav_put_float_array(buf, 4, io, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SLIM_IO, buf, MAVLINK_MSG_ID_SLIM_IO_MIN_LEN, MAVLINK_MSG_ID_SLIM_IO_LEN, MAVLINK_MSG_ID_SLIM_IO_CRC);
#else
    mavlink_slim_io_t *packet = (mavlink_slim_io_t *)msgbuf;
    packet->time = time;
    mav_array_memcpy(packet->io, io, sizeof(float)*4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SLIM_IO, (const char *)packet, MAVLINK_MSG_ID_SLIM_IO_MIN_LEN, MAVLINK_MSG_ID_SLIM_IO_LEN, MAVLINK_MSG_ID_SLIM_IO_CRC);
#endif
}
#endif

#endif

// MESSAGE SLIM_IO UNPACKING


/**
 * @brief Get field time from slim_io message
 *
 * @return  Time at which the message was sent.
 */
static inline uint32_t mavlink_msg_slim_io_get_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field io from slim_io message
 *
 * @return  4 gpio floating point values.
 */
static inline uint16_t mavlink_msg_slim_io_get_io(const mavlink_message_t* msg, float *io)
{
    return _MAV_RETURN_float_array(msg, io, 4,  4);
}

/**
 * @brief Decode a slim_io message into a struct
 *
 * @param msg The message to decode
 * @param slim_io C-struct to decode the message contents into
 */
static inline void mavlink_msg_slim_io_decode(const mavlink_message_t* msg, mavlink_slim_io_t* slim_io)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    slim_io->time = mavlink_msg_slim_io_get_time(msg);
    mavlink_msg_slim_io_get_io(msg, slim_io->io);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SLIM_IO_LEN? msg->len : MAVLINK_MSG_ID_SLIM_IO_LEN;
        memset(slim_io, 0, MAVLINK_MSG_ID_SLIM_IO_LEN);
    memcpy(slim_io, _MAV_PAYLOAD(msg), len);
#endif
}
