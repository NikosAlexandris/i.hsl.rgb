#include <stdio.h>
#include <grass/gis.h>
#include <grass/raster.h>
#include <grass/glocale.h>
#include "globals.h"

/*
 * hue, saturation, lightness,
 * red, green, blue,
 * input file descriptors, output file descriptors,
 * (input/output?) rowbuffers
 */

void open_files(char *hue, char *saturation, char *lightness, 
               char *red, char *green, char *blue,
               int fd_input[3], int fd_output[3],
               DCELL * rowbuffer[3])
{
    /* open output files */
    fd_output[0] = Rast_open_fp_new(red);
    fd_output[1] = Rast_open_fp_new(green);
    fd_output[2] = Rast_open_fp_new(blue);

    /* allocate the cell row buffer */
    rowbuffer[0] = Rast_allocate_d_buf();
    rowbuffer[1] = Rast_allocate_d_buf();
    rowbuffer[2] = Rast_allocate_d_buf();

    /* open input files (maps can be in different mapsets) */
    fd_input[0] = Rast_open_old(hue, "");
    fd_input[1] = Rast_open_old(saturation, "");
    fd_input[2] = Rast_open_old(lightness, "");
}
