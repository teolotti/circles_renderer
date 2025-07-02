//
// Created by matteo on 25/06/25.
//

#ifndef CIRCLES_RENDERER_CIRCLEUTILSPARALLEL_H
#define CIRCLES_RENDERER_CIRCLEUTILSPARALLEL_H


#include "CircleUtils.h"

class CircleUtilsParallel : public CircleUtils {
public:
    CircleUtilsParallel(int width, int height, int n) : CircleUtils(width, height, n) {}

    void generateCircles() override;
    void renderCircles() override;

};


#endif //CIRCLES_RENDERER_CIRCLEUTILSPARALLEL_H
