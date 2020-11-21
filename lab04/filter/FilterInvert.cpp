#include "FilterInvert.h"
#include <iostream>
FilterInvert::~FilterInvert()
{
}

void FilterInvert::apply(Canvas2D *canvas) {
    int width = canvas->width();

    RGBA* current_pixel = nullptr;
    RGBA* current_row = canvas->data();

    // TODO: Task 8 [Optional] Use bitwise complement to set inversion

    for (int r = 0; r < canvas->height(); r++) {
        current_pixel = current_row;

        for (int c = 0; c < canvas->width(); c++) {
            // TODO: Task 7 Update the color with its inversion

            char red = current_pixel->r;
            char green = current_pixel->g;
            char blue = current_pixel->b;
            current_pixel->r = 255 - red;
            current_pixel->g = 255 - green;
            current_pixel->b = 255 - blue;


            // CONTINUED: Task 8 [Optional]


            current_pixel++;
        }
        current_row += width;
    }
}
