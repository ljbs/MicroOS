#ifndef BAUMER_OADM20I4471_H
#define BAUMER_OADM20I4471_H

#include "analog_sensor.h"

class BaumerOADM20I4471: public AnalogSensor {
public:
  BaumerOADM20I4471(uint8_t pin, uint8_t ID = 0);

  float readCalibratedValue();
};

#endif // BAUMER_OADM20I4471_H
