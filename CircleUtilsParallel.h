//
// Created by matteo on 25/06/25.
//

#ifndef CIRCLES_RENDERER_CIRCLEUTILSPARALLEL_H
#define CIRCLES_RENDERER_CIRCLEUTILSPARALLEL_H


#include "CircleUtils.h"

class CircleUtilsParallel : public CircleUtils {
//private:
//    std::vector<std::vector<double>> imgR;
//    std::vector<std::vector<double>> imgG;
//    std::vector<std::vector<double>> imgB;
//    int width;
//    int height;
//    std::vector<Circle*> circles;
//    const double alpha = 0.5;
//    int n;
public:
    CircleUtilsParallel(int width, int height) : CircleUtils(width, height) {}
//        imgR = std::vector<std::vector<double>>(width, std::vector<double>(height, 0.0));
//        imgG = std::vector<std::vector<double>>(width, std::vector<double>(height, 0.0));
//        imgB = std::vector<std::vector<double>>(width, std::vector<double>(height, 0.0));
//    }

    void renderCircles() override;

};


#endif //CIRCLES_RENDERER_CIRCLEUTILSPARALLEL_H
