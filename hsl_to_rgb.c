/*
 * PURPOSE      Convert hue, saturation and lightness properties of the HSL
 *              color space model to red, green and blue of the RGB color space
 *              model
 */

#include <grass/gis.h>
#include "globals.h"
#include <math.h>

void hsl_to_rgb(DCELL *rowbuffer[3], int columns, double max_colors)
{
    long column;            // column indicator
    double red;             // the red band output
    double green;           // the green band output
    double blue;            // the blue band output
    double chroma;          // value used for determining RGB
    double intermediate;    // value used for determining RGB
    double baseline_rgb;    // value used for determining RGB
    double lightness;       // lightness value
    double saturation;      // saturation value
    double hue;             // hue
    double hue60;           // hue

    /* loop over columns and appropriately set NULLs */
    for (column = 0; column < columns; column++) {
    if (Rast_is_d_null_value(&rowbuffer[0][column]) ||
        Rast_is_d_null_value(&rowbuffer[1][column]) ||
        Rast_is_d_null_value(&rowbuffer[2][column]))
    {
        Rast_set_d_null_value(&rowbuffer[0][column], 1);
        Rast_set_d_null_value(&rowbuffer[1][column], 1);
        Rast_set_d_null_value(&rowbuffer[2][column], 1);
        continue;
    }

    /* input HSL color-space properties */
    hue = rowbuffer[0][column];
    saturation = rowbuffer[1][column];
    lightness = rowbuffer[2][column];
    G_debug(2, "Input Hue, Saturation, Lightness: %f, %f, %f",
            hue, saturation, lightness);

    /* chroma, hue/60, intermediate `x`, baseline RGB */
    chroma = (1.0 - fabs(2.0*lightness - 1.0)) * saturation;
    G_debug(2, "Chroma: %f", chroma);

    hue60 = hue / 60.0;
    G_debug(2, "Hue/60: %f", hue60);

    intermediate = chroma * (1.0 - fabs( fmod(hue60, 2) - 1.0));
    G_debug(2, "Intermediate: %f", intermediate);

    baseline_rgb = lightness - 0.5 * chroma;
    G_debug(2, "Baseline RGB value: %f", baseline_rgb);

    /* conversions */
    if (hue >= 0.0 && hue < 60.0)
    {
        red = chroma;
        green = intermediate;
        blue = 0.0;
    }
    else if (hue >= 60.0 && hue < 120.0)
    {
        red = intermediate;
        green = chroma;
        blue = 0.0;
    }
    else if (hue >= 120.0 && hue < 180.0)
    {
        red = 0.0;
        green = chroma;
        blue = intermediate;
    }
    else if (hue >= 180.0 && hue < 240.0)
    {
        red = 0.0;
        green = intermediate;
        blue = chroma;
    }
    else if (hue >= 240.0 && hue < 300.0)
    {
        red = intermediate;
        green = 0.0;
        blue = chroma;
    }
    else if (hue >= 300.0 && hue < 360.0)
    {
        red = chroma;
        green = 0.0;
        blue = intermediate;
    }
    else
    {
        red = green = blue = 0.0;
    }

    /* add baseline RGB value */
    red += baseline_rgb;
    green += baseline_rgb;
    blue += baseline_rgb;
    G_debug(2, "Red, Green, Blue: %f, %f, %f", red, green, blue);

    /* scale up to requested bitness */
    red *= max_colors;
    green *= max_colors;
    blue *= max_colors;
    G_debug(2, "Red, Green, Blue [scaled up to]: %f, %f, %f, [%.0f]",
            red, green, blue, max_colors);

    /* place output row into corresponding buffer */
    rowbuffer[0][column] = (DCELL) red;
    rowbuffer[1][column] = (DCELL) green;
    rowbuffer[2][column] = (DCELL) blue;
    }
}
