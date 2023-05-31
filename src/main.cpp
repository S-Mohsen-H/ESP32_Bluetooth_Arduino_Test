#include <Arduino.h>
#include "BTFunctions.h"
#include "piano16bit.h"
#include <BluetoothSerial.h>

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
  case 'd':
  {
    a2dp_source.disconnect();
    a2dp_source.end();
    break;
  }
  case 'l':
  {
    BluetoothSerial SerialBT;
    Serial.println("Starting discover...");
    BTScanResults *pResults = SerialBT.discover(10000);
    if (pResults)
      pResults->dump(&Serial);
    else
      Serial.println("Error on BT Scan, no result!");
  }
  // case 'L':
  //   a2dp_source.set_ssid_callback(isValid);
  //   break;
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
  case 'm':
  {
    a2dp_source.start("TSCO-TH5365TWS"); // TSCO-TH5365TWS
    break;
  }
  case 'n':
  {
    a2dp_source.start("Bluetooth Music"); // TSCO-TH5365TWS
    break;
  }
  case 'o':
  {
    esp_bd_addr_t s530 = {91, 79, 31, 126, 198, 200};
    a2dp_source.start("S530"); // TSCO-TH5365TWS
    break;
  }
  case 'y':
    a2dp_source.start("");
    break;
  case 'i':
  {
    a2dp_source.set_local_name("ESP32 a2dp SOUrce");
    a2dp_source.set_discoverability(ESP_BT_GENERAL_DISCOVERABLE);
    a2dp_source.set_volume(60);
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
