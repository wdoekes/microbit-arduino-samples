/***********************************************************************

This sample shows the three different LED patterns on the micro:bit
that can be lit up at the same time. 12 pins are used, for 3 "rows" and
9 simultanous LEDs.

See: https://lancaster-university.github.io/microbit-docs/ubit/display/

> if we scan through the different rows fast enough - faster than the
> eye can see - then we can provide the illusion of all the LEDS being
> on at the same time!

This is only useful to understand how the LEDs work. You'll normally
want to use some abstraction that handles this for you. Like
Adafruit_Microbit_Matrix from <Adafruit_Microbit.h>.

Listing on the Serial console:

    11:43:23.926 -> showing rows
    11:43:23.926 -> row (all LEDs) 0
    11:43:24.923 -> row (all LEDs) 1
    11:43:25.919 -> row (all LEDs) 2

    11:43:29.944 -> showing individual pixels
    11:43:29.944 -> row 0 0 (1.1) 1 (2.4) 2 (1.2) 3 (2.5) 4 (1.3)
    11:43:30.444 -> row 1 0 (3.4) 1 (3.5) 2 (3.6) 3 (3.7) 4 (3.8)
    11:43:30.943 -> row 2 0 (2.2) 1 (1.9) 2 (2.3) 3 (3.9) 4 (2.1)
    11:43:31.442 -> row 3 0 (1.8) 1 (1.7) 2 (1.6) 3 (1.5) 4 (1.4)
    11:43:31.940 -> row 4 0 (3.3) 1 (2.7) 2 (3.1) 3 (2.6) 4 (3.2)

***********************************************************************/

#include <Arduino.h>

/* Neat trick to let us do multiple Serial.print() using the << operator:
 * Serial << x << " " << y << LF; */
template<class T> inline Print &operator << (Print &obj, T arg) {
    obj.print(arg);
    return obj;
};
const char endl = '\n';

// rowpins/colpins shamelessly taken from
// https://github.com/adafruit/Adafruit_Microbit
//   /blob/master/Adafruit_Microbit.cpp
#if defined(NRF51)
# define MATRIX_ROWS 3 //!< Number of rows on the microbit LED matrix
# define MATRIX_COLS 9 //!< Number of columns on the microbit LED matrix
uint8_t rowpins[MATRIX_ROWS] = {26, 27, 28};
uint8_t colpins[MATRIX_COLS] = {3,  4, 10, 23, 24, 25, 9, 7,  6};
uint8_t pixel_to_row[25] = {
    1, 2, 1, 2, 1, 3, 3, 3, 3, 3, 2, 1, 2,
    3, 2, 1, 1, 1, 1, 1, 3, 2, 3, 2, 3};
uint8_t pixel_to_col[25] = {
    1, 4, 2, 5, 3, 4, 5, 6, 7, 8, 2, 9, 3,
    9, 1, 8, 7, 6, 5, 4, 3, 7, 1, 6, 2}; 
#else
# error Unhandled micro:bit version
#endif

void setup() {  
    Serial.begin(115200);

    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
        pinMode(colpins[c], OUTPUT);
        digitalWrite(colpins[c], HIGH); /* set all lights OFF */
    }

    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        pinMode(rowpins[r], OUTPUT);
        digitalWrite(rowpins[r], LOW); /* DISABLE all rows */
    }
}

void loop() {
    Serial << endl << "showing rows" << endl;

    for (uint8_t i = 0; i < 2; ++i) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            digitalWrite(colpins[c], LOW); /* set all columns ON */
        }
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            Serial << "row (all LEDs) " << row << endl;
            digitalWrite(rowpins[row], HIGH); /* row ON */
            delay(1000);
            digitalWrite(rowpins[row], LOW); /* row OFF */
        }
    }

    Serial << endl << "showing individual pixels" << endl;

    for (uint8_t i = 0; i < 2; ++i) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            digitalWrite(colpins[c], HIGH); /* set all columns OFF */
        }
        for (uint8_t row = 0; row < 5; ++row) {
            Serial << "row " << row;
            for (uint8_t col = 0; col < 5; ++col) {
                uint8_t idx = 5 * row + col;
                uint8_t lr = pixel_to_row[idx];
                uint8_t lc = pixel_to_col[idx];
                Serial << " " << col << " (" << lr << "." << lc << ")";
                digitalWrite(rowpins[lr - 1], HIGH); /* row ON */
                digitalWrite(colpins[lc - 1], LOW);  /* col ON */
                delay(100);
                digitalWrite(rowpins[lr - 1], LOW);  /* row OFF */
                digitalWrite(colpins[lc - 1], HIGH); /* col OFF */
            }
            Serial << endl;
        }
    }
}
