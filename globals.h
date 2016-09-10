#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <grass/raster.h>

/*
 * open_files.c
 * hue, saturation, lightness,
 * red, green, blue,
 * int fd_input[3], int fd_output[3],
 * DCELL * rowbuf[3]
 */
void open_files(char *, char *, char *,
                char *, char *, char *,
                int[3], int[3],
                DCELL *[3]);

/* hsl_to_rgb.c */
void hsl_to_rgb(DCELL *[3], int, double);

/*
 * close_files.c
 * free allocated memory (row buffers),
 * close raster maps
 * set color table for output maps to grey scale.
 */
int close_files(char *, char *, char *,
                int[3],
                DCELL *[3]);

#endif /* __GLOBALS_H__ */
