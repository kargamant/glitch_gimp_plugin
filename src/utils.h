#include <libgimp/gimp.h>

void glitch(GimpDrawable* dr);

void inverse_pixels(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels);
void shift_pixels(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels);
void color_corrupt(GimpPixelRgn* rgin, GimpPixelRgn* rgout, int channels);
void get_random_rgn(GimpDrawable* dr, GimpPixelRgn* rgin, GimpPixelRgn* rgout);
