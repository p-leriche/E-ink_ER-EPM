# E-ink_ER-EPM
Arduino library for East Rising e-ink displays.

This library provides facilities for displaying text and simple graphics on e-ink displays. It is based on the sample code distributed by East Rising, but with the following enhancements:
* 50% shaded fill is offered in addition to solid fill for rectangles and circles.
* The same library can be used for any size display.
* Different pin numbers may be chosen for connection to the Arduino instead of the default 7, 8, 9 and 10. (MOSI, pin 11 and SCLK pin 13 cannot be changed.)

For now (at least), only a single display is supported.

Introduction
============

The top left hand corner of the display is pixel (0, 0).

In order to save RAM, text and graphics are individually uploaded to the display, each as a rectangular "paint" object, being a subset of the display.

Pixels are similarly addressed within a paint object, but the coordinate frame can be rotated, for example, to give vertical text. Thus, with a 90 degree (clockwise) rotation, (0, 0) is the top right hand pixel and text would read from top to bottom.

Pixels within a paint object are either COLORED or UNCOLORED. UNCOLORED is white. On uploading the paint object, COLORED can be specified as either black or the secondary colour (red or yellow, according to the type of display).

Initialisation
==============

First, you must create an epd (e-paper display) object:
Epd edp();

The default width and height is 152 pixels, but you can create an epd for a different size display:
Epd epd(WIDTH, HEIGHT);

The default Arduino pin numbers are:
BUSY:  7
RESET: 8
DC:    9
CS:   10
These can be changed:
Epd epd(WIDTH, HEIGHT, BUSY_PIN, RESET_PIN, DC_PIN, CS_PIN);

Next, we must create a paint object, giving it a char array to store data in:
unsigned char image[1024];
Paint paint(image, 152, 18); // Create a paint object width 152 height 18

The char array must be large enough to hold the biggest paint object which is to be used, calculated at 8 pixels per byte.
Note that the width MUST be a multiple of 8 otherwise it will be rounded up and may give confusing results. The width and height are initial values, and can be changed later.

Text and Graphics
=================
The dimensions of a paint object can be changed at any time, e.g.:
paint.SetWidth(40);
paint.SetHeight(36);

The rotation state can be set thus:
paint.SetRotate(ROTATE_270);

Also available are ROTATE_0, ROTATE_90 and ROTATE_180.
Note that this simply defineswhich corner of the paint object is considered (0.0).

A paint object must first be initialised to either COLORED or UNCOLORED, e.g.:
paint.Clear(UNCOLORED);

Text and graphics may be drawn either COLORED or UNCOLORED, e.g. to set an individual pixel in a paint object:
paint.DrawPixel(5, 3, COLORED);

This will set pixel (5, 3) within thepaint object to the required state.

You can draw text anywhere within a paint object:
paint.DrawStringAt(22, 2, "e-ink Demo", &Font16, COLORED);

This would place the string with the top left hand pixel of the first character at (22, 2). Other size fonts are available:
Font8  - 5x8 pixels
Font12 - 7x12 pixels
Font16 - 11x16 pixels
Font20 - 14x20 pixels
Font24 - 17x24 pixels

To draw a line, you specify the coordinates of the ends, e.g. from (5, 3) tp (35, 33):
paint.DrawLine(5, 3, 35, 33, COLORED);

For a rectangle or filled rectangle, specify the coordinates of two opposite corners:
paint.DrawRectangle(5, 3, 35, 33, COLORED);
paint.DrawFilledRectangle(5, 3, 35, 33, COLORED);

A (50%) shaded rectangle is the same except that you don't need to specify COLORED or UNCOLORED as it would make no perceptible difference:
paint.DrawShadedRectangle(5, 3, 35, 33);

For a speckled rectangle (random pixels COLORED), optionally specify the density as a percent of COLORED pixels (default 50%). The following are equivalent:
paint.DrawSpeckledRectangle(5, 3, 35, 33);
paint.DrawSpeckledRectangle(5, 3, 35, 33, 50);

For a circle, specify the coordinates of the centre, and the radius:
paint.DrawCircle(20, 18, 15, COLORED);
paint.DrawFilledCircle(20, 18, 15, COLORED);
paint.DrawShadedCircle(20, 18, 15);
paint.DrawSpeckledCircle(20, 18, 15, 50); // (The density defaults to 50 if not given)

(The centre in these examples is (20, 18) and the radius is 15.)

Uploading a paint object to the display
=======================================

A paint object can be uploaded with COLORED pixels representing either black or red. You must specify the absolute coordinates on the display of the top left hand pixel of the area to be painted (0, 42 in these examples):
epd.SetPartialWindowBlack(paint.GetImage(), 0, 42, paint.GetWidth(), paint.GetHeight());

or:
epd.SetPartialWindowRed(paint.GetImage(), 0, 42, paint.GetWidth(), paint.GetHeight());

So far we have only uploaded the image to the display's internal RAM. It is still necessary to command it to refresh the display with this image:
epd.DisplayFrame();

Instead of constructing an image with the text and graphic functions, you can directly upload a complete bitmap. Black and red pixels are specified in separate bitmaps. The bitmap specifies the display pixels row by row with 8 pixels per byte. You can create it programatically (as the text and graphic functions do for you) or you can find or create a tool for convering a common bitmap file format such as .bmp or .png.
epd.DisplayFrame(image_black, image_red);

If you wish to clear the display you can do this as follows:
epd.ClearFrame();

To save power, you can turn the display off (the image, of course, will be retained):
epd.Sleep();
