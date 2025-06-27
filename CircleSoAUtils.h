//
// Created by matteo on 28/03/25.
//

#include <string>
#include "CircleSoA.h"
#include "Utils.h"

#ifndef CIRCLES_RENDERER_CIRCLESOAUTILS_H
#define CIRCLES_RENDERER_CIRCLESOAUTILS_H


class CircleSoAUtils : public Utils {
protected:
    std::vector<std::vector<double>> imgR;
    std::vector<std::vector<double>> imgG;
    std::vector<std::vector<double>> imgB;
    CircleSoA* circles;
    int width;
    int height;
    int n;
    double alpha = 0.5;

public:
    CircleSoAUtils(int width, int height, int n) : width(width), height(height), n(n) {
        circles = new CircleSoA(n);
        imgR = std::vector<std::vector<double>>(width, std::vector<double>(height, 0.0));
        imgG = std::vector<std::vector<double>>(width, std::vector<double>(height, 0.0));
        imgB = std::vector<std::vector<double>>(width, std::vector<double>(height, 0.0));
    }

    ~CircleSoAUtils() {
        delete circles;
    }

    void generateCircles() override;
    void renderCircles() override;
    bool isInsideCircle(double px, double py, int index) override;
    void savePPM(const std::string& filename) override;

};


#endif //CIRCLES_RENDERER_CIRCLESOAUTILS_H
