#include <array>

class LedBitmap
{
    private:
        std::array<std::array<uint8_t, 12>,8> led_bitmap;
        /**
         * Sets Led Bitmap to have a bold letter H.
         * 
         * @param starting_col Optional arguement for horizontal formatting of letter H
         */
        void set_letter_h(int starting_col = 1);
        /**
         * Sets Led Bitmap to have a bold letter i.
         * 
         * @param starting_col Optional arguement for horizontal formatting of letter i
         */
        void set_letter_i(int starting_col = 8);
        /**
         * Clears the matrix on the interface and resets the LED bitmap to all zeros to prevent propagation of lit leds.
         */
        void reset_bitmap();
    public:
        /**
         * Constructor of LED bitmap. Intializes LED interface on Arduino as well. 
         */
        LedBitmap();
        /**
         * Build Hi in bitmap so display can take in one function pointer.
         */
        void build_hi();
        /**
         * Building of WIFI <checkmark>. Uses magic numbers and hardocded values.
         */
        void set_wifi_success();
        /**
         * Building of WIFI <x>. Uses magic numbers and hardocded values.
         */
        void set_wifi_fail();
        /**
         * Displays the bitmap LED on the arduino using matrix interface.
         * 
         * @param display_func Pointer to the callable function to execute to set the bitmap before displaying
         * @param should_reset Optional argument if the board should reset after showing the message
         * @param user_delay Optional argument specifying the amount of time to display the message before resetting the matrix
         */
        void display_bitmap(void (LedBitmap::*display_func)(), bool should_reset = true, int user_delay = 2500);
};
