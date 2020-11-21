#include "FilterShift.h"
#include "FilterUtils.h"

FilterShift::FilterShift(ShiftDirection direction):
    m_shiftDir(direction)
{
    // TODO: Task 19 Initialize kernel for shift
    m_kernel={0.f,0.f,0.f,
             m_shiftDir == SHIFT_RIGHT? 1.f:0.f,0.f,m_shiftDir == SHIFT_LEFT? 1.f:0.f,
             0.f,0.f,0.f,};

}

FilterShift::~FilterShift()
{
}

void FilterShift::apply(Canvas2D *canvas) {
    // TODO: Task 18 Call convolve function from superclass
    FilterUtils::Convolve2D(canvas->data(),canvas->width(),canvas->height(),m_kernel);

}
