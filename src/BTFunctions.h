#ifndef BTFUNCTIONS_H
#define BTFUNCTIONS_H

#include "Arduino.h"
#include "BluetoothA2DPSource.h"
#include "piano16bit.h"
#include <math.h>

#include "stdlib.h"

extern float c3_frequency;
extern char fCommand[256];
extern BluetoothA2DPSource a2dp_source;
extern SoundData *data ;


extern bool getCommand(uint8_t num);

extern bool isValid(const char *SSID, esp_bd_addr_t address, int rssi);
extern int32_t get_data_frames(Frame *frame, int32_t frame_count);
extern void Heap_Information(void);



#endif