#include <libgimp/gimp.h>

void glitch(GimpDrawable* dr, int rand_regions, int shift);

void inverse_pixels(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels);
void shift_pixels(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels, int shift);
void color_corrupt(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels);
void get_random_rgn(GimpDrawable* dr, GimpPixelRgn* rgin, GimpPixelRgn* rgout);
