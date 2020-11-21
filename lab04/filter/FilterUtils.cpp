#include "FilterUtils.h"
#include <algorithm>
#include "math.h"
#include <cstring>
#include <iostream>


namespace FilterUtils {

inline unsigned char REAL2byte(float f) {
    int i = static_cast<int>((f * 255.0 + 0.5));
    return (i < 0) ? 0 : (i > 255) ? 255 : i;
}

void Convolve2D(RGBA* data, int width, int height, const std::vector<float> &kernel) {
    // TODO: Task 9 Create buffer to store new image data
    RGBA results[width * height];

    // TODO: Task 10 Obtain kernel dimension
    int dim = sqrt(kernel.size());

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            size_t centerIndex = r * width + c;
            // TODO: Task 11 Initialize color to accumulate convolution data
            float red_acc = 0.f;
            float green_acc = 0.f;
            float blue_acc = 0.f;

            // TODO: Task 12
            // Iterate over the kernel using the value from task 10
            // Obtain the value at current index of kernel
            // Find correct index in original image data
            // Accumulate the kernel applied to pixel value in color_acc
            for (int rk = 0; rk < dim; rk ++){
                for (int ck = 0; ck < dim; ck ++){
                    if (r - dim/2 + rk < 0 || r - dim/2 + rk >= height|| c - dim/2 + ck < 0 || c - dim/2 + ck>= width){
                        continue;
                    }

                    float ker = kernel[rk * dim + ck];
                    RGBA pix = data[(r - dim/2 + rk) * width + (c - dim/2 + ck)];
                    red_acc += (float)pix.r * ker;
                    green_acc += (float)pix.g * ker;
                    blue_acc += (float)pix.b * ker;

                }
            }

            // TODO: Task 13 Ignore outside bounds


            // TODO: Task 14 Update buffer with accumulated color
            results[r * width + c] = RGBA((int)red_acc,(int)green_acc,(int)blue_acc);

        }
    }

    // TODO: Task 15 Copy over buffer to canvas data
    memcpy(data,results,width*height*sizeof(RGBA));
}

}
