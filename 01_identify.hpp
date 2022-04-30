/***********************************************************************

This sample shows how to read the DEVICE id from the NRF_FICR region in
the micro:bit.

This is useful when you want to use the same program with slight
adaptations based on which device it runs on.

Open the Arduino Serial Console (ctrl-M) at 115200 baud and see this:

    11:15:13.396 -> DEV: Jesper - {0x9A278893,0x14255506}

***********************************************************************/

#include <Arduino.h>
#include "nrf.h"

struct known_device_ids {
    uint32_t device_id0;
    uint32_t device_id1;
} known_devices[] = {
    { 0x9A278893, 0x14255506 }, // Jesper
    { 0xA8F4A4DD, 0x569A7D70 }, // Seb
    { 0x8294B254, 0x61091A15 }, // Vera
    { 0, 0 }
};

enum known_device {
    DEV_UNKNOWN = -1,
    DEV_JESPER, DEV_SEB, DEV_VERA,
};

char const *const known_device_names[] = {
    "Jesper", "Seb", "Vera",
};

enum known_device CURRENT_DEVICE_ID;
char CURRENT_DEVICE_IDS[24];
char const *CURRENT_DEVICE_NAME;

/* Neat trick to let us do multiple Serial.print() using the << operator:
 * Serial << x << " " << y << LF; */
template<class T> inline Print &operator << (Print &obj, T arg) {
    obj.print(arg);
    return obj;
};

void setup_device_id() {
    sprintf(CURRENT_DEVICE_IDS, "{0x%lX,0x%lX}",
            NRF_FICR->DEVICEID[0], NRF_FICR->DEVICEID[1]);
    int i = 0;
    while (known_devices[i].device_id0 || known_devices[i].device_id1) {
        if (NRF_FICR->DEVICEID[0] == known_devices[i].device_id0 &&
                NRF_FICR->DEVICEID[1] == known_devices[i].device_id1) {
            CURRENT_DEVICE_ID = (enum known_device)i;
            CURRENT_DEVICE_NAME = known_device_names[CURRENT_DEVICE_ID];
            return;
        }
        ++i;
    }
    CURRENT_DEVICE_NAME = CURRENT_DEVICE_IDS;
}

void setup() {
    setup_device_id();
    Serial.begin(115200);
    Serial << "DEV: " << CURRENT_DEVICE_NAME << " - " <<
        CURRENT_DEVICE_IDS << '\n';
}

void loop () {
    delay(1000);
}
