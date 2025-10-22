#include <LedBitmap.h>
#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;

LedBitmap::LedBitmap()
{
    led_bitmap = {{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}};

    matrix.begin();
}

void LedBitmap::reset_bitmap()
{
    matrix.clear();
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 12; col++)
        {
            led_bitmap[row][col] = 0;
        }
    }
}

void LedBitmap::display_bitmap(void (LedBitmap::*display_func)(), bool should_reset, int user_delay) {
    (this->*display_func)();    
    matrix.renderBitmap(led_bitmap, 8, 12);
    if(should_reset) {
        delay(user_delay);
        reset_bitmap();
    }
}

void LedBitmap::set_letter_h(int starting_col)
{
    for (int row = 0; row < 8; row++)
    {
        led_bitmap[row][starting_col] = 1;
        led_bitmap[row][starting_col + 1] = 1;
        led_bitmap[row][starting_col + 4] = 1;
        led_bitmap[row][starting_col + 5] = 1;
    }
    led_bitmap[4][starting_col + 2] = 1;
    led_bitmap[3][starting_col + 2] = 1;
    led_bitmap[4][starting_col + 3] = 1;
    led_bitmap[3][starting_col + 3] = 1;
}

void LedBitmap::set_letter_i(int starting_col)
{
    for (int row = 3; row < 8; row++)
    {
        led_bitmap[row][starting_col] = 1;
        led_bitmap[row][starting_col + 1] = 1;
    }
    led_bitmap[0][starting_col + 1] = 1;
    led_bitmap[1][starting_col] = 1;
    led_bitmap[1][starting_col + 1] = 1;
    led_bitmap[0][starting_col] = 1;
}

void LedBitmap::build_hi() {
    set_letter_h();
    set_letter_i();
}

void LedBitmap::set_wifi_success() {
    led_bitmap = {{{1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
                   {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
                   {1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0},
                   {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                   {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}}};
}

void LedBitmap::set_wifi_fail() {
    led_bitmap = {{{1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
                   {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
                   {1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0},
                   {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0}}};
}