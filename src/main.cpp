#include <Arduino.h>
#include "BTFunctions.h"
#include "piano16bit.h"
#include "BluetoothA2DPCommon.h"
esp_bd_addr_t *lPeer;
esp_bd_addr_t tsco ={0xad,0x8f,0xe7,0xb7,0x60,0xc1};
// ad:8f:e7:b7:60:c1

void setup()
{
  Serial.begin(115200);
  a2dp_source.set_local_name("ESP32 a2dp SOUrce");
  a2dp_source.set_discoverability(ESP_BT_GENERAL_DISCOVERABLE);
  a2dp_source.set_volume(30);
}

void loop()
{

  getCommand(0);
  // printf("nope0");

  switch (fCommand[0])
  {
  case 'y':
  {
    a2dp_source.connect_to(tsco);
    break;
  }
  case 'x':
  {
    lPeer = a2dp_source.get_last_peer_address();
    const char *s = a2dp_source.to_str(*lPeer);
    // SS = s;
    Serial.println(s);
    break;
  }
  case 'd':

    a2dp_source.end(true);
    break;

  case 'l':

    a2dp_source.set_ssid_callback(isValid); // Activate SSID Callback
    break;

  case 'L':
    a2dp_source.set_ssid_callback(doNothing); // Remove SSID Callback
    break;

  case 'k':

    Serial.println(a2dp_source.get_connection_state());
    break;

  case 'j':

    a2dp_source.write_data(data);
    break;

  case 'm':

    a2dp_source.start("TSCO-TH5365TWS"); // TSCO-TH5365TWS
    a2dp_source.set_volume(30);

    break;

  case 'n':

    a2dp_source.start("Bluetooth Music"); // TSCO-TH5365TWS
    a2dp_source.set_volume(30);

    break;

  case 'o':

    a2dp_source.start("S530"); // TSCO-TH5365TWS
    a2dp_source.set_volume(30);

    break;
  case 'p':
    a2dp_source.start(""); // TSCO-TH5365TWS
    a2dp_source.set_volume(30);

    break;
  case 'i':

    a2dp_source.set_local_name("ESP32 a2dp SOUrce");
    a2dp_source.set_discoverability(ESP_BT_GENERAL_DISCOVERABLE);
    break;

  case 'v': /////           set volume
  {
    int a = 1;
    while (a)
    {
      if (Serial.available())
      {

        uint8_t v = Serial.parseInt();
        a2dp_source.set_volume(v);
        a = 0;
      }
    }
    break;
  }

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
