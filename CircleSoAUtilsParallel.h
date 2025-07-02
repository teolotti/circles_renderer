//
// Created by matteo on 27/06/25.
//

#ifndef CIRCLES_RENDERER_CIRCLESOAUTILSPARALLEL_H
#define CIRCLES_RENDERER_CIRCLESOAUTILSPARALLEL_H


#include "CircleSoAUtils.h"

class CircleSoAUtilsParallel : public CircleSoAUtils {
public:
    CircleSoAUtilsParallel(int width, int height, int n) : CircleSoAUtils(width, height, n) {}

    void generateCircles() override;
    void renderCircles() override;
};


#endif //CIRCLES_RENDERER_CIRCLESOAUTILSPARALLEL_H
