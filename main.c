
/****************************************************************************
 *
 * MODULE:      i.hsl.rgb
 *
 * AUTHOR(S):   Nikos Alexandris
 *
 * PURPOSE:     Color space conversion, HSL to RGB
 *
 * COPYRIGHT:   (C) 2016 by Nikos Alexandris and the GRASS Development Team
 *
 *              This program is free software under the GNU General
 *              Public License (>=v2). Read the COPYING file that
 *              comes with GRASS for details.
 *
 * NOTES:       - Reused base code from i.his.rgb and parts from a diff submitted
 *              in GRASS-GIS' trac ticket #774
 *              Adapted from https://en.wikipedia.org/wiki/HSL_and_HSV#From_HSL
 *              - Adapted from https://en.wikipedia.org/wiki/HSL_and_HSV#From_HSL
 *              - Also consulted http://dystopiancode.blogspot.ch/2012/06/hsl-rgb-conversion-algorithms-in-c.html
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <grass/gis.h>
#include <grass/raster.h>
#include <grass/glocale.h>
#include "globals.h"

int main(int argc, char **argv)
{

    unsigned long row;
    unsigned int rows, cols;
    DCELL *rowbuffer[3];
    struct Option *opt_hue;
    struct Option *opt_saturation;
    struct Option *opt_lightness;
    struct Option *opt_red;
    struct Option *opt_green;
    struct Option *opt_blue;
    struct Option *opt_bits;    // bits per input image, as in bits per channel
    struct GModule *module;
    unsigned int bits;
    unsigned int max_colors;          // maximum number of colors
    int fd_input[3];
    int fd_output[3];

    G_gisinit(argv[0]);

    /* Set description */
    module = G_define_module();
    G_add_keyword(_("imagery"));
    G_add_keyword(_("color space conversion"));
    G_add_keyword("HSL");
    G_add_keyword("hue");
    G_add_keyword("saturation");
    G_add_keyword("lightness");
    G_add_keyword("RGB");
    module->description =
    ("Converts Hue, Saturation, Lightness (HSL) images to "
     "Red, Green, Blue (RGB)");

    /* Define the different options */
    opt_hue = G_define_standard_option(G_OPT_R_INPUT);
    opt_hue->key = "hue";
    opt_hue->description = _("Hue input image in degrees [0, 360]");

    opt_saturation = G_define_standard_option(G_OPT_R_INPUT);
    opt_saturation->key = "saturation";
    opt_saturation->description = _("Saturation input image ranging in [0, 1]");

    opt_lightness = G_define_standard_option(G_OPT_R_INPUT);
    opt_lightness->key = "lightness";
    opt_lightness->description = _("Lightness input image ranging in [0, 1]");

    opt_red = G_define_standard_option(G_OPT_R_OUTPUT);
    opt_red->key = "red";
    opt_red->description = _("Red output image");

    opt_green = G_define_standard_option(G_OPT_R_OUTPUT);
    opt_green->key = "green";
    opt_green->description = _("Green output image");

    opt_blue = G_define_standard_option(G_OPT_R_OUTPUT);
    opt_blue->key = "blue";
    opt_blue->description = _("Blue output image");

    opt_bits = G_define_option();
    opt_bits->key = "bits";
    opt_bits->type = TYPE_INTEGER;
    opt_bits->required = NO;
    opt_bits->answer = "8";
    opt_bits->options = "2-16";
    opt_bits->description = _("Bits per output image");

    if (G_parser(argc, argv))
        exit(EXIT_FAILURE);

    /* bits per image, should be > 0 */
    bits = atoi(opt_bits->answer);
    if (bits <= 0)
        G_fatal_error(_("Invalid bit depth definition!"));

    /* open half ended range for maximum number of colors */
    max_colors = pow(2, bits) - 1;
    G_debug(1, "%d-bit data ranging in [0,%.0d)", bits, max_colors);

    /* get image dimensions */
    rows = Rast_window_rows();
    cols = Rast_window_cols();

    /* open input and output files */
    open_files(opt_hue->answer,  opt_saturation->answer, opt_lightness->answer,
               opt_red->answer, opt_green->answer, opt_blue->answer,
               fd_input, fd_output, rowbuffer);

    /* loop over hue, saturation and lightness color space properties */
    for (row = 0; row < rows; row++) {
         int property;

        /* read in row from each cell map */
        for (property = 0; property < 3; property++)
             Rast_get_d_row(fd_input[property], rowbuffer[property], row);

            /* process row of image */
            hsl_to_rgb(rowbuffer, cols, max_colors);

        /* write out the new row for each cell map */
        for (property = 0; property < 3; property++)
             Rast_put_row(fd_output[property], rowbuffer[property], DCELL_TYPE);
    }

    /* progress */
    G_percent(row, rows, 2);

    /* close output files */
    close_files(opt_red->answer, opt_green->answer, opt_blue->answer,
                fd_output, rowbuffer);

    exit(EXIT_SUCCESS);
}
