#include "BTFunctions.h"

BluetoothA2DPSource a2dp_source;

SoundData *data = new OneChannelSoundData((int16_t *)piano16bit_raw, piano16bit_raw_len / 2);

float c3_frequency = 1000;
char fCommand[256];

bool getCommand(uint8_t num)
{
  if (Serial.available())
  {
    fCommand[num] = Serial.read();
    if (fCommand[num] == -1)
      return 0;
    else
    {
      Serial.print("got command"); //%c ->%c", num, fCommand[num]);
      Serial.print(num);
      // String s(2,fCommand[num]);
      Serial.println(fCommand[num]);

      return 1;
    }
  }
  else
    return 0;
}

void Heap_Information(void)
{
  // printf("Heap_Information:\n");
  // printf("\nHeap - size: %d - ", ESP.getHeapSize());
  // printf("Free: %d - ", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  // printf("Min Free: %d - ", heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT));
  // printf("Max Alloc: %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
  // multi_heap_info_t *info = NULL;
  // info = (multi_heap_info_t *)new (std::nothrow) multi_heap_info_t;
  multi_heap_info_t info;

// #define iiii (*info)
#define iiii info

  heap_caps_get_info(&info, MALLOC_CAP_INTERNAL);
  printf("Current HeapSize: %d\n", heap_caps_get_total_size(MALLOC_CAP_8BIT));
  printf("--------------------------------------------\n");
  printf("free_blocks: %d\n", iiii.free_blocks);
  printf("largest_free block: %d\n", iiii.largest_free_block);
  printf("minimum_free bytes: %d\n", iiii.minimum_free_bytes);
  printf("total_allocated bytes: %d\n", iiii.total_allocated_bytes);
  printf("total_blocks: %d\n", iiii.total_blocks);
  printf("total_free bytes: %d\n", iiii.total_free_bytes);
  printf("total_free + total_allocated bytes: %d\n", iiii.total_free_bytes + iiii.total_allocated_bytes);

  printf("--------------------------------------------\n");
  // delete info;

  // errFunc("Memory");
}
int32_t get_data_frames(Frame *frame, int32_t frame_count)
{
  static float m_time = 0.0;
  float m_amplitude = 10000.0; // -32,768 to 32,767
  float m_deltaTime = 1.0 / 44100.0;
  float m_phase = 0.0;
  float pi_2 = PI * 2.0;
  // fill the channel data
  for (int sample = 0; sample < frame_count; ++sample)
  {
    float angle = pi_2 * c3_frequency * m_time + m_phase;
    frame[sample].channel1 = m_amplitude * sin(angle);
    frame[sample].channel2 = frame[sample].channel1;
    m_time += m_deltaTime;
  }

  return frame_count;
}

bool isValid(const char *SSID, esp_bd_addr_t address, int rssi)
{
  Serial.print("available SSID: ");
  Serial.println(SSID);
  return false;
}
bool doNothing(const char *SSID, esp_bd_addr_t address, int rssi)
{
  return false;
}

uint16_t toHex(uint8_t *c)
{
  bool err = 0;
  uint8_t t[2];
  uint16_t a = 0;

  t[0] = *c;
  t[1] = *(c + 1);
  for (int i = 0; i < 2; i++)
  {
    if (t[i] >= '0' && t[i] <= '9')
      t[i] -= '0';

    else if (t[i] >= 'a' && t[i] <= 'f')
      t[i] -= 'a';

    else if (t[i] >= 'A' && t[i] <= 'F')
      t[i] -= 'A';
    else
      return 0;
  }

  a = (t[0]) * 16 + t[1];
  return a;
}
