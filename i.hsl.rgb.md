DESCRIPTION
-----------

*i.hsl.rgb* converts hue, saturation and lightness input images, being
dimensions of the HSL color space, into red, green and blue values in
the RGB color space. Each output image is given a linear gray scale
color table. The current geographic region and mask settings are
respected.

EXAMPLES
--------

Read examples in the manual of [i.rgb.hsl](i.rgb.hsl.html)

NOTES
-----

- The <em>bits</em> option refers to the bit (or color) depth of the input
images, as in *bits per color channel*.  Not to confuse with *bits-per-pixel*,
which refers to the sum of all three color channels.  For example, an 8-bit
image feaures 256 number of colors.  Expecting all input images to be of the
same color depth, in this case 8 bits, then, an RGB composite would feature 24
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
