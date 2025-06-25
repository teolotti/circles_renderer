//
// Created by matteo on 26/03/25.
//
#include <vector>
#include <random>
#include "Circle.h"
#include "CircleSoA.h"
#include "Utils.h"

#ifndef CIRCLES_RENDERER_GENERATOR_H
#define CIRCLES_RENDERER_GENERATOR_H


class CircleUtils : public Utils {
protected:
    std::vector<std::vector<double>> imgR;
    std::vector<std::vector<double>> imgG;
    std::vector<std::vector<double>> imgB;
    int width;
    int height;
    std::vector<Circle*> circles;
    const double alpha = 0.5;
    int n;

public:
    CircleUtils(int width, int height) : width(width), height(height) {
        imgR = std::vector<std::vector<double>>(width, std::vector<double>(height, 0.0));
        imgG = std::vector<std::vector<double>>(width, std::vector<double>(height, 0.0));
        imgB = std::vector<std::vector<double>>(width, std::vector<double>(height, 0.0));
    }

    void generateCircles();
    void renderCircles();
    bool isInsideCircle(double px, double py, int index);
    void savePPM(const std::string& filename);

};


#endif //CIRCLES_RENDERER_GENERATOR_H
