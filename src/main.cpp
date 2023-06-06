#include <Arduino.h>
#include "BTFunctions.h"
#include "piano16bit.h"
#include "BluetoothA2DPCommon.h"
#include <BluetoothSerial.h>

esp_bd_addr_t *lPeer;
// esp_bd_addr_t tsco = {0xad, 0x8f, 0xe7, 0xb7, 0x60, 0xc1};
// esp_bd_addr_t bluM = {0x4d, 0x01, 0xb5, 0x3b, 0xa8, 0x66};

// ad:8f:e7:b7:60:c1  tsco
// 4d:01:b5:3b:a8:66  bluetooth music

void setup()
{
  Serial.begin(115200);
  a2dp_source.set_local_name("ESP32 a2dp SOUrce");
  a2dp_source.set_discoverability(ESP_BT_GENERAL_DISCOVERABLE);
  a2dp_source.start(); // TSCO-TH5365TWS
  a2dp_source.set_volume(30);
  vTaskDelay(200 / portTICK_PERIOD_MS);
  // a2dp_source.disconnect();
}

void loop()
{

  getCommand(0);
  // printf("nope0");

  switch (fCommand[0])
  {

  case 'X':                //    only use if you are not going to use bluetooth in the current boot/session.
    a2dp_source.end(true); //    if .end() is used, you cannot use bluetooth without rebooting microcontroller
    break;
  case '6':
    a2dp_source.reconnect();
    break;

  case '5':
  {
    lPeer = a2dp_source.get_last_peer_address();
    // memcpy(tsco, *lPeer, sizeof(*lPeer));

    const char *s = a2dp_source.to_str(*lPeer);
    // SS = s;
    Serial.println(s);
    break;
  }
  case 'd': // disconnect

    a2dp_source.disconnect();
    break;

  case 'L':
    a2dp_source.set_ssid_callback(doNothing); // Remove SSID Callback
    break;

  case 'l':
    a2dp_source.set_ssid_callback(isValid); // submit SSID Callback
    break;

  case '4':
    a2dp_source.write_data(data);
    break;

  case '3':
    Serial.println(a2dp_source.get_connection_state());
    break;

  case '2': //  Bluetooth Music
  {
    esp_bd_addr_t bda = {0x4d, 0x01, 0xb5, 0x3b, 0xa8, 0x66};
    a2dp_source.connect_to(bda);
    a2dp_source.set_volume(50);
    break;
  }

  case '1': //  TSCO-TH5365TWS
  {
    esp_bd_addr_t bda = {0xad, 0x8f, 0xe7, 0xb7, 0x60, 0xc1};
    a2dp_source.connect_to(bda);
    a2dp_source.set_volume(30);
    break;
  }

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

  case 'H':
    Heap_Information();
    break;
  case 'h':
    Serial.println(heap_caps_get_largest_free_block(MALLOC_CAP_32BIT));
    Serial.println(heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

    Serial.println(heap_caps_get_free_size(MALLOC_CAP_32BIT));
    Serial.println(heap_caps_get_free_size(MALLOC_CAP_8BIT));
    // heap_caps_dump(MALLOC_CAP_8BIT);
    // heap_caps_dump(MALLOC_CAP_32BIT);

    Serial.println(heap_caps_check_integrity_all(1));

    break;
  }

  for (int i = 0; i < 256; i++)
    fCommand[i] = '0';
}