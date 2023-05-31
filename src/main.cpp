#include <Arduino.h>
#include "BTFunctions.h"
#include "piano16bit.h"

void setup()
{
  Serial.begin(115200);
}

void loop()
{

  getCommand(0);
  // printf("nope0");

  switch (fCommand[0])
  {
  case 'l':
  {
    a2dp_source.set_ssid_callback(isValid);
    a2dp_source.set_local_name("ESP32 a2dp SOUrce");
    a2dp_source.set_discoverability(ESP_BT_GENERAL_DISCOVERABLE);
    a2dp_source.set_volume(20);
    break;
  }
  case 'k':
  {
    Serial.println(a2dp_source.get_connection_state());
    break;
  }
  case 'j':
  {
    a2dp_source.write_data(data);
    break;
  }
  case 'i':
  {
    a2dp_source.start("TSCO-TH5365TWS"); // TSCO-TH5365TWS
    a2dp_source.set_local_name("ESP32 a2dp SOUrce");
    a2dp_source.set_discoverability(ESP_BT_GENERAL_DISCOVERABLE);
    a2dp_source.set_volume(20);
    break;

    break;
  }
    // case 'h':
    // {
    //   BluetoothA2DPSource a2dp_SOurce;

    //   a2dp_SOurce.start("TSCO-TH5365TWS", get_data_frames);
    //   a2dp_SOurce.set_volume(30);
    //   break;
    // }

  case '2':
    Heap_Information();
    break;
  case 'b':
    Serial.println(heap_caps_get_largest_free_block(MALLOC_CAP_32BIT));
    Serial.println(heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

    Serial.println(heap_caps_get_free_size(MALLOC_CAP_32BIT));
    Serial.println(heap_caps_get_free_size(MALLOC_CAP_8BIT));
    heap_caps_dump(MALLOC_CAP_8BIT);
    heap_caps_dump(MALLOC_CAP_32BIT);

    Serial.println(heap_caps_check_integrity_all(1));

    break;
  }

  for (int i = 0; i < 256; i++)
    fCommand[i] = '0';
}
