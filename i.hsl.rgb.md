DESCRIPTION
-----------

*i.hsl.rgb* converts hue, saturation and lightness input images, being
dimensions of the HSL color space, into red, green and blue values in
the RGB color space. Each output image is given a linear gray scale
color table. The current geographic region and mask settings are
respected.

NOTES
-----

- The *bits* option refers to the bit (or color) depth of the input
images, as in bits per color channel. Not to be confused with bits-per-pixel,
which refers to the sum of all three color channels.  For example, an 8-bit
image feaures 256 number of colors.  Expecting all input images to be of the
same color depth, in example 8 bits, then, an RGB composite would feature 24
bits per pixel.

- It is possible to process three images with *i.hsl.rgb* and then recover
the original images with *i.rgb.hsl*.

SEE ALSO
--------

*[i.rgb.hsl](i.rgb.hsl.html), [i.rgb.his](i.rgb.his.html), [i.rgb.his](i.his.rgb.html),
[r.colors](r.colors.html)*

AUTHOR
------

Nikos Alexandris

*Last changed: \$Date: 2016-09-09 13:10:00 +0100 (Fri, 9 Sep 2016) \$*
