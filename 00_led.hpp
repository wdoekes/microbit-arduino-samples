/***********************************************************************

This sample manual LED settings on the micro:bit.

See: https://lancaster-university.github.io/microbit-docs/ubit/display/

This is only useful to understand how the LEDs work. You'll normally
want to use some abstraction that handles this for you. Like
Adafruit_Microbit_Matrix from <Adafruit_Microbit.h>.

Pixel PINs with "rows" and "columns". The row pin must be set HIGH and
the column pin must be set LOW.

    (26. 3) (27.23) (26. 4) (27.24) (26.10)
    (28.23) (28.24) (28.25) (28. 9) (28. 7)
    (27. 4) (26. 6) (27.10) (28. 6) (27. 3)
    (26. 7) (26. 9) (26.25) (26.24) (26.23)
    (28.10) (27. 9) (28. 3) (27.25) (28. 4)
    (26. 3) (27.23) (26. 4) (27.24) (26.10)

These values are only valid for the micro:bit.

***********************************************************************/

#include <Arduino.h>

uint8_t led_row = 26;
uint8_t led_col = 3;

/* Neat trick to let us do multiple Serial.print() using the << operator:
 * Serial << x << " " << y << LF; */
template<class T> inline Print &operator << (Print &obj, T arg) {
    obj.print(arg);
    return obj;
};
const char endl = '\n';

void setup() {
    Serial.begin(115200);
    pinMode(led_row, OUTPUT);
    pinMode(led_col, OUTPUT);
    digitalWrite(led_row, HIGH); /* select this row */
}

void loop() {
    Serial << "on" << endl;
    digitalWrite(led_col, LOW); /* ON */
    delay(500);
    Serial << "off" << endl;
    digitalWrite(led_col, HIGH); /* OFF */
    delay(500);
}
