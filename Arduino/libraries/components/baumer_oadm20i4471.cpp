#include "baumer_oadm20i4471.h"

BaumerOADM20I4471::BaumerOADM20I4471(uint8_t pin, uint8_t ID) : AnalogSensor(pin,ID) { }

float BaumerOADM20I4471::readCalibratedValue() {
  _calibrated_value = this->readRawValue() / 1023.0f * 0.5f; // 0-5V mapped to 1023 steps: 1023 == 0.5m
}
