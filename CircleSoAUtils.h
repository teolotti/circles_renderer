//
// Created by matteo on 28/03/25.
//

#include <string>
#include "CircleSoA.h"
#include "Utils.h"

#ifndef CIRCLES_RENDERER_CIRCLESOAUTILS_H
#define CIRCLES_RENDERER_CIRCLESOAUTILS_H


class CircleSoAUtils : public Utils {
private:
    CircleSoA* circles;
    int width;
    int height;
    int n;
    double alpha = 0.5;

public:
    CircleSoAUtils(int width, int height) : width(width), height(height) {
        circles = new CircleSoA(width * height);
    }

    ~CircleSoAUtils() {
        delete circles;
    }

    void generateCircles();
    void renderCircles();
    bool isInsideCircle(double px, double py, int index);
    void savePPM(const std::string& filename);

};


#endif //CIRCLES_RENDERER_CIRCLESOAUTILS_H
