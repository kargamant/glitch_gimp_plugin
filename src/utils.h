#include <libgimp/gimp.h>

void inverse_pixels(GimpDrawable* dr);
void shift_pixels(GimpDrawable* dr);
void color_corrupt(GimpDrawable* dr);
void get_random_rgn(GimpDrawable* dr, GimpPixelRgn* rgin, GimpPixelRgn* rgout);
